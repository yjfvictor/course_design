#include <cstdio>
#include <cstring>

class BiNode
{
public:
	BiNode()
	{
		left_child = right_child = NULL ;
	}
	~BiNode()
	{
		if ( left_child != NULL )
		{
			delete left_child ;
			left_child = NULL ;
		}
		if ( right_child != NULL )
		{
			delete right_child ;
			right_child = NULL ;
		}
	}
	int digit ;
	BiNode * left_child , * right_child ;
} ;

typedef BiNode *BiTree ;

bool SearchBST (BiTree T , int data , BiTree f , BiTree &p)
{
	if(!T)
	{
		p = f ;
		return false ;
	}
	else if ( data == T->digit )
	{
		p = T ;
		return true ;
	}
	else if ( data < T->digit )
		return SearchBST ( T->left_child , data , T , p );
	else
		return SearchBST ( T->right_child , data , T , p );
}

inline bool InsertBST ( BiTree &T , int data )
{
	BiTree p = NULL , s = NULL ;
	if( SearchBST (T, data , NULL , p ) )
		return false ;
	else
	{
		s = new BiNode ;
		s->digit = data ;
		if ( p == NULL )
			T = s  ;
		else if ( data < p->digit )
			p->left_child = s ;
		else
			p->right_child = s ;
		return true ;
	}
}

bool identical ( BiTree p , BiTree q )
{
	if ( p == NULL && q == NULL )
		return true ;
	else if (p == NULL )
		return false ;
	else if (q == NULL )
		return false ;
	else if ( p->digit != q->digit )
		return false ;
	else
		return ( identical ( p->left_child , q->left_child ) && identical ( p->right_child , q->right_child ) );
}

int main(void)
{
	int i , n ;
	char input[15] ;
	BiTree control_group = NULL ;	// 对照组
	BiTree experimental_group = NULL ;	// 实验组
	while ( scanf ( "%d" , &n ) , n )
	{
		scanf ( "%s" , input ) ;
		for ( i = 0 ; input [i] != '\0' ; i ++ )
			InsertBST ( control_group , input[i] );
		while ( n -- )
		{
			scanf ( "%s" , input ) ;
			for ( i = 0 ; input [i] != '\0' ; i ++ )
				InsertBST ( experimental_group , input[i] ) ;
			if ( identical ( control_group , experimental_group ) )
				puts ( "YES" ) ;
			else
				puts ( "NO" ) ;
			if ( experimental_group != NULL )
			{
				delete experimental_group ;
				experimental_group = NULL ;
			}
		}
		if ( control_group != NULL )
		{
			delete control_group ;
			control_group = NULL ;
		}
	}
	return 0 ;
}
