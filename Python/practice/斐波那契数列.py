def f_iterative(n):
    if n == 1 or n == 2:
        return 1

    # 初始化前两个数
    a, b = 1, 1

    # 从第3个开始算，一直算到第n个
    for _ in range(3, n + 1):
        # 新的数是前两个数之和
        # 更新逻辑：a变成旧的b，b变成旧的a+b
        a, b = b, a + b

    return b

print(f_iterative(1000))