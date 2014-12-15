#include <string>
#include <iostream>
#include <queue>

using namespace std;

class BiTree
{
public:
	BiTree()
	{
		left_child = right_child = NULL ;
	}
	~BiTree()
	{
		if(left_child)
		{
			delete left_child ;
			left_child = NULL ;
		}
		if(right_child)
		{
			delete right_child ;
			right_child = NULL ;
		}
	}
	char data;
	BiTree *left_child , *right_child ;
} ;

void CreateTree(BiTree *p, string pre , string in , int len )
{
	int i;
	string left_tree_pre, left_tree_in , right_tree_pre, right_tree_in ;
	p->data = pre[0];
	for (i = 0 ; in[i] != p->data ; i ++)
		left_tree_in += in[i] ;
	for ( i++ ; i < len ; i ++)
		right_tree_in += in[i] ;
	for (i = 1 ; i < len ; i ++)
	{
		if ( (left_tree_in).find_first_of(pre[i]) == string::npos )
			right_tree_pre += pre[i];
		else
			left_tree_pre += pre[i];
	}
	if( left_tree_pre.length() != 0 )
	{
		p->left_child = new BiTree  ;
		CreateTree ( p->left_child , left_tree_pre , left_tree_in , left_tree_pre.length() );
	}
	if( right_tree_pre.length() != 0 )
	{
		p->right_child = new BiTree ;
		CreateTree ( p->right_child , right_tree_pre , right_tree_in , right_tree_pre.length() );
	}
}

void LevelOrderTranverse(queue <BiTree *> Q)
{
	BiTree *T = NULL ;
	if (Q.empty())
		return ;
	T = Q.front();
	Q.pop();
	putchar( T->data );
	if (T != NULL )
	{
		if(T->left_child != NULL)
			Q.push( T->left_child );
		if(T->right_child !=NULL)
			Q.push( T->right_child );
	}
	LevelOrderTranverse(Q);
}

int main(void)
{
	int n , len ;
	BiTree *head ;
	string pre , in ;
	queue <BiTree *> Q;
	cin >> n;
	while (n--)
	{
		cin >> pre >> in ;
		head = new BiTree ;
		len = pre.length();
		CreateTree (head , pre , in , len);
		Q.push(head);
		LevelOrderTranverse(Q);
		putchar('\n');
		delete head ;
		head = NULL ;
		if(!(Q.empty()))
			Q.pop();
	}
	return 0;
}

