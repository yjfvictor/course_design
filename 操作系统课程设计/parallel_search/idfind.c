/*
 * idfind.c
 * 
 * Copyright 2012 叶剑飞
 * 
 * Compile command:
 * 		gcc idfind.c -o idfind -D_REENTRANT -lpthread -std=c99 -Wall
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

typedef int COUNT;

char * id;
char * dirname;
pthread_mutex_t * mutex;

void * searching_thread( void * args )
{
	int number = *(int *)args;
	DIR * dirp;
	struct dirent * entry;
	if ( number == 0 )
	{
		dirp = opendir( dirname );
		while ( (entry = readdir( dirp )) )
			puts( entry->d_name );
	}
	return NULL;
}

bool StartSearch( const int threads, const char * id, const char * dirname )
{
	COUNT i;
	pthread_t threadid[threads];
	mutex = (pthread_mutex_t *)malloc( threads * sizeof(pthread_mutex_t) );
	for ( i = 0 ; i < threads ; i ++ )
	{
		if ( pthread_mutex_init( &mutex[i], NULL ) )
			return false;
	}
	for ( i = 0 ; i < threads ; i ++ )
	{
		if ( pthread_create( &threadid[i], NULL, searching_thread, &i ) )
			return false;
	}
	for ( i = 0 ; i < threads ; i ++ )
	{
		if ( pthread_join( threadid[i], NULL ) )
			return false;
	}
	for ( i = 0 ; i < threads ; i ++ )
		pthread_mutex_destroy( &mutex[i] );
	free( mutex );
	return true;
}

int main ( int argc, char * argv[] )
{
	int threads;
	int length;
	switch ( argc )
	{
		case 3:
			threads = 1;
			length = strlen(argv[1]) + 1;
			id = (char *)malloc( ( strlen(argv[1]) + 1 ) * sizeof(char) );
			strncpy( id, argv[1], length );
			length = strlen(argv[2]) + 1;
			dirname = (char *)malloc( ( strlen(argv[2]) + 1 ) * sizeof(char) );
			strncpy( dirname, argv[2], length );
			break;
		case 5:
			if ( strcmp( "-j", argv[1] ) )
				goto badArgument;
			if ( sscanf( argv[2], "%d", &threads ) != 1 )
				goto badArgument;
			if ( threads < 1 )
			{
				fprintf( stderr, "The amount of threads must be a positive integer.\n\n" );
				return EXIT_FAILURE;
			}
			length = strlen(argv[3]) + 1;
			id = (char *)malloc( ( strlen(argv[3]) + 1 ) * sizeof(char) );
			strncpy( id, argv[3], length );
			length = strlen(argv[4]) + 1;
			dirname = (char *)malloc( ( strlen(argv[4]) + 1 ) * sizeof(char) );
			strncpy( dirname, argv[4], length );
			break;
		default:
			goto badArgument;
	}
	if ( StartSearch( threads, id, dirname ) )
		return EXIT_SUCCESS;
	else
	{
		fprintf( stderr, "Error in threads." );
		return EXIT_FAILURE;
	}
badArgument:
	fprintf( stderr, "Usage: %s [-j n] id filename\n\n", argv[0] );
	fprintf( stderr, "\tn\tthe amount of threads, in arabic numbers.\n" );
	fprintf( stderr, "\tid\tthe word that you are looking for\n" );
	fprintf( stderr, "\tdirname\tthe directory name where the file is\n" );
	fprintf( stderr, "\n\n" );
	return EXIT_FAILURE;
}
