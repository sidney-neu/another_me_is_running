#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#define PID_FILE "./pid.txt"
//#define WHO_AM_I "pid_check"
static int another_me_running(char *processname, char *pid_file)
{
	FILE *fp=NULL;
	pid_t old_pid;
	char pid_string[12];
	DIR *dir;
	struct dirent *entry;
	int ret = 0;

	fp = fopen(pid_file, "r");
	if (fp == NULL)
		return ret;

	if (fscanf(fp, "%d", &old_pid) < 1)
	{
		fclose(fp);
		return ret;
	}

	fclose(fp);

	sprintf(pid_string, "%d", old_pid);

	dir = opendir("/proc");
	while(1)
	{
		char *name = NULL;

		if ((entry = readdir(dir)) == NULL)
			break;

		name = entry->d_name;
		if ((isdigit(name[0])) && (strcmp(name, pid_string) == 0))
		{
			char status[32];
			char buf[1024];
			char short_cmd[16] = {0, };

			sprintf(status, "/proc/%s/stat", pid_string);

			if((fp = fopen(status, "r")) == NULL)
				break;
			name = fgets(buf, sizeof(buf), fp);
			fclose(fp);
			if(name == NULL)
				break;
			name = strrchr(buf, ')'); /* split into "PID (cmd" and "<rest>" */
			if(name == 0 || name[1] != ' ')
				break;
			*name = 0;
			sscanf(buf, "%*s (%15c", short_cmd);

			if (strncmp(short_cmd, processname, strlen(short_cmd)) == 0)
				ret = 1;

			break;
		}
	}
	closedir(dir);
	dir = NULL;
	return ret;
}

int pid_file_process()
{
	if (0 != another_me_running(WHO_AM_I, PID_FILE)){
		printf("%s is runing.\n",WHO_AM_I);
		return -1;
	}
        FILE *fp = NULL;
        fp = fopen(PID_FILE, "w+");
        if(fp == NULL){
                printf("DGA pid_file_process failed.\n");
                return -1;
        }
        int pid = getpid();
        fprintf(fp, "%d", pid);
        fclose(fp);
        return 0;
}
