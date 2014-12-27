/*
 * victor.c
 * 
 * Copyright 2012 叶剑飞
 * 
 * Compile command:
 *		gcc victorshell.c -o victorshell -std=gnu99 -pedantic -D_REENTRANT -lpthread -Wall
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/wait.h>
#include <pthread.h>

#define MAX_LENGTH 256

typedef int COUNT;

typedef struct
{
	pid_t pid;
	char cmdline[MAX_LENGTH];
} PROCESS_STRUCTURE;

void version(void)
{
	puts( "Victor Shell, version 1.0.0-beta" );
	puts( "Copyright (C) 2012 Victor Jianfei Ye" );
	puts("");
}

void arghelp( const char * currentFilename )
{
	version();
	printf ( "Usage:%s [option] ...\n", currentFilename );
	puts ( "Options:" );
	puts( "\t--version");
	puts( "\t--help");
	puts( "\t-v" );
}

void help(const char * content)
{
	if ( content == NULL )
	{
		version();
		puts ( "exit" );
		puts ( "cd" );
		puts ( "clear" );
		puts ( "pwd" );
		puts ( "echo" );
		puts ( "" );
	}
	else
	{
		if ( !strcmp( content, "exit" ) )
		{
			puts( "exit: exit [n]" );
			puts( "\tExit the shell." );
			puts( "" );
			puts( "\tExits the shell with a status of N.  If N is omitted, the exit status" );
			puts( "\tis that of the last command executed." );
		}
		else if ( !strcmp( content, "cd" ) )
		{
			puts( "cd: cd <directory name>" );
			puts( "\tchange to the directory" );
			puts( "" );
		}
		else if ( !strcmp( content, "clear" ) )
		{
			puts( "clear: clear" );
			puts( "\tclear the terminal screen" );
		}
		else if ( !strcmp( content, "pwd" ) )
		{
			puts( "pwd: pwd" );
			puts( "Print the name of the current working directory." );
		}
		else if ( !strcmp( content, "echo" ) )
		{
			puts( "echo: echo [arg ...]" );
			puts( "\tWrite arguments to the standard output." );
			puts( "\tDisplay the ARGs on the standard output followed by a newline." );
			puts( "" );
		}
	}
}

bool exeInternalCmd( const char *cmd )
{
	int argc;
	char argv[MAX_LENGTH][MAX_LENGTH];
	memset( argv, 0, sizeof(argv) );
	argc = sscanf(cmd, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], argv[11], argv[12], argv[13], argv[14], argv[15], argv[16], argv[17], argv[18], argv[19], argv[20], argv[21], argv[22], argv[23], argv[24], argv[25], argv[26], argv[27], argv[28], argv[29], argv[30], argv[31], argv[32], argv[33], argv[34] );
	if ( argc <= 0 )
		return true;
	else if ( argc >= 1 )
	{
		if ( argv[0][0] == '#' )
			return true;
		if ( !strcmp( argv[0], "exit" ) )
		{
			puts("exit");
			if ( argc == 1 )
				exit(EXIT_SUCCESS);
			else if ( argc == 2 )
			{
				int exitcode;
				if ( sscanf( argv[1], "%d", &exitcode ) == 1 )
					exit( exitcode );
				else
				{
					printf("victorshell: exit: %s: numeric argument required\n", argv[1] );
					exit(255);
				}
			}
			else
			{
				puts("victorshell: exit: too many arguments");
				exit(EXIT_FAILURE);
			}
		}
		else if ( !strcmp(argv[0], "cd" ) )
		{
			if( argc == 1 || (argc == 2 && !strcmp( argv[1], "~") ) )
			{
				if ( chdir(getenv("HOME")) != 0 )
					printf( "victorshell: cd: %s: no such file or directory\n", getenv("HOME") );
			}
			else if ( argc == 2 && !strcmp( argv[1] , "-" ) )
			{
				char * oldPwd = getenv("OLDPWD");
				char curPwd[MAX_LENGTH];
				if ( getcwd( curPwd, sizeof(curPwd) ) == NULL )
					strncpy( curPwd, "", 3 ) ;
				if ( oldPwd == NULL )
					puts( "victorshell: cd: OLDPWD not set" );
				else
				{
					if ( chdir(oldPwd) != 0 )
						printf( "victorshell: cd: %s: no such file or directory\n", oldPwd );
					else
					{
						puts( oldPwd );
						if ( strcmp( curPwd, "" ) )
							setenv( "OLDPWD", curPwd, 1 );
						else
							unsetenv( "OLDPWD" );
					}
				}
			}
			else
			{
				char curPwd[MAX_LENGTH];
				if ( getcwd( curPwd, sizeof(curPwd) ) == NULL )
					strncpy( curPwd, "", 3 ) ;
				if( chdir(argv[1]) != 0 )
					printf( "victorshell: cd: %s: no such file or directory\n", argv[1] );
				else
				{
					if ( strcmp( curPwd, "" ) )
						setenv( "OLDPWD", curPwd, 1 );
					else
						unsetenv( "OLDPWD" );
				}
			}
			return true;
		}
		else if ( !strcmp(argv[0], "echo" ) )
		{
			if ( argc > 1 )
			{
				printf( "%s", argv[1] );
				for ( int i = 2; i < argc; i ++ )
					printf ( " %s", argv[i] );
			}
			puts("");
			return true;
		}
		else if ( !strcmp( argv[0], "pwd" ) )
		{
			char path[MAX_LENGTH];
			if ( getcwd(path, sizeof(path)) == NULL )
				puts("invalid path");
			else
				puts(path);
			return true;
		}
		else if ( !strcmp( argv[0], "clear" ) )
		{
			printf("\033[H\033[2J");
			return true;
		}
		else if ( !strcmp( argv[0], "environ" ) )
		{
			char path[MAX_LENGTH];
			getcwd( path, sizeof(path) );
			printf( "USER=%s\n", getpwuid(getuid())->pw_name );
			printf( "PWD=%s\n", path );
			printf( "HOME=%s\n", getenv("HOME") );
			printf( "PATH=%s\n", getenv("PATH") );
			return true;
		}
		else if ( !strcmp(argv[0], "help" ) )
		{
			if ( argc == 1 )
				help(NULL);
			else
				help(argv[1]);
			return true;
		}
	}
	return false;
}

void * waitBackgroundProcess ( void * args )
{
	int status;
	PROCESS_STRUCTURE processStructure = *(PROCESS_STRUCTURE *)args;
	pid_t pid = processStructure.pid;
	waitpid( pid, &status, 0 );
	if ( WEXITSTATUS(status) == EXIT_FAILURE )
	{
		fprintf( stderr, "victorshell: %s: command not found...\n", processStructure.cmdline );
	}
	else
	{
		printf ( "Done\t\t\t%s\n", processStructure.cmdline );
	}
	return NULL;
}

bool exeExternalCmd( const char * cmd )
{
	int argc;
	COUNT i;
	pid_t pid;
	char * argv[MAX_LENGTH];
	int status;
	bool background;
	for ( i = 0 ; i < MAX_LENGTH ; i ++ )
	{
		argv[i] = (char *)malloc( MAX_LENGTH * sizeof(char) );
	}
	argc = sscanf(cmd, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], argv[11], argv[12], argv[13], argv[14], argv[15], argv[16], argv[17], argv[18], argv[19], argv[20], argv[21], argv[22], argv[23], argv[24], argv[25], argv[26], argv[27], argv[28], argv[29], argv[30], argv[31], argv[32], argv[33], argv[34] );
	for ( i = argc ; i < MAX_LENGTH ; i ++ )
	{
		free( argv[i] );
		argv[i] = NULL;
	}
	if ( !strcmp( argv[argc-1], "&") ) 
	{
		free( argv[argc-1] );
		argv[argc-1] = NULL;
		background = true;
	}
	else if ( argv[argc-1][strlen(argv[argc-1])-1] == '&' ) 
	{
		argv[argc-1][strlen(argv[argc-1])-1] = '\0';
		background = true;
	}
	else
	{
		background = false;
	}

	if ( (pid = fork() ) < 0 )
	{
		puts ( "fork() failed." );
		return true;
	}
	else if ( pid == 0 )
	{
		if ( execvp( argv[0], argv ) < 0 )
		{
			exit( EXIT_FAILURE );
		}
	}
	if ( background ) 
	{
		pthread_t backgroundWaitingThread;
		PROCESS_STRUCTURE processStructure;
		processStructure.pid = pid;
		strncpy( processStructure.cmdline, argv[0] , MAX_LENGTH ) ;
		pthread_create( &backgroundWaitingThread, NULL, waitBackgroundProcess, (void *)&processStructure );
		return true;
	}
	else
	{
		waitpid( pid, &status, 0 );
		if ( WEXITSTATUS(status) == EXIT_FAILURE )
			return false;
		else
			return true;
	}
}

int main (int argc, char * argv[])
{
	FILE * fp = NULL;
	bool debug = false;
	char cmd[MAX_LENGTH];
	memset( cmd, 0, sizeof(cmd) );
	if ( argc >= 2 )
	{
		if ( !strcmp("-v", argv[1] ) )
			debug = true;
		else if ( !strcmp("--help", argv[1] ) )
		{
			arghelp(argv[0]);
			return EXIT_SUCCESS;
		}
		else if ( !strcmp("--version", argv[1] ) )
		{
			version();
			return EXIT_SUCCESS;
		}
		else
		{
			if ( ( fp = fopen(argv[1] , "r" ) ) == NULL )
			{
				printf( "victorshell: %s: invalid option\n", argv[1] );
				arghelp( argv[0] );
				return EXIT_FAILURE;
			}
		}
	}
	if ( fp == NULL )
		fp = stdin;
	while (true)
	{
		char path[MAX_LENGTH];
		char hostname[MAX_LENGTH];
		if ( fp == stdin )
		{
			gethostname( hostname, sizeof(hostname) );
			getcwd( path, sizeof(path) );
			printf ( "[%s@%s %s]", getpwuid(getuid())->pw_name, hostname, path );
			if ( getuid() == 0 )
				printf ( "# " );
			else
				printf ( "$ " );
			fflush( stdout );
		}
		if ( fgets(cmd, sizeof(cmd)-1, fp ) == NULL )
		{
			if ( fp != stdin )
				fclose( fp );
			return EXIT_SUCCESS;
		}
		cmd[strlen(cmd)-1] = '\0';
		if (debug)
			puts(cmd);
		if ( !exeInternalCmd(cmd) )
		{
			if( !exeExternalCmd(cmd) )
			{
				char argfirst[MAX_LENGTH];
				sscanf( cmd, "%s", argfirst );
				printf( "victorshell: %s: command not found...\n", argfirst );
			}
		}
	}
	return EXIT_SUCCESS;
}
