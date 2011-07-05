#ifndef  _LOG_H_
#define  _LOG_H_

#define	LOG_FILE_PATH		"/home/orion/codes/c/etable/log"			/*  */

#define	MAX_FILE_NAME_LEN	512			/*  */

#ifdef	DEBUG
    #define	debuglog(args...)	LOG(__FILE__, __LINE__, __func__, ##args);
#else
    #define	debuglog(args...)
#endif

#include 	<string.h>
#include 	<stdarg.h>
#include 	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<unistd.h>


typedef struct
{
	FILE *logfile;
	int status;
}_LOGFILE;

_LOGFILE Log;

int init_log(FILE *logfile, const char* logname);
void LOG(const char* fname, const int linenum, const char* func, const char* fmt, ...);
int exit_log();

#endif
