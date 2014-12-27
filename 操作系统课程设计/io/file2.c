/*
 * file2.c
 * 
 * Copyright 2012 叶剑飞
 * 
 * Compile command:
 * 		gcc file2.c -o file2 -std=c99 -pedantic -Wall
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main ( int argc, char * argv[] )
{
	int fd = 0;
	char * pText = NULL;
	char temp;
	int bytes, offset, filesize;
	struct stat statbuf;
	if ( argc != 3 )
	{
		fprintf( stderr, "Usage: %s <filename> <bytes>\n\n", argv[0] );
		return EXIT_FAILURE;
	}
	if ( sscanf( argv[2], "%d", &bytes ) != 1 )
	{
		fprintf( stderr, "Bytes number must be number!\n\n" );
		return EXIT_FAILURE;
	}
	fd = open( argv[1], O_RDWR );
	if ( fd == -1 )
	{
		fprintf( stderr, "File Open Error\n\n" );
		return EXIT_FAILURE;
	}
	if ( fstat(fd, &statbuf) != 0 )
	{
		fprintf( stderr, "Error Getting File Information\n\n" );
		close(fd);
		return EXIT_FAILURE;
	}
	filesize = statbuf.st_size;
	pText = (char *)malloc( filesize * sizeof(char) );
	if ( pText == NULL )
	{
		close(fd);
		fprintf( stderr, "No Enough Memory!!!\n\n" );
		return EXIT_FAILURE;
	}
	offset = 0;
	while ( offset < filesize )
		offset += read( fd, pText+offset, bytes * sizeof(char) );
	if ( lseek( fd, 0, SEEK_SET ) == -1 )
	{
		fprintf( stderr, "lseek error\n\n" );
		free( pText );
		close(fd);
		return EXIT_FAILURE;
	}
	for ( int i = (filesize >> 1) ; i < filesize; i ++ )
	{
		temp = pText[i];
		pText[i] = pText[filesize-i-1];
		pText[filesize-i-1] = temp;
	}
	offset = 0;
	while ( offset < filesize )
	{
		offset += write( fd, pText+offset, bytes * sizeof(char) );
	}
	close(fd);
	free(pText);
	return EXIT_FAILURE;
}
