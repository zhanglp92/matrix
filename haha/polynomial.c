#include<stdio.h>
#include<stdlib.h>

typedef struct polynomial{

	int	exp;
	int	xishu;
	struct polynomial *next;
}Node, *polynomial;

polynomial creatPolynomial(void);
void destroyLink(polynomial head);
polynomial polynomialAdd(polynomial Link1, polynomial Link2);

polynomial creatPolynomial(void)	//创建单链表存储多项式
{
	polynomial	head;
	Node		*p, *q, save = {0};
	int		i = 0;

	head = (polynomial)malloc(sizeof(Node));
	head->next = NULL, q = head;
	printf("请输入多项式的系数和指数（以系数为0结束）：\n");
	printf("请输入第%d项：", ++i);
	scanf("%d", &save.xishu);
	while(save.xishu){

		scanf("%d", &save.exp);
		p = (polynomial)malloc(sizeof(Node));
		*p = save;
		q->next = p;
		q = p;
		printf("请输入第%d项：", ++i);
		scanf("%d", &save.xishu);
	}
	return head;
}
void sortPolnomial(polynomial head)	//给多项式按 升幂排序  并且合并同类项
{
	Node	*p, *q, temp, *s;

	for(p = head->next; p; p = p->next)
		for(q = p->next; q; q = q->next)
			if(p->exp > q->exp){

				temp = *p, *p = *q, *q = temp;
				temp.next = p->next;
				p->next = q->next;
				q->next = temp.next;
			}
	for(q = head, p = head->next; p && p->next; )
		if(p->exp == p->next->exp){	//前后两项指数相同

			p->xishu += p->next->xishu;
			if(!p->xishu){		//合并前后两项系数和为0的

				q->next = p->next->next;
				s = p, p = p->next, free(s);
				s = p, p = p->next, free(s);
				p = q->next;
			}
			else{

				s = p->next;
				p->next = p->next->next;
				free(s);
			}
		}
		else
			p = p->next, q = q->next;
}
void destroyLink(polynomial head)
{
	Node	*p = head->next;

	while(p){

		head->next = p->next;
		free(p);
		p = head->next;
	}
	free(head);
}
polynomial polynomialAdd(polynomial Link1, polynomial Link2)
{
	Node		*p = Link1->next, *q = Link2->next, *temp;
	polynomial	Link = Link1;

	free(Link2);
	while(p && q){

		if(p->exp < q->exp){

			Link = Link->next = p;
			p = p->next;
		}
		else if(p->exp > q->exp){

			Link = Link->next = q;
			q = q->next;
		}
		else{

			if((p->xishu += q->xishu)){

				Link = Link->next = p;
				p = p->next;
				temp = q;
				q = q->next;
				free(temp);
			}
			else
				p = p->next, q = q->next;
		}
	}
	if( !p )
		p = q;
	Link->next = p;

	return Link1;
}
void showPolnomial(polynomial head)
{
	Node	*p = head->next;

	if( !p ){

		printf("0\n");
		return ;
	}
	for(p = head->next; p->next; p = p->next)
		printf("%dX^%d + ", p->xishu, p->exp);
	printf("%dX^%d\n", p->xishu, p->exp);
}
int main(void)
{
	polynomial	Link1, Link2, Link;

	Link1 = creatPolynomial();
	sortPolnomial(Link1);
	printf("多项式1：\n");
	showPolnomial(Link1);
	Link2 = creatPolynomial();
	sortPolnomial(Link2);
	printf("多项式2：\n");
	showPolnomial(Link2);
	printf("多项式和：\n");
	Link = polynomialAdd(Link1, Link2);
	showPolnomial(Link);

	destroyLink(Link);
	return 0;
}
