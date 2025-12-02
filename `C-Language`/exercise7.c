#include <stdio.h>
#include <stdlib.h>
//一个升级版的数独小游戏 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char *argv[]) {
	
    int grid[3][3] = {
        {1, 3, 2},
        {2, 1, 3},
        {3, 2, 1}
    };   
    int i, j;
    printf("填好的方框如下：\n");
    
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            printf("%d  ", grid[i][j]);
        }
        printf("\n"); 
    }
	return 0;
}
