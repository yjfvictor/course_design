#include <stdio.h>

int main(void)
{
	int i,j,k,n,a[50000],b,c[50000];
	while(scanf("%d",&n),n)
	{
		for(i=0;i<n;i++)
			scanf("%d",&a[i]);
		c[0]=j=0;
		k=1;
		for(i=0;i<n;i++)
		{
			scanf("%d",&b);
			for(;j<n && a[j]<=b;j++)
			{
				if(a[j]==b)
				{
					c[k++]=b;
					c[0]++;
					break;
				}
			}
		}
		printf("%d",c[0]);
		for(i=1;i<=c[0];i++)
			printf(" %d",c[i]);
		putchar('\n');
	}
	return 0;
}
