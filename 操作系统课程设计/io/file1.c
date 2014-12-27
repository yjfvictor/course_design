/*
 * file1.c
 * 
 * Copyright 2012 叶剑飞
 * 
 * Compile command:
 * 		gcc file1.c -o file1 -std=c99 -pedantic -Wall
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main ( int argc, char * argv[] )
{
	FILE * fp = NULL;
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
	if ( stat(argv[1], &statbuf ) != 0 )
	{
		fprintf( stderr, "File Access Error\n\n" );
		return EXIT_FAILURE;
	}
	filesize = statbuf.st_size;
	fp = fopen( argv[1], "rb" );
	if ( fp == NULL )
	{
		fprintf( stderr, "File Open Error\n\n" );
		return EXIT_FAILURE;
	}
	pText = (char *)malloc( filesize * sizeof(char) );
	if ( pText == NULL )
	{
		fclose(fp);
		fprintf( stderr, "No Enough Memory!!!\n\n" );
		return EXIT_FAILURE;
	}
	offset = 0;
	while ( !feof(fp) )
	{
		fread( pText+offset, bytes * sizeof(char), 1, fp );
		offset += bytes;
	}
	fclose(fp);
	fp = NULL;
	for ( int i = (filesize >> 1) ; i < filesize; i ++ )
	{
		temp = pText[i];
		pText[i] = pText[filesize-i-1];
		pText[filesize-i-1] = temp;
	}
	fp = fopen( argv[1], "wb" );
	if ( fp == NULL )
	{
		fprintf( stderr, "File Open Error\n\n" );
		free( pText );
		return EXIT_FAILURE;
	}
	offset = 0;
	while ( offset+bytes < filesize )
	{
		fwrite( pText+offset, bytes * sizeof(char), 1, fp );
		offset += bytes;
	}
	fwrite( pText+offset, (filesize-offset)*sizeof(char), 1, fp );
	fclose(fp);
	free(pText);
	return EXIT_FAILURE;
}
