#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "pid_check.h"

int main(int argc, char** argv)
{
	unsigned int i = 1;
	if(0 > pid_file_process()){
		return -1;
	}
	while(1){
		printf("running %d.\n",i);
		i++;
		sleep(1);
	}
	return 0;
}
