#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/题目：1、编写程序，输入一个100以内的正整数n，输入小于n的正整数p，输入n个整数并保存到一维数组。移动一维数组中的内容，要求把下标从0到p(p小于等于n－1)的数组元素平移到数组的最后，把下标从p+1的数组元素移到数组的前部。[难度等级：小学] 
int main(int argc, char *argv[]) {
	int n,p;
	int a[100];
	int b[100];
	int i=0;
	int k=0;
	printf("请输入n（数组长度）：");
	scanf("%d",&n);
	printf("请输入p（分割位置）：");
	scanf("%d",&p);
	printf("请输入n个整数");
	for(i=0;i<n;i++) {
		scanf("%d",&a[i]);
	}
	// 第一步：把原数组 a 后半截（p+1 开始到最后）搬到 b 的开头
	for(i=p+1;i<n;i++){
		b[k]=a[i];
		k++;
	}
	// 第二步：把原数组 a 前半截（0 开始到 p）搬到 b 的后面
	for(i=0;i<=p;i++){
		b[k]=a[i];
		k++;
	}
	//  输出结果 
	printf("最终结果是：");
	for(k=0;k<n;k++){
		printf("%d",b[k]);
	}
	return 0;
}
