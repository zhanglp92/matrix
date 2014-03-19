/*************************************************************************
	> File Name: luoxuan.c
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2014年03月19日 星期三 22时09分31秒
 ************************************************************************/

#include <stdio.h>

#define MAX_M   7 
#define M_half  (MAX_M >> 1) 

// 取矩阵的元素 等价与 a[i][j]
#define element(a, i, j, n) \
    a[i*n +j]

// 创建矩阵
void create_matrix (int *a, int n) 
{ 
    int     i, j; 
    int     k, col; 

    i = j = M_half; 
    for (k = 1, col = M_half+1; col < MAX_M; col++) { 

        // 给上边的行赋值
        for ( ; j < col; j++) 
            element (a, i, j, n) = k++;

        // 给右边的列赋值
        for ( ; i < col; i++) 
            element (a, i, j, n) = k++;

        // 给下边的行赋值
        for ( ; j > (2*M_half-col); j--) 
            element (a, i, j, n) = k++;

        // 给左边的列赋值
        for ( ; i > (2*M_half-col); i--)
            element (a, i, j, n) = k++;
    }
    // 给上边的最后一行赋值（即第一行）
    for ( ; j < col; j++) 
            element (a, i, j, n) = k++;
}


void print_matrix (const int *a, int n)
{
    int     i, j;

    for (i = 0; i < MAX_M; i++) {
        for (j = 0; j < MAX_M; j++) 
            printf ("%-4d", element (a, i, j, n));
        printf ("\n\n");
    }
}

int main (void)
{
    int     a[MAX_M * MAX_M];

    create_matrix (a, MAX_M);
    print_matrix (a, MAX_M);

    return 0;
}
