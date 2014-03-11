#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TURE	1
#define FALSE	0

typedef struct StackType1
{
	double			opnd;
	struct StackType1	*next;	
}OPNDType;		//存储运算数
typedef struct StackType2
{
	char			optr;
	struct StackType2	*next;	
}OPTRType;		//存储运算符

void makeStack(OPNDType *top1, OPTRType *top2);
void PushStack1(OPNDType *top, double x);
void PushStack2(OPTRType *top, char x);
void PopStack2(OPTRType *top, char *operator);
void PopStack1(OPNDType *top, double *data);
char GetTop(OPTRType *top2);
int decide(char ch);
char Precede(char ch1, char ch2);
double Operate(double a, char operator, double b);
void result(OPNDType *top);
void strrev(char * str);
void destroyLink(OPNDType *top1, OPTRType *top2);

void makeStack(OPNDType *top1, OPTRType *top2)
{
	OPNDType	*Np, *Nq;
	OPTRType	*Tp, *Tq;
	char		ch, operator;
	char		save[20] = {0};
	int		i, f, k = 0, k1;
	double		a, b;

	PushStack2(top2, '#');		//先给运算栈低存入 # 起始标识符
	ch = getchar();
	while( 1 ){

		if( !decide(ch) )	//若 非运算符运算数 则转换成 # 结束标识符
			ch = '#';

		i = 0, f = 0, k1 = 0;	//i和f辅助存入 n 位数字 k1 辅助存入负数

		if( (ch >= '0' && ch <= '9') || ch == '.')	f = 1;
		if( (k == '#' || k == '(') && !f && ch == '-'){		//判断减号是否为负号

			ch = getchar(), k1 = 1;
			if( ch >= '0' && ch <= '9' )	f = 1;
		}
		while( (ch >= '0' && ch <= '9') || ch == '.')
			save[i++] = ch, ch = getchar();		//将字符型数字存到数组中

		if( f ){

			save[i] = '\0';
			if( k1 )
				PushStack1(top1, atof(save)*-1);	//将字符串转换成双精度
			else
				PushStack1(top1, atof(save));
			continue ;
		}
		k = ch;			//辅助存入负数
		switch(Precede(GetTop(top2), ch)){

			case 1 : return ;	//运算完毕
			case '<' :
				PushStack2(top2, ch);	ch = getchar();	break;	//进栈继续接收
			case '=' :
				PopStack2(top2, &operator);	ch = getchar();	break;	//出栈继续接收
			case '>' :			//运算 不接收
				PopStack2(top2, &operator);
				PopStack1(top1, &a), PopStack1(top1, &b);
				PushStack1(top1, Operate(b, operator, a));
				break ;
		}
		if( ch == '#' && !top2->next)
			return ;
	}
}
void PushStack1(OPNDType *top, double x)
{
	OPNDType	*p;

	p = (OPNDType *)malloc(sizeof(OPNDType));
	p->opnd = x;
	p->next = top->next;
	top->next = p;
}
void PushStack2(OPTRType *top, char x)
{
	OPTRType	*p;

	p = (OPTRType *)malloc(sizeof(OPTRType));
	p->optr = x;
	p->next = top->next;
	top->next = p;
}
void PopStack2(OPTRType *top, char *operator)
{
	OPTRType	*temp;

	temp = top->next;
	top->next = temp->next;
	*operator = temp->optr;
	free(temp);
}
void PopStack1(OPNDType *top, double *data)
{
	OPNDType	*temp;

	temp = top->next;
	top->next = temp->next;
	*data = temp->opnd;
	free(temp);
}
char GetTop(OPTRType *top2)
{
	return top2->next->optr;
}
int decide(char ch)
{
	if((ch>='0' && ch<='9') || ch=='(' || ch==')' || ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='#')
		return TURE;
	return FALSE;
}
char Precede(char ch1, char ch2)	//比较两算符优先级
{
	if(ch1 == '(' && ch2 == ')')
		return '=';
	else if( ch1 == '#' && ch2 == '#')
		return 1;
	else if( ch1 == '#' || ch2 == '(' || ch1 == '(' || ((ch1 == '+' || ch1 == '-') && (ch2 == '*' || ch2 == '/')))
		return '<';
	else
		return '>';
}
double Operate(double a, char operator, double b)
{
	switch(operator){

		case '+' :	return a+b;
		case '-' :	return a-b;
		case '*' :	return a*b;
		case '/' :
			if( b )
				return a/b;

			printf("除0错！\n");
			exit(1);
	}
}
void destroyLink(OPNDType *top1, OPTRType *top2)
{
	OPNDType	*p;
	OPTRType	*q;

	p = top1->next;
	while( p ){

		top1->next = p->next;
		free(p);
		p = top1->next;
	}
	q = top2->next;
	while( q ){

		top2->next = q->next;
		free(q);
		q = top2->next;
	}
	free(top1), free(top2);
}
void strrev(char * str)		//倒置字符串
{
	int i, l = strlen(str)-1;
	char ch;

	for(i=0; i <= l/2; i++)
	{
		ch = str[i];
		str[i] = str[l-i];
		str[l-i] = ch;
	}	
}
void result(OPNDType *top)
{
	char	buf[20], i, k = 0;

	sprintf(buf, "%lf", top->next->opnd);
	strrev(buf);
	while( buf[k]== '0' )	k++;
	if( buf[k]=='.' )
		k++;
	for(i = k; buf[i]; i++)
		buf[i-k] = buf[i];
	buf[i-k] = '\0';
	strrev(buf);
	printf("= ");
	puts(buf);
}
int main(void)
{
	OPNDType	*top1;
	OPTRType	*top2;

	top1 = (OPNDType *)malloc(sizeof(OPNDType));
	top2 = (OPTRType *)malloc(sizeof(OPTRType));
	
	printf("请输入：\n");
	makeStack(top1, top2);
	result(top1);

	destroyLink(top1, top2);
	return FALSE;
}
