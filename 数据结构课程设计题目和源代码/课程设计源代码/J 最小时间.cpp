#include <string>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>

using namespace std ;

int city[101][101];
int dis[101];

class linklist
{
public:
	linklist()
	{
		next = NULL ;
	}
	int data ;
	linklist * next ;
} ;

linklist *head ;

inline bool Search (int n)
{
	linklist *p = head ;
	while ( p != NULL )
	{
		if (p->data == n)
			return true ;
		p = p->next ;
	}
	return false ;
}

inline void clean(linklist *&head)
{
	linklist *p = head ;
	linklist *q = NULL ;
	while ( p != NULL )
	{
		q = p->next ;
		delete p;
		p = q ;
	}
}

int main(void)
{
	int n;
	int i , j ;
	int iMin , shortest , current , iTemp , cur_shortest ;
	string temp;
	linklist *p ;
	while ( cin >> n )
	{
		memset ( city , 0 , sizeof (city) ) ;
		memset ( dis , 0 , sizeof(dis) );
		for ( i = 2 ; i <= n ; i ++ )
		{
			for ( j = 1 ; j < i ; j ++ )
			{
				cin >> temp ;
				if ( temp == "x" )
					city[j][i] = city[i][j] = INT_MAX ;
				else
					city[j][i] = city[i][j] = atoi( temp.c_str() );
			}
		}
		head = new linklist ;
		head->data = 1;
		iMin = INT_MAX ;
		j = 1 ;
		for ( j = 2 ; j <= n ; j ++ )
		{
			if ( (dis[j] = city[1][j]) < iMin )
			{
				iMin = dis[j];
				shortest = j ;
			}
		}
		p = head->next = new linklist ;
		p->data = shortest ;
		current = iMin ;
		iMin = INT_MAX ;
		cur_shortest = shortest ;
		for( i = 2 ; i < n ; i ++ )
		{
			for ( j = 2 ; j <= n ; j ++ )
			{
				if ( Search (j) )
					continue ;
				if ( ( iTemp = current + city[cur_shortest][j] ) < dis[j] && iTemp >0 )
					dis[j] = iTemp;
				if ( dis[j] < iMin )
				{
					iMin = dis[j];
					shortest = j ;
				}
			}
			current = iMin ;
			cur_shortest = shortest ;
			iMin = INT_MAX ;
			p->next = new linklist ;
			p = p->next ;
			p->data = shortest ;
		}
		clean(head);
		cout << current << endl ;
	}
	return 0;
}
