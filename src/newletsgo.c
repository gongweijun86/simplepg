#include	"../include/newletsgo.h"
#include	<sys/stat.h>
#include 	<signal.h>

extern EPG globle_epg[128];
extern PIDList pidlist;
bool error = false;


int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("arguments too few!\n");
		printf("Usage:\t%s filename.\n",argv[0]);
		exit(1);
	}
	init_log(Log.logfile, "debug");
	FILE *f;
	char *filepath = argv[1];

	struct stat buf;
	//get the file status in order to check whether it is a regular file
	if(lstat(argv[1],&buf) < 0){
		debuglog("Get %s status failed!\n",argv[1]);
		printf("Get %s status failed!\n",argv[1]);
		exit(1);
	}
	if(!S_ISREG(buf.st_mode)){
		debuglog("%s is not a regular file!\n",argv[1]);
		printf("%s is not a regular file!\n",argv[1]);
		exit(1);
	}

	if (!(f = fopen(filepath, "rb"))) {
		debuglog("Failure to open stream \"%s\"!\n",argv[1]);
		printf("Failure to open stream \"%s\"!\n",argv[1]);
		exit(1);
	}
	if (!check_file(f)) {
		debuglog("Could not find start of Header - check stream!\n");
		printf("Could not find start of Header - check stream!\n");
		exit(1);
	}


	init_pidlist(&pidlist);

	//static char buf[BUF_SIZE];如何使用缓冲呢？
	//setbuf(f,buf);
	int packet = 0;
	int total = get_total_packet(f);
	printf("totalpackets:%d\n", total);
	printf("processing...\n");
	while (!feof(f) && !error) {
		handle_packet(packet++, f);
		//printf("\b\b\b%.2d%%",(int)(100 *(float)packet/total));
	}
	printf("\ndone!\n");
	fclose(f);
	exit_log();
	int i = 0;
	for(i=0;i<128;i++){
		if(globle_epg[i].service_provider_name[0] == '\0') continue;
		printf("globle_epg[%d].service_provider_name:%s\t",i,globle_epg[i].service_provider_name);
		printf("globle_epg[%d].service_name:%s\t",i,globle_epg[i].service_name);
		printf("globle_epg[%d].event_name:%s\t",i,globle_epg[i].event_name);
		printf("globle_epg[%d].start_date:%d\t",i,globle_epg[i].start_date);
		printf("globle_epg[%d].start_time:%u\t",i,globle_epg[i].start_time);
		printf("globle_epg[%d].duration:%u\n",i,globle_epg[i].duration);
	}

	return 0;
}
