/*
 * createfile.c
 * 
 * Copyright 2012 叶剑飞
 * 
 * Compile command:
 * 		gcc createfile.c -o createfile -std=c99 -pedantic -Wall
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main ( int argc , char * argv[] )
{
	int filesize;
	char * pText = NULL;
	int fd;
	if ( argc != 3 )
	{
		fprintf( stderr, "Usage: %s <filename> <filesize>\n\n", argv[0] );
		return EXIT_FAILURE;
	}
	if ( sscanf( argv[2], "%d", &filesize ) != 1 )
	{
		fprintf( stderr, "Filesize must be measured in arabic numbers.\n\n" );
		return EXIT_FAILURE;
	}
	pText = (char *)malloc( filesize * sizeof(char) );
	if ( pText == NULL )
	{
		fprintf( stderr, "No enough memory!\n\n" );
		return EXIT_FAILURE;
	}
	srand( time(NULL) );
	for ( int i = 0 ; i < filesize ; i ++ )
		pText[i] = 32 + rand() % 95;
	fd = open( argv[1], O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR );
	if ( fd ==-1 )
	{
		free( pText );
		fprintf( stderr, "File Open Error\n\n" );
		return EXIT_FAILURE;
	}
	write( fd, pText, filesize * sizeof(char) );
	free( pText );
	close(fd);
	return EXIT_SUCCESS;
}
