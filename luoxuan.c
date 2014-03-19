/*************************************************************************
	> File Name: luoxuan.c
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2014年03月19日 星期三 22时09分31秒
 ************************************************************************/

#include <stdio.h>

#define MAX_M   7
#define M_half  3 // MAX_M/2 


void create_matrix (int a[MAX_M][MAX_M])
{
    int     i, j;
    int     k, col;


    i = j = M_half;
    for (k = 1, col = M_half+1; col < MAX_M; col++) {

        for ( ; j < col; j++) 
            a[i][j] = k++;

        for ( ; i < col; i++) 
            a[i][j] = k++;

        for ( ; j > (2*M_half-col); j--) 
            a[i][j] = k++;

        for ( ; i > (2*M_half-col); i--)
            a[i][j] = k++;
    }

    for ( ; j < col; j++) 
        a[i][j] = k++;


}

int main (void)
{
    int     a[MAX_M][MAX_M];
    int     i, j;

    create_matrix (a);
    for (i = 0; i < MAX_M; i++) {
        for (j = 0; j < MAX_M; j++) 
            printf ("%-4d", a[i][j]);
        printf ("\n\n");
    }

    return 0;
}
