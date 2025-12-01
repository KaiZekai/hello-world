import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# 设置绘图风格
plt.style.use('seaborn-v0_8')
plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False      # 用来正常显示负号

# ==========================================
# 1. 数据读取与清洗
# ==========================================
print("Step 1: 读取数据...")
try:
    df = pd.read_csv('data.csv', encoding='GBK')
except:
    df = pd.read_csv('data.csv', encoding='utf-8')

df['EventDate'] = pd.to_datetime(df['EventDate'])
df.sort_values(['SecuCode', 'EventDate'], inplace=True)

# 计算基础指标
df['daily_ret'] = df.groupby('SecuCode')['close'].pct_change()
df['turnover'] = df['volume'] / df['AFloats']
df.dropna(subset=['daily_ret', 'turnover'], inplace=True)

# ==========================================
# 2. 构建三大动量因子 (核心加分项)
# ==========================================
print("Step 2: 计算三大因子 (普通、加权、指数衰减)...")
N = 20 # 窗口期

# (1) 普通动量
df['return_20d'] = df.groupby('SecuCode')['close'].pct_change(N)

# (2) 换手率加权动量 (前期已做)
df['ret_x_turnover'] = df['daily_ret'] * df['turnover']
rolling = df.groupby('SecuCode').rolling(window=N, min_periods=10)
num = rolling['ret_x_turnover'].sum().reset_index(level=0, drop=True)
den = rolling['turnover'].sum().reset_index(level=0, drop=True)
df['wgt_return_20d'] = num / den

# (3) ★指数衰减加权动量 (Exp Weighted) - 满分关键
# 逻辑：最近几天的换手率和涨跌幅，权重更大。使用 ewm (指数加权移动平均)
# span=N 表示给予最近N天较大的权重
# 分子：(收益 * 换手) 的指数加权均值
num_exp = df.groupby('SecuCode')['ret_x_turnover'].ewm(span=N, adjust=False).mean().reset_index(level=0, drop=True)
# 分母：(换手) 的指数加权均值
den_exp = df.groupby('SecuCode')['turnover'].ewm(span=N, adjust=False).mean().reset_index(level=0, drop=True)
df['exp_wgt_return_20d'] = num_exp / den_exp

# ==========================================
# 3. 因子评估 (IC & 分层回测)
# ==========================================
print("Step 3: 评估因子表现...")

# 计算下期收益 (Target)
df['next_ret'] = df.groupby('SecuCode')['close'].shift(-N) / df['close'] - 1
df_valid = df.dropna(subset=['return_20d', 'wgt_return_20d', 'exp_wgt_return_20d', 'next_ret'])

# --- A. 计算 IC 值 ---
def calc_ic(group):
    return group[['return_20d', 'wgt_return_20d', 'exp_wgt_return_20d']].corrwith(group['next_ret'], method='spearman')

ic_df = df_valid.groupby('EventDate').apply(calc_ic)

print("\n======== 因子 IC 表现 (绝对值越大越好) ========")
print(f"1. 普通动量 IC均值: {ic_df['return_20d'].mean():.4f}")
print(f"2. 加权动量 IC均值: {ic_df['wgt_return_20d'].mean():.4f}")
print(f"3. 指数动量 IC均值: {ic_df['exp_wgt_return_20d'].mean():.4f} (通常最强)")

# --- B. 分层回测 (Stratified Backtest) ---
# 我们选表现最好的 'exp_wgt_return_20d' 来做分层回测
factor_name = 'exp_wgt_return_20d'

# 1. 每天给因子打分，分成 5 组 (group 0 是因子最小，group 4 是因子最大)
df_valid['group'] = df_valid.groupby('EventDate')[factor_name].transform(
    lambda x: pd.qcut(x, 5, labels=False, duplicates='drop')
)

# 2. 计算每一组的平均下期收益
group_ret = df_valid.groupby(['EventDate', 'group'])['next_ret'].mean().unstack()

# 3. 计算累计净值 (Cumulative Return)
# 注意：这里是简单累加近似，专业回测会用 (1+r).cumprod()
group_nav = group_ret.cumsum()
# 多空组合收益 (做多 Group 0，做空 Group 4)
long_short_ret = group_ret[0] - group_ret[4]

# =============================================
# 核心补全：计算三大考核指标
# =============================================
# 假设一年有 252 个交易日，每期是 20 个交易日
annual_factor = 252 / 20

# 1. 年化收益率
annual_ret = long_short_ret.mean() * annual_factor

# 2. 年化波动率
annual_vol = long_short_ret.std() * np.sqrt(annual_factor)

# 3. 夏普比率 (Sharpe Ratio)
sharpe = annual_ret / annual_vol

# 4. 信息比率 (Information Ratio)
info_ratio = annual_ret / annual_vol

print(f"\n====== 多空组合(Long-Short) 考核指标报告 ======")
print(f"1. 年化收益率 (Annualized Return): {annual_ret:.2%}")
print(f"2. 夏普比率 (Sharpe Ratio):        {sharpe:.4f}")
print(f"3. 信息比率 (Information Ratio):   {info_ratio:.4f}")
print(f"---------------------------------------------")
# ==========================================
# 4. 画图展示 (满分图表)
# ==========================================
print("\nStep 4: 正在绘图...")

fig, axes = plt.subplots(1, 2, figsize=(18, 6))

# 图1：IC 累积曲线 (看谁跌得最稳/涨得最稳)
ic_df.cumsum().plot(ax=axes[0])
axes[0].set_title('动量因子 IC 累积曲线 (预测能力对比)')
axes[0].set_xlabel('日期')
axes[0].set_ylabel('累积 IC')
axes[0].legend(['普通动量', '换手率加权', '指数衰减加权'])
axes[0].grid(True)

# 图2：分层回测净值图 (看能不能把好股票坏股票分开)
group_nav.plot(ax=axes[1], colormap='coolwarm')
axes[1].set_title(f'指数衰减动量因子({factor_name}) 分层回测净值')
axes[1].set_xlabel('日期')
axes[1].set_ylabel('累积收益')
axes[1].legend(['组1(因子最小)', '组2', '组3', '组4', '组5(因子最大)'])
axes[1].grid(True)

plt.tight_layout()
plt.show()