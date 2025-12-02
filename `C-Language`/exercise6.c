#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//编写函数double fun(double x[], int n)，计算并输出给定数组(长度为9)中每相邻两个元素之平均值的平方根之和。在函数main中给数组赋值，调用函数fun，并输出计算结果。[难度等级：小学]
double fun(double x[], int n){
	int i;
	double average,sum;
	sum=0.0;
	for(i=0;i<n-1;i++){
		sum += sqrt(average);
	}
	return sum;
}
int main(int argc, char *argv[]) {
	double a[9];
	int i;
	printf("请输入9个数字：\n");
	for(i=0;i<9;i++){
		scanf("%lf",&a[i]);
	}
	double result=fun(a,9);
	printf("计算结果是：%lf\n", result);
	return 0;
}
