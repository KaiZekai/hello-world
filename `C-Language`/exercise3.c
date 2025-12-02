#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//编写程序，定义一个3×3的整型二维数组，并输入其中的9个值。使数组左下半三角元素中的值全部置成0，然后输出该二维数组。[难度等级：小学] 
int main(int argc, char *argv[]) {
	// 1. 定义一个 3x3 的二维数组
    int a[3][3];
    int i, j; // i用来代表行，j用来代表列

    // 2. 输入环节：用双重循环填满 9 个格子
    printf("请输入 9 个整数（用来填充 3x3 矩阵）：\n");
    for(i = 0; i < 3; i++) {       // 外层循环控制行 (0到2)
        for(j = 0; j < 3; j++) {   // 内层循环控制列 (0到2)
            scanf("%d", &a[i][j]);
        }
    }

    // 3. 核心逻辑：把左下角变成 0
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            // 如果 行号 > 列号，说明这个格子在左下角
            if(i > j) {
                a[i][j] = 0;
            }
        }
    }

    // 4. 输出环节：把处理后的矩阵打印出来
    printf("置零后的矩阵结果：\n");
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            printf("%d ", a[i][j]); 
        }
        printf("\n"); 
    }
	return 0;
}
