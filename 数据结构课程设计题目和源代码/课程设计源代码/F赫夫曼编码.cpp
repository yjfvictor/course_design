#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std ;

typedef struct
{
	int frequency ;
	string letter ;
} LETTER ;

LETTER letter [27];
int code_length[27] ;
int frequency[27];

inline void initialize ( void )
{
	int i ;
	memset ( code_length , 0 , sizeof (code_length) ) ;
	memset ( frequency , 0 , sizeof (frequency) ) ;
	letter[0].frequency = 0;
	letter[0].letter = '_' ;
	for ( i = 0 ; i < 27 ; i ++ )
	{
		letter[i].frequency = 0;
		letter[i].letter = ((char)( i + 'A' - 1 )) ;
	}
}

inline void statistics ( char c )
{
	if ( c == '_' )
	{
		letter[0].frequency ++ ;
		frequency[0] ++ ;
	}
	else
	{
		letter[c - 'A' + 1].frequency ++ ;
		frequency[c - 'A' + 1] ++ ;
	}
}

inline void encode ( char c )
{
	if ( c == '_' )
		code_length[0] ++ ;
	else
		code_length[c - 'A' + 1] ++ ;
}

int compare ( const void * element1 , const void * element2 )
{
	return (( const LETTER * )element1)->frequency - (( const LETTER * )element2)->frequency ;
}

int main (void)
{
	int i , j , len , current_length , ascii_length , Huffman ;
	string text ;
	while ( (cin >> text) , (text != "END") )
	{
		len = text.length() ;
		initialize () ;
		for ( i = 0 ; i < len ; i ++ )
			statistics ( text[i] ) ;
		qsort ( letter , 27 , sizeof(letter[0]) , compare ) ;
		for ( i = 0 ; i < 27 ; i ++ )
		{
			if ( letter[i].frequency != 0 )
				break;
		}
		if(i == 26)
			Huffman = len ;
		else
		{
			for ( ; i < 26 ; i ++ )
			{
				letter[i+1].frequency += letter[i].frequency ;
				letter[i+1].letter += letter[i].letter ;
				current_length = letter[i+1].letter.length() ;
				for( j = 0 ; j < current_length ; j ++ )
					encode ( (letter[i+1].letter)[j] ) ;
				qsort ( &letter[i+1] , 26 - i , sizeof(letter[0]) , compare ) ;
			}
			ascii_length = len * 8 ;
			Huffman = 0 ;
			for ( i = 0 ; i < 27 ; i ++ )
				Huffman +=  (code_length[i]) * frequency[i] ;
		}
		printf("%d %d %.1lf\n" , ascii_length , Huffman , (double)ascii_length / (double)Huffman );
	}
	return 0 ;
}
