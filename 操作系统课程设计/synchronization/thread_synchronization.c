/*
 * thread_synchronization.c
 * 
 * Copyright 2012 叶剑飞
 *
 * Compile command:
 *		gcc thread_synchronization.c -o thread_synchronization -std=gnu99 -pedantic -D_REENTRANT -lpthread -Wall
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

typedef int COUNT;

sem_t p12, p13, p24, p25, p35, p46, p56;
int maxLoop[7];

void * thread1 ( void * args )
{
	for ( COUNT i = 0 ; i < maxLoop[1] ; i ++ )
	{
		puts( "I am thread one." );
		usleep(500000);
	}
	sem_post( &p12 );
	sem_post( &p13 );
	return NULL;
}

void * thread2 ( void * args )
{
	sem_wait( &p12 );
	for ( COUNT i = 0 ; i < maxLoop[2] ; i ++ )
	{
		puts( "I am thread two." );
		usleep(500000);
	}
	sem_post( &p24 );
	sem_post( &p25 );
	return NULL;
}

void * thread3 ( void * args )
{
	sem_wait( &p13 );
	for ( COUNT i = 0 ; i < maxLoop[3] ; i ++ )
	{
		puts( "I am thread three." );
		usleep(500000);
	}
	sem_post( &p35 );
	return NULL;
}

void * thread4 ( void * args )
{
	sem_wait( &p24 );
	for ( COUNT i = 0 ; i < maxLoop[4] ; i ++ )
	{
		puts( "I am thread four." );
		usleep(500000);
	}
	sem_post( &p46 );
	return NULL;
}

void * thread5 ( void * args )
{
	sem_wait( &p25 );
	sem_wait( &p35 );
	for ( COUNT i = 0 ; i < maxLoop[5] ; i ++ )
	{
		puts( "I am thread five." );
		usleep(500000);
	}
	sem_post( &p56 );
	return NULL;
}

void * thread6 ( void * args )
{
	sem_wait( &p46 );
	sem_wait( &p56 );
	for ( COUNT i = 0 ; i < maxLoop[6] ; i ++ )
	{
		puts( "I am thread six." );
		usleep(500000);
	}
	return NULL;
}

int main (void)
{
	pthread_t threadid[7];
	const int n = 10;

	srand( time(NULL) );

	for ( COUNT i = 1 ; i < 7 ; i ++ )
		maxLoop[i] = (rand() % n) + 1;

	if ( sem_init( &p12, 0, 0 ) == -1 )
	{
		fprintf( stderr, "Error Initializing Semaphore\n\n");
		return EXIT_FAILURE;
	}
	if ( sem_init( &p13, 0, 0 ) == -1 )
	{
		fprintf( stderr, "Error Initializing Semaphore\n\n");
		return EXIT_FAILURE;
	}
	if ( sem_init( &p24, 0, 0 ) == -1 )
	{
		fprintf( stderr, "Error Initializing Semaphore\n\n");
		return EXIT_FAILURE;
	}
	if ( sem_init( &p25, 0, 0 ) == -1 )
	{
		fprintf( stderr, "Error Initializing Semaphore\n\n");
		return EXIT_FAILURE;
	}
	if ( sem_init( &p35, 0, 0 ) == -1 )
	{
		fprintf( stderr, "Error Initializing Semaphore\n\n");
		return EXIT_FAILURE;
	}
	if ( sem_init( &p46, 0, 0 ) == -1 )
	{
		fprintf( stderr, "Error Initializing Semaphore\n\n");
		return EXIT_FAILURE;
	}
	if ( sem_init( &p56, 0, 0 ) == -1 )
	{
		fprintf( stderr, "Error Initializing Semaphore\n\n");
		return EXIT_FAILURE;
	}

	if ( pthread_create( &threadid[1], NULL, thread1, NULL ) )
	{
		fprintf( stderr, "Error Creating Thread.\n\n" );
		return EXIT_FAILURE;
	}
	if ( pthread_create( &threadid[2], NULL, thread2, NULL ) )
	{
		fprintf( stderr, "Error Creating Thread.\n\n" );
		return EXIT_FAILURE;
	}
	if ( pthread_create( &threadid[3], NULL, thread3, NULL ) )
	{
		fprintf( stderr, "Error Creating Thread.\n\n" );
		return EXIT_FAILURE;
	}
	if ( pthread_create( &threadid[4], NULL, thread4, NULL ) )
	{
		fprintf( stderr, "Error Creating Thread.\n\n" );
		return EXIT_FAILURE;
	}
	if ( pthread_create( &threadid[5], NULL, thread5, NULL ) )
	{
		fprintf( stderr, "Error Creating Thread.\n\n" );
		return EXIT_FAILURE;
	}
	if ( pthread_create( &threadid[6], NULL, thread6, NULL ) )
	{
		fprintf( stderr, "Error Creating Thread.\n\n" );
		return EXIT_FAILURE;
	}

	for ( COUNT i = 1 ; i < 7 ; i ++ )
	{
		if ( pthread_join( threadid[i] , NULL ) )
		{
			fprintf( stderr, "Error Joining Thread.\n\n" );
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}
