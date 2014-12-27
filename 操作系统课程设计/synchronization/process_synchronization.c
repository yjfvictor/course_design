/*
 * process_synchronization.c
 * 
 * Copyright 2012 叶剑飞
 *
 * Compile command:
 *		gcc process_synchronization.c -o process_synchronization -std=gnu99 -pedantic -Wall
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

typedef int COUNT;

union semun {
	int               val;    /* Value for SETVAL */
	struct semid_ds * buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  * array;  /* Array for GETALL, SETALL */
	struct seminfo  * __buf;  /* Buffer for IPC_INFO
				     (Linux-specific) */
};

int createSemaphore ( void )
{
	int semid;
	union semun arg;
	semid = semget( IPC_PRIVATE, 1, 0666|IPC_CREAT );
	if ( semid == -1 )
		return -1;
	arg.val = 1;
	if ( semctl( semid, 0, SETVAL, arg ) == -1 )
		return -1;
	return semid;
}

bool destroySemaphore ( int semid )
{
	union semun arg;
	if ( semctl( semid, 0, IPC_RMID, arg ) == -1 )
		return false;
	else
		return true;
}

bool P( int semid )
{
	struct sembuf spos;
	spos.sem_num = 0;
	spos.sem_op  = -1;
	spos.sem_flg = 0;
	if ( semop( semid, &spos, 1 ) == -1 )
		return false;
	return true;
}

bool V( int semid )
{
	struct sembuf spos;
	spos.sem_num = 0;
	spos.sem_op  = 1;
	spos.sem_flg = 0;
	if ( semop( semid, &spos, 1 ) == -1 )
		return false;
	return true;
}

int main (void)
{
	const int n = 10;
	int maxLoop[7];
	COUNT i;
	pid_t pid;

	int p12 = createSemaphore();
	int p13 = createSemaphore();
	int p24 = createSemaphore();
	int p25 = createSemaphore();
	int p35 = createSemaphore();
	int p46 = createSemaphore();
	int p56 = createSemaphore();
	int p6  = createSemaphore();

	srand( time(NULL) );
	for ( i = 1; i < 7 ; i ++ )
		maxLoop[i] = (rand() % n) + 1;
	P(p12);
	P(p13);
	P(p24);
	P(p25);
	P(p35);
	P(p46);
	P(p56);
	P(p6);

	for ( i = 1; i <= 6 ; i ++ )
	{
		if ( (pid = fork() ) < 0 )
		{
			fprintf( stderr, "fork() error!\n\n" );
			return EXIT_FAILURE;
		}
		else if ( pid == 0 )
			break;
	}

	switch ( i )
	{
		case 1:
			for ( COUNT j = 0 ; j < maxLoop[1] ; j ++ )
			{
				puts( "I am process one." );
				usleep( 500000 );
			}
			V(p12);
			V(p13);
			return EXIT_SUCCESS;
		case 2:
			P(p12);
			for ( COUNT j = 0 ; j < maxLoop[2] ; j ++ )
			{
				puts( "I am process two." );
				usleep( 500000 );
			}
			V(p24);
			V(p25);
			return EXIT_SUCCESS;
		case 3:
			P(p13);
			for ( COUNT j = 0 ; j < maxLoop[3] ; j ++ )
			{
				puts( "I am process three." );
				usleep( 500000 );
			}
			V(p35);
			return EXIT_SUCCESS;
		case 4:
			P(p24);
			for ( COUNT j = 0 ; j < maxLoop[4] ; j ++ )
			{
				puts( "I am process four." );
				usleep( 500000 );
			}
			V(p46);
			return EXIT_SUCCESS;
		case 5:
			P(p25);
			P(p35);
			for ( COUNT j = 0 ; j < maxLoop[5] ; j ++ )
			{
				puts( "I am process five." );
				usleep( 500000 );
			}
			V(p56);
			return EXIT_SUCCESS;
		case 6:
			P(p46);
			P(p56);
			for ( COUNT j = 0 ; j < maxLoop[6] ; j ++ )
			{
				puts( "I am process six." );
				usleep( 500000 );
			}
			V(p6);
			return EXIT_SUCCESS;
		default:
			P(p6);
			destroySemaphore( p12 );
			destroySemaphore( p13 );
			destroySemaphore( p24 );
			destroySemaphore( p25 );
			destroySemaphore( p35 );
			destroySemaphore( p46 );
			destroySemaphore( p56 );
			destroySemaphore( p6 );
			puts("All Processes have finished.");
			return EXIT_SUCCESS;
	}


	return EXIT_SUCCESS;
}
