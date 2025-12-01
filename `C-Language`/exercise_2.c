#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//2、编写程序，定义并输入一个一维整型数组a，删去一维数组中所有相同的数，使之只剩一个。数组中的数已按由小到大的顺序排列，输出删除之后的数组a。[难度等级：中学]
int main(int argc, char *argv[]) {int n, i, k = 0;
    int a[100]; // 原数组
    int b[100]; // 结果数组

    printf("请输入数组长度 n: ");
    scanf("%d", &n);

    printf("请输入 %d 个有序整数（例如 1 1 2 3 3）：", n);
    for(i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    // 1. 第一个数肯定要留下，先放进 b 数组
    if (n > 0) {
        b[0] = a[0];
        k = 1; // k 代表 b 数组里现在有几个数
    }

    // 2. 从第 2 个数开始遍历 (i=1)
    for(i = 1; i < n; i++) {
        // 如果当前这个数 a[i]，跟前一个数 a[i-1] 不一样
        if(a[i] != a[i-1]) {
            b[k] = a[i]; // 把它放进 b 数组
            k++;         // b 数组的计数加 1
        }
    }

    // === 输出结果 ===
    printf("去重后的数组：");
    for(i = 0; i < k; i++) {
        printf("%d ", b[i]);
    }
	return 0;
}
