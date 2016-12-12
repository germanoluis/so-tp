/* This program must be run with sudo privileges */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND_SIZE 500

int main(int argc, char *argv[]){

	/* Depending on the scheduling policy, we need to get one or two
         * arguments. So if we have got different, exit the program */
	if((argc != 2) && (argc != 3)){
		printf("Usage: ./a.out <scheduling policy> <priority(if required)>\n");
		exit(EXIT_FAILURE);
	}

	/* Getting all the running processes pid's */
	system("ps -Ao pid | tail -n +2 > ps_output");

	FILE *ps_output;

	/* Opening the file so it can be read */
	ps_output = fopen("ps_output", "r");

	char command[COMMAND_SIZE];
	long pid;

	while(!feof(ps_output)){
		fscanf(ps_output, "%li", &pid);

		/* This is here because otherwise the last pid would be read twice */
		if(!feof(ps_output)){
			/* Emptying the command buffer */
			memset(command, 0, COMMAND_SIZE);

			/* Now we properly print the command in the buffer, according to
                         * which scheduling policy was chosen */
			if(strcmp(argv[1], "SCHED_OTHER") == 0)
				sprintf(&command[strlen(command)], "chrt -aop 0 %li", pid);
			else if(strcmp(argv[1], "SCHED_FIFO") == 0)
                                sprintf(&command[strlen(command)], "chrt -afp %s %li", argv[2], pid);
			else if(strcmp(argv[1], "SCHED_RR") == 0)
                                sprintf(&command[strlen(command)], "chrt -arp %s %li", argv[2], pid);
			else if(strcmp(argv[1], "SCHED_BATCH") == 0)
				sprintf(&command[strlen(command)], "chrt -abp 0 %li", pid);
			else if(strcmp(argv[1], "SCHED_IDLE") == 0)
                                sprintf(&command[strlen(command)], "chrt -aip 0 %li", pid);

			/* Let's execute the command! */
			system(command);
		}
	}

	/* Don't forget to close it */
	fclose(ps_output);

	return 0;

}
