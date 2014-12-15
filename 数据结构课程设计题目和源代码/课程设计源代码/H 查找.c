#include <stdio.h>
#include <stdlib.h>


int compare(const void *a, const void *b)
{
	return *(const int *)a-*(const int *)b;
}

int a[100000],b;

int main(void)
{
	int i,n,m,possibility,left,right,middle;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		for(i=0;i<n;i++)
			scanf("%d",&a[i]);
		qsort(a,n,sizeof(a[0]),compare);
		for(i=0;i<m;i++)
		{
			possibility=1;
			left=0;
			right=n-1;
			scanf("%d",&b);
			if(a[left]!=b && a[right]!=b)
			{
				for(;;)
				{
					if(right-left<=1)
					{
						possibility=0;
						break;
					}
					middle=(left+right)/2;
					if(a[middle]==b)
						break;
					else if(a[middle]<b)
						left=middle;
					else
						right=middle;
				}
			}
			if(possibility)
				puts("yes");
			else
				puts("no");
		}
		
	}
	return 0;
}
