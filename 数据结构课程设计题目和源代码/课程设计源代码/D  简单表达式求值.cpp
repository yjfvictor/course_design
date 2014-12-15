#include <cstdio>
#include <iostream>
#include <stack>
#include <cstring>
using namespace std;

int main(void)
{	
	stack <double> S;
	double temp;
	int num;
	char sign;
	double result;
	while(true)
	{
		scanf("%d",&num);
		scanf("%c",&sign);
		if(num==0 && (sign=='\n' || sign=='\r'))
			return 0;
		else if((sign=='\n' || sign=='\r'))
		{
			printf("%.2lf\n",((double)(num)));
			continue;
		}
		else
			S.push((double)num);
		temp=0;
		result=(double)0;
		for(;;)
		{
			scanf("%c",&sign);
			if(sign=='\n' || sign=='\r')
				break;
			else if(sign==' ')
				scanf("%c",&sign);
			scanf("%d",&num);
			switch(sign)
			{
			case '*':
				temp=S.top()*num;
				S.pop();
				S.push(temp);
				break;
			case '/':
				temp=S.top()/num;
				S.pop();
				S.push(temp);
				break;
			case '+':
				S.push((double)num);
				break;
			case '-':
				S.push((double)(-num));
				break;
			}
		}
		while(!S.empty())
		{
			result+=S.top();
			S.pop();
		}
		printf("%.2lf\n",result);
	}
}
