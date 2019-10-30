#include <stdlib.h> 
#include <stdio.h>

 typedef struct PolyNode *Polynomial;
 struct PolyNode {
     int coef;
     int expon;
     Polynomial link;
 };
 
void Attach(int c,int e, Polynomial * pRear);
Polynomial ReadPoly();
Polynomial Add(Polynomial P1,Polynomial P2);
Polynomial Mult(Polynomial P1,Polynomial P2);
void PrintPoly( Polynomial P );

int main(){
	Polynomial P1,P2,PP,PS;
	P1=ReadPoly();
	P2=ReadPoly();
	PP=Mult(P1,P2);
	PrintPoly(PP);
	PS=Add(P1,P2);
	PrintPoly(PS);
    return 0;
}

void Attach(int c,int e,Polynomial * pRear)
{//在传入的链表后面再加一个链表 
	Polynomial temp;
	temp=(Polynomial)malloc(sizeof(struct PolyNode));
	temp->coef=c;
	temp->expon=e;
	temp->link=(*pRear)->link;
	(*pRear)->link=temp;
	(*pRear)=temp;
}
Polynomial ReadPoly()	//输入数字，转化为链表 
{
	Polynomial P,Rear,first;
	int N,c,e;
	
	P=(Polynomial)malloc(sizeof( struct PolyNode ));	//申请头结点
	P->link=NULL;
	Rear=P;
	scanf("%d",&N);
	
	while(N--)
	{
		scanf("%d %d",&c,&e);
		Attach(c,e,&Rear);
	}
	
	first=P;	//三行代码，free掉头结点
	P=P->link;
	free(first);
	return P;
}
 
 
Polynomial Add(Polynomial P1,Polynomial P2)	//两个链表的相加 
{
	Polynomial temp,temp1,temp2,P;
	temp1=P1;
	temp2=P2;
	P=(Polynomial)malloc(sizeof( struct PolyNode));
	P->link=NULL;
	temp=P;
	while(temp1&&temp2)	//当两个链表都不为NULL时才要做下面的循环和判断。
	{
		if(temp1->expon>temp2->expon)
		{
			Attach(temp1->coef,temp1->expon,&temp);
			temp1=temp1->link;
		}else if(temp1->expon<temp2->expon){
			Attach(temp2->coef,temp2->expon,&temp);
			temp2=temp2->link;
		}else{		//两个多项式的expon相等时
			if(!(temp1->coef+temp2->coef)==0)
			{
		        Attach(temp1->coef+temp2->coef,temp1->expon,&temp);				
				temp1=temp1->link;
				temp2=temp2->link;
			}else{		//expon相等，coef互为相反数
				temp1=temp1->link;
				temp2=temp2->link;
			}
		}
	}
	for(;temp1;temp1=temp1->link)		//当有一个指针指向NULL时，说明这条多项式已经加完了。此时只要把另一条多项式剩下的全Attach到P后边就行了
	{
		Attach(temp1->coef,temp1->expon,&temp);
	}
	for(;temp2;temp2=temp2->link)
	{
		Attach(temp2->coef,temp2->expon,&temp);
	}
	temp=P;
	P=P->link;
	free(temp);
	return P;	
}
Polynomial Mult(Polynomial P1,Polynomial P2)	//两个链表的相乘 
{
	Polynomial P,Rear,t1,t2,t;
	int c,e;
	
	if(!P1||!P2)return NULL;	//判断两个多项式都不为零多项式
	
	t1=P1;
	t2=P2;
	P=(Polynomial)malloc(sizeof( struct PolyNode ));
	P->link=NULL;
	Rear=P;
	while(t2)		//初始多项式由P1的第一项乘以P2的每一项得到
	{
		Attach(t1->coef*t2->coef,t1->expon+t2->expon,&Rear);
		t2=t2->link;
    	}
    t1=t1->link;		//t1指针指向P1的第二项
	while(t1)		
	{
		t2=P2;
		Rear=P;	//每一次的t1指向的多项式乘以t2的每一项后，Rear都重新指回P的头结点，以便下一次得到的t1和t2的乘积插入P
		while(t2)
		{
			c=t1->coef*t2->coef;
			e=t1->expon+t2->expon;
			while(Rear->link&&Rear->link->expon>e)	//当Rear的下一项不为空且下一项的指数比当前的乘积e大时，Rear后移
			{									//为什么e不对比Rear指向的当前项的指数？
				Rear=Rear->link;					//因为是单链表，如果把当前的多项式插入Rear，那么当先多项式无法和上一项相连接
			}
			if(Rear->link&&Rear->link->expon==e)	//指数相等的情况
			{
				if(Rear->link->coef+c)				//系数相加不为零
				{
					Rear->link->coef+=c;
				}else{							//系数相加为0，是零多项式
					Rear->link->coef=0;
					Rear->link->expon=0;
				}
			}else{								//当前多项式的指数大于Rear的下一项指数
				t=(Polynomial)malloc(sizeof(struct PolyNode));
				t->coef=c;
				t->expon=e;
				t->link=Rear->link;
				Rear->link=t;
				Rear=Rear->link;
			}			
			t2=t2->link;
		}		
		t1=t1->link;
	}	
	Rear=P;
	P=P->link;
	free(Rear);
	return P;
}
void PrintPoly( Polynomial P ){
	int flag = 0;
	if (!P){printf("0 0\n"); return;}

	while(P){
		if (!flag)
			flag = 1;
		else
			printf(" ");
		printf("%d %d", P->coef, P->expon );
		P = P->link;
	}
	printf("\n");
}




