#include<stdio.h>
#include<stdlib.h>

#define	NN	10	//10 表示 8*8

int	N;

typedef struct CHESS{

	int	pos;
	char	num;
}chessType[NN][NN];

chessType	chess;

typedef struct STACK{

	int	i;
	int	j;
	struct STACK	*next;
}LinkStack;

void PushStack(LinkStack *top, int i, int j);
void PopStack(LinkStack *top, int *i, int *j);
void destroyLink(LinkStack *top);

void PushStack(LinkStack *top, int i, int j)
{
	LinkStack	*p;

	p = (LinkStack *)malloc(sizeof(LinkStack));
	p->i = i, p->j = j;
	p->next = top->next;
	top->next = p;
}
void PopStack(LinkStack *top, int *i, int *j)
{
	LinkStack	*p = top->next;

	chess[p->i][p->j].num = 0, chess[p->i][p->j].pos = 0;

	top->next = p->next;
	free(p);
	*i = top->next->i, *j = top->next->j;
}
void destroyLink(LinkStack *top)
{
	LinkStack	*p;

	p = top->next;
	while( p ){

		top->next = p->next;
		free(p);
		p = p->next;
	}
	free(top);
}

void printChess(void);
void initChess(void);
void stepHorse(int *i, int *j);
void horseChess(int starti, int startj, LinkStack *StackTop);

void horseChess(int starti, int startj, LinkStack *StackTop)
{
	int	k = 1, i = starti, j = startj;

	chess[i][j].num = k++;
	PushStack(StackTop, i, j);
	while( k <= (N-2)*(N-2) ){

		stepHorse(&i, &j);
		if( i == 0 && j == 0){

			if( chess[starti][startj].pos == 8 ){

				printf("起点为(%d,%d)时，马不能全部走完所有的格子！\n", starti, startj);
				return ;
			}
			PopStack(StackTop, &i, &j), k--;
			continue ;
		}
		chess[i][j].num = k++;
		PushStack(StackTop, i, j);
	}
	printf("共%d步\n", k-1);
	printChess();
	printf("起点(%d,%d)终点(%d,%d)\n", starti, startj, StackTop->next->i, StackTop->next->j);
}
void stepHorse(int *i, int *j)
{

	switch( chess[*i][*j].pos ){

		case 0 :
			if( (*i+1 > 0 && *i+1 < N-1) && (*j+2 > 0 && *j+2 < N-1) && chess[*i+1][*j+2].num == 0 ){

				chess[*i][*j].pos = 1;
				*i = *i + 1, *j = *j + 2;	break;
			}
		case 1 :
			if( (*i+2 > 0 && *i+2 < N-1) && (*j+1 > 0 && *j+1 < N-1) && chess[*i+2][*j+1].num == 0 ){

				chess[*i][*j].pos = 2;
				*i = *i + 2, *j = *j + 1;	break;
			}
		case 2 :
			if( (*i+2 > 0 && *i+2 < N-1) && (*j-1 > 0 && *j-1 < N-1) && chess[*i+2][*j-1].num == 0 ){

				chess[*i][*j].pos = 3;
				*i = *i + 2, *j = *j - 1;	break;
			}
		case 3 :
			if( (*i+1 > 0 && *i+1 < N-1) && (*j-2 > 0 && *j-2 < N-1) && chess[*i+1][*j-2].num == 0 ){

				chess[*i][*j].pos = 4;
				*i = *i + 1, *j = *j - 2;	break;
			}
		case 4 :
			if( (*i-1 > 0 && *i-1 < N-1) && (*j-2 > 0 && *j-2 < N-1) && chess[*i-1][*j-2].num == 0 ){

				chess[*i][*j].pos = 5;
				*i = *i - 1, *j = *j - 2;	break;
			}
		case 5 :
			if( (*i-2 > 0 && *i-2 < N-1) && (*j-1 > 0 && *j-1 < N-1) && chess[*i-2][*j-1].num == 0 ){

				chess[*i][*j].pos = 6;
				*i = *i - 2, *j = *j - 1;	break;
			}
		case 6 :
			if( (*i-2 > 0 && *i-2 < N-1) && (*j+1 > 0 && *j+1 < N-1) && chess[*i-2][*j+1].num == 0 ){

				chess[*i][*j].pos = 7;
				*i = *i - 2, *j = *j + 1;	break;
			}
		case 7 :
			if( (*i-1 > 0 && *i-1 < N-1) && (*j+2 > 0 && *j+2 < N-1) && chess[*i-1][*j+2].num == 0 ){

				chess[*i][*j].pos = 8;
				*i = *i - 1, *j = *j + 2;	break;
			}
		default :
			chess[*i][*j].pos = 8;
			*i = *j = 0;	break;
	}

}
void initChess(void)
{
	int	i, j;

	for(i = 0; i<N; i++){

		for(j = 1; i>0 && j<N-1 && i<N-1; j++)
			chess[i][j].num = 0, chess[i][j].pos = 0;

		chess[0][i].num = chess[N-1][i].num = 'X';
		chess[i][0].num = chess[i][N-1].num = 'X';
	}
}
void printChess(void)
{
	int	i, j;

	for(j = 0; j<N; j++)
		printf("%-4c", chess[0][j].num);
	printf("\n\n");
	for(i = 1; i<N-1; i++){

		printf("%-4c", chess[i][0].num);
		for(j = 1; j<N-1; j++)
			printf("%-4d", chess[i][j].num);
		printf("%-4c\n\n", chess[i][N-1].num);
	}
	for(j = 0; j<N; j++)
		printf("%-4c", chess[N-1][j].num);
	printf("\n");
}
int run(int starti, int startj)
{
	LinkStack	*StackTop;

	StackTop = (LinkStack *)malloc(sizeof(LinkStack));
	initChess();
	horseChess(starti, startj, StackTop);
	destroyLink(StackTop);
}
void inputStart(int *i, int *j)
{
	printf("请输入马的起始位置（如（3,4））：");
	scanf("%d,%d", i, j);

	while( 1 ){

		if( (*i>0 && *i<N-1) && (*j>0 && *j<N-1) )
			return ;
		printf("您输入的有误，请重新输入：\n");
		scanf("%d,%d", i, j);
	}
	
}
int main(void)
{
	int	starti, startj;

	printf("请输入棋盘的格数如（5*5 输入5）\n");
	scanf("%d", &N);
	N += 2;
	inputStart(&starti, &startj);
	run(starti, startj);

	return 0;
}
