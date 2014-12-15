#include <cstdio>
#include <iostream>
#include <stack>

using namespace std;

int main(void)
{
	int i,m,n,bus[100];
	while(scanf("%d%d",&n,&m),n||m)
	{
		while(m--)
		{
			stack <int> start,St;
			bool possibility=true;
			for(i=n;i>=1;i--)
				start.push(i);
			for(i=0;i<n;i++)
				scanf("%d",&bus[i]);
			for(i=0;i<n;)
			{
				if(possibility)
				{
					if(!start.empty())
					{
						if(start.top()==bus[i])
						{
							i++;
							start.pop();
						}
						else
						{
							if(!St.empty())
							{
								if(St.top()==bus[i])
								{
									i++;
									St.pop();
								}
								else
								{
									St.push(start.top());
									start.pop();
								}
							}
							else
							{
								St.push(start.top());
								start.pop();
							}
						}
					}
					else
					{
						if(!St.empty())
						{
							if(St.top()==bus[i])
							{
								i++;
								St.pop();
							}
							else
								possibility=false;
						}
						else
							possibility=false;
					}
				}
				else
					break;
			}
			if(possibility)
				puts("YES");
			else
				puts("NO");
		}
	}
	return 0;
}
