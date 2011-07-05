#include	"../include/log.h"

int
init_log(FILE *logfile,const char *log_name)
{
	if(log_name == NULL)
	{
		return -1;
	}
	char *log_path;
	unsigned int len_dir;
	unsigned int len_name;

	log_path = (char *)malloc(sizeof(char) * MAX_FILE_NAME_LEN);
	if(log_path == NULL)
	{
		return -1;
	}

	memset(log_path, 0, MAX_FILE_NAME_LEN);

	if(access(LOG_FILE_PATH, R_OK | W_OK) != -1)
	{
		len_dir = strlen(LOG_FILE_PATH);
		memcpy(log_path, LOG_FILE_PATH, len_dir);
	}
	else
	{
		log_path = getcwd(log_path, MAX_FILE_NAME_LEN);
		len_dir = strlen(log_path);
	}
	len_name = strlen(log_name);
//	log_path[len_dir] = "/";
//
	memset(log_path + len_dir,'/', 1);

	memcpy(log_path + len_dir + 1, log_name, len_name);
	memcpy(log_path + len_dir + len_name + 1, ".log", 4);

	
	if((Log.logfile = fopen(log_path, "w+")) == NULL)
	{
		return -1;
	}
	free(log_path);
	log_path = NULL;
	return 0;
}

void
LOG(const char* fname,const int linenum,const char* func,const char* fmt, ...)
{
	va_list args;
	time_t t = time(0);
	char local_time[64];
	va_start(args, fmt);
	strftime(local_time, sizeof(local_time), "%Y-%m-%d %X", localtime(&t));
	fprintf(Log.logfile, "[%s: %s %s %d]\t", local_time, fname, func, linenum);
	vfprintf(Log.logfile, fmt, args);
	fprintf(Log.logfile, "\r\n");
	va_end(args);
}

int
exit_log(){
	return fclose(Log.logfile);
}
//int
//main(int argc, char ** argv)
//{
//
//	if(init_log(Log.logfile, "DEBUG") == -1)
//	{
//		//todo
//	}
////	init_log(Log.logfile,"DEBUG");
//	debuglog("helloworld!");
//	debuglog("logtest!%s","hope succeed!");
//	debuglog("logtest!!!%s","hope succeed!");
//	debuglog("logtest!!!!!!%s","hope succeed!");
//
//	return 0;
//}
