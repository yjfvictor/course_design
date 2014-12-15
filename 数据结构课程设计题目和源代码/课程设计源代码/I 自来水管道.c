#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int road[51][51];
typedef struct TREE
{
	int point;
	struct TREE *next;
} TREE;

int i,j,P,R;
int a,b,price,min;
TREE *head=NULL;

TREE *clean(TREE *head)
{
	TREE *p,*q=NULL;
	p=head;
	while(p!=NULL)
	{
		q=p->next;
		free(p);
		p=q;
	}
	return NULL;
}

TREE *Search(TREE *head,int n)
{
	TREE *p=head;
	while(p!=NULL)
	{
		if(p->point==n)
			return p;
		p=p->next;
	}
	return NULL;
}

int length(TREE *head)
{
	TREE *p=head;
	int i=0;
	while(p!=NULL)
	{
		i++;
		p=p->next;
	}
	return i;
}

int main(void)
{
	TREE *p,*current;
	int cur;
	while(scanf("%d%d",&P,&R),P)
	{
		if(P==1)
		{
			for(i=0;i<R;i++)
			{
				scanf("%d%d%d",&a,&b,&price);
			}
			puts("0");
		}
		else
		{
			for(i=0;i<R;i++)
			{
				memset(road,0,sizeof(road));
				for(i=0;i<R;i++)
				{
					scanf("%d%d%d",&a,&b,&price);
					if(road[a][b] == 0 || road[a][b] > price)
					{
						road[a][b] = price;
						road[b][a] = price;
					}
				}
				current=head=(TREE *)malloc(sizeof(TREE));
				head->point=1;
				head->next=NULL;
				price=0;
				while(length(head)<P)
				{
					p=head;
					min=101;
					while(p!=NULL)
					{
						for(j=1;j<=P;j++)
						{
							if(Search(head,j)==NULL)
							{
								if(road[p->point][j]!=0 && road[p->point][j]<min)
								{
									min=road[p->point][j];
									cur=j;
								}
							}
						}
						p=p->next;
					}
					current->next=(TREE *)malloc(sizeof(TREE));
					current=current->next;
					current->point =cur;
					current->next=NULL;
					price+=min;
				}
				printf("%d\n",price);
				head=clean(head);
			}
		}
	}
	return 0;
}
