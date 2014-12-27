/*
 * file3.c
 * 
 * Copyright 2012 叶剑飞
 * 
 * Compile command:
 * 		gcc file3.c -o file3 -std=c99 -pedantic -Wall
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main ( int argc, char * argv[] )
{
	int fd = 0;
	char * pText = NULL;
	char temp;
	int filesize;
	struct stat statbuf;
	if ( argc != 2 )
	{
		fprintf( stderr, "Usage: %s <filename>\n\n", argv[0] );
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
	pText = mmap( NULL, filesize, 
			PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0 );
	for ( int i = (filesize >> 1) ; i < filesize; i ++ )
	{
		temp = pText[i];
		pText[i] = pText[filesize-i-1];
		pText[filesize-i-1] = temp;
	}
	munmap( pText, filesize );
	close(fd);
	return EXIT_FAILURE;
}
