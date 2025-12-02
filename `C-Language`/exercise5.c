#include <stdio.h>
#include <stdlib.h>
//编写函数double fun(int n)，其功能是：计算并输出下列多项式值：s=1+1/(1+2)+1/(1+2+3)+..1/(1+2+3…+n)在函数main中输入正整数n，调用函数fun，最后，输出计算结果。[难度等级：小学]
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
double fun(int n){
	double s=0.0;
	int t = 0;
	int i;
	for(i=1;i<=n;i++){
		t += i;
		s += 1.0 / t;
	}
	return s;
} 
int main(int argc, char *argv[]) {
	int n;
    printf("请输入 n 的值：");
    scanf("%d", &n);
    double result = fun(n);
    printf("计算结果是：%lf\n", result);
	return 0;
}
