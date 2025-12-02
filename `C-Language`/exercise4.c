#include <stdio.h>
#include <stdlib.h>
//编写函数double fun(double x)计算函数f(x)，定义如下： (x+1)/(x-2)  x > 0;f(x) =  0        x = 0 或者 x = 2  (x-1)/(x-2)  x < 0;在主函数输入x的值，调用fun，将计算结果输出。[难度等级：小学]

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
double fun(double x) {
    double result;
    
    if (x == 0 || x == 2) {
        result = 0;
    }
    else if (x > 0) {
        result = (x + 1) / (x - 2);
    }
    else {
        result = (x - 1) / (x - 2);
    }
    
    return result;
}
int main(int argc, char *argv[]) {
	double x, y;
    printf("请输入 x 的值: ");
    scanf("%lf", &x);
    y = fun(x);
    printf("%lf",y);
	return 0;
}
