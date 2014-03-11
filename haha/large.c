#include<stdio.h>
#include<stdlib.h>

typedef struct std{

	char		n;
	struct std	*prior;
	struct std	*next;
}Node, *lagerType;

int	anum;
int	bnum;
char	operator;

lagerType creatLink(int *n);
void showLarge(lagerType head);
void destroyLink(lagerType head);
lagerType plusLarge(lagerType Link1, lagerType Link2);
lagerType subtractionLarge(lagerType Link1, lagerType Link2);
lagerType multiplicationLarge(lagerType Link1, lagerType Link2);
void multiModefy(lagerType head);

void my_flushall(void)
{
	char	rubbish[BUFSIZ];

	setbuf(stdin, rubbish);
}
lagerType creatLink(int *n)	//存储数字
{
	lagerType      	head;
        Node            *p, *q;
	char		save;
	int		f = 0;

        q = head = (lagerType)malloc(sizeof(Node));
	q->prior = q->next = NULL, q->n = '+';
	*n = 0;
	
	my_flushall();
	while(!(save = getchar() - 48)) f = 1;	//不存储前边的0(待处理)
        if( (save == '+'-48) || (save == '-'-48) ){

                if( save != operator-48 )
                        q->n = '-';
		while(!(save = getchar() - 48)) f = 1;
        }
	else if( operator == '-')
		q->n = '-';
	while((save >= 0 && save <= 9) || f){		//创建双向循环链表

		p = (lagerType)malloc(sizeof(Node));
		p->n = save, *n += 1;
		q->next = p, p->prior = q, q = p;
		if( f )
		{	p->n = 0; break ;}
		save = getchar() - 48;
	}
	q->next = head, head->prior = q;

	return head;
}
void destroyLink(lagerType head)	//摧毁链表
{
        Node    *p = head->next;

        while(p != head){

                head->next = p->next;
		p->next->prior = head;
                free(p);
                p = head->next;
        }
        free(head);
}
void showLarge(lagerType head)		//显示数字
{
	Node	*p;

	if(head->next == head)
		printf("0");
	else if( head->n == '-')
		printf("-");
	for(p = head->next; p!=head; p = p->next)
		printf("%d", p->n);
	printf("\n");
}
lagerType plusLarge(lagerType Link1, lagerType Link2)		//两数的加法运算
{
	Node	*Link, *p = Link1->prior, *q = Link2->prior, *k, *temp;
	Node	*pf = Link1, *qf = Link2;
	int	carry = 0;

	k = Link = (lagerType)malloc(sizeof(Node));
	if(anum < bnum){

		pf = Link2, qf = Link1;
		p = Link2->prior, q = Link1->prior;
	}
	Link->prior = p;	//让新连表头的前驱指向 p（最长的链表的最后一个结点）

	while(p!=pf && q!=qf){

		p->n = p->n + q->n + carry;
		carry = p->n/10, p->n = p->n%10;	//求 本位和进位
		
		k->prior = p;
		p = p->prior;
		k->prior->next = k;
		k = k->prior;		//将新赋值的结点 p 连到新连表中

		temp = q;
		q = q->prior;
		free(temp);	//释放 q 空间
	}
	if( p==pf && carry ){		//若两个链表一样长且有进位 则再开辟一个空间存放最后的进位

			p = (lagerType)malloc(sizeof(Node));
			p->n = carry;
			k->prior = p;
			k->prior->next = k;
			k = k->prior;
	}
	else if( p!=pf ){

		p->next = k, k->prior = p, k = pf->next;	//将剩下的 p 链接到新链表中
		while( carry && p!=pf ){	//将上边产生的进位继续加

			p->n += carry;
			carry = p->n/10, p->n = p->n%10;
			p = p->prior;
		}
		if(p==pf && carry){		//进位已加到头且还有进位 则在开辟空间链接进位

			q = (lagerType)malloc(sizeof(Node));
			q->n = carry;
			p = p->next;	//让 p 指向加数中最长的链表的第一个元素
			p->prior = q;
			p->prior->next = p;
			p = p->prior;
			k = p;
		}
	}
	k->prior = Link, Link->next = k;
	free(qf), free(pf);

	return Link;
}
lagerType subtractionLarge(lagerType Link1, lagerType Link2)	//两数的减法运算
{
	Node	*Link, *p = Link1->prior, *q = Link2->prior, *k;
	Node	*pf = Link1, *qf = Link2, *temp;
	int	borrow = 0;
	char	signal = '+';

	k = Link = (lagerType)malloc(sizeof(Node)), k->next = k;
	if(anum < bnum){		//比较减数和被减数的大小（长度）

		p = Link2->prior, q = Link1->prior;
		pf = Link2, qf = Link1, signal = '-';
	}
	else if(anum == bnum){

		p = Link1->next, q = Link2->next;
		while(p!=Link1 && q!=Link2){

			if(q->n < p->n){

				p = Link1->prior, q = Link2->prior;
				break ;
			}
			else if(q->n > p->n){

				p = Link2->prior, q = Link1->prior;
				pf = Link2, qf = Link1, signal = '-';
				break ;
			}
			else{		//当减数和被减数长度一样时 比较高位的项 若两个对应相等则删除

				p->prior->next = p->next;
				p->next->prior = p->prior;
				temp = p, p = p->next, free(temp);

				q->prior->next = q->next;
				q->next->prior = q->prior;
				temp = q, q = q->next, free(temp);
			}
		}
		if( p==Link1 ){		//判断两数相等

			free(Link1), free(Link2);
			return Link;
		}
	}
	Link->n = signal;	//将符号保存到新链表头中
	borrow = 0;		//借位
	while(p!=pf && q!=qf){

		if( (p->n = p->n - q->n - borrow) < 0)
			borrow = 1, p->n = 10 + p->n;	//若借位则borrow为1 
		else
			borrow = 0;		//若无借位则borrow置为0

		p = p->prior;		//p 空间保留
		temp = q, q = q->prior, free(temp);	//释放 q
	}
	if( p!=pf && borrow)		//若减数完了还有借位 则继续借位
		while( p!=pf ){		//直到借到为止

			if( p->n ){

				p->n -= 1;
				break ;
			}
			p = p->prior;
		}
	p = pf->next;
	while( !p->n )		//删除新连表前边的0
		temp = p, p = p->next, free(temp);

	Link->next = p;
	p->prior = Link;
	pf->prior->next = Link;
	Link->prior = pf->prior;

	free(pf), free(qf);
	return Link;
}
lagerType multiplicationLarge(lagerType Link1, lagerType Link2)
{
	Node		*L1p, *L2q, *Linkp, *k, *p, *q;
	lagerType	Link;
	int		Ccarry, Jcarry, save, t;

	/*算法本质和（小学）列乘法式子一样，用乘数的每一位去乘被乘数，然后对应位相加
	  此算法是乘数乘一个就加一个 乘一个加一个

	  用L1p， L2p 分别表示两个链表的当前位置
	  用Linkp 来表示乘数当前的位置
	  用k 来表示每此乘数乘第一位被乘数是 要加的起始位置
	*/
	k = Linkp = Link = (lagerType)malloc(sizeof(Node));
	Linkp->prior = Linkp, Linkp->next = Linkp;
	if( !Link1->next->n || !Link2->next->n)		//若有一个是0 则值为0
		return Link;

	for(L1p = Link1->prior ; L1p!=Link1 ; L1p = L1p->prior, k = k->prior){

		for(Linkp=k, L2q=Link2->prior, Ccarry=0, Jcarry=0 ; L2q!=Link2 ; L2q=L2q->prior, Linkp=Linkp->prior){

			t = L1p->n * L2q->n + Ccarry;	//乘时的本位和进位
			save = t%10, Ccarry = t/10;
			
			if( Linkp->prior == Link ){	//新链表申请空间，第一个数存放到头结点中

				p = (lagerType)malloc(sizeof(Node));
				p->next = Linkp, Linkp->prior =p;
				p->prior = Link, Link->next = p;
			}
			Linkp->n += (save + Jcarry);
			Jcarry = Linkp->n/10, Linkp->n = Linkp->n%10;	//加时的本位和进位
		}
		if( (t = Ccarry+Jcarry)!=0 )	//加法和乘的进位
			Linkp->n = t;		//此时的Linkp 为空没有数据，因为第一个是从头结点开始存的
	}
	multiModefy(Link);		//处理链表将头结点中的信息 插入到最后一个结点
	if( Link1->n == Link2->n )	//符号处理
		Link->n = '+';
	else
		Link->n = '-';
	free(Link1), free(Link2);

	return Link;
}
void multiModefy(lagerType head)
{
	Node	*p = head->next;

	if( !(p->n) )
		p->next->prior = head, head->next = p->next;	//第一个结点是0 ，利用第一个结点
	else
		p = (lagerType)malloc(sizeof(Node));		//第一个结点非0 开辟一个空间

	p->next = head;
	p->prior = head->prior;
	p->prior->next = p;
	head->prior = p;

	p->n = head->n;		//交换头结点中的数据
}
lagerType inputLager(lagerType head, int *n)
{
	head = creatLink(n);
	if( head->next == head ){

		printf("您的输入有误，请重新输入:\n");
		head = inputLager(head, n);
	}
	return head;
}
void run(void)
{
	lagerType	Link1, Link2, Link;
	char	ch;

	operator = '+';
	printf("请输入第一个数：\n");
	Link1 = inputLager(Link1, &anum);
	printf("请输入运算符：\n");
	while( 1 ){

		scanf("%c", &operator);
		if( operator == '+' || operator == '-' || operator == '*')
			break ;
		printf("您输入的运算符有误请重新输入：\n");
	}
	printf("请输入第二个数：\n");
	Link2 = inputLager(Link2, &bnum);

	if( operator == '*' )
		Link = multiplicationLarge(Link1, Link2);
	else if(Link1->n == Link2->n){
	
		ch = Link1->n;
		Link = plusLarge(Link1, Link2);
		Link->n = ch;
	}
	else if(Link1->n == '+')
		Link = subtractionLarge(Link1, Link2);
	else
		Link = subtractionLarge(Link2, Link1);
	showLarge(Link);

	destroyLink(Link);
}
int main(void)
{
	while(1)
		run();
}
