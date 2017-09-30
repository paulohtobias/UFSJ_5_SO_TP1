#include "commander.h"

#define FD_READ 0
#define FD_WRITE 1

int main(){
	int pipefd[2];
	pid_t pid;
	char buf;

	pipe(pipefd);
	pid = fork();
	
	switch(pid){
		case -1:
			perror("has not created a children process");
			break;
		case 0:
			printf("Child\n");
			close(pipefd[FD_WRITE]);
			dup2(pipefd[FD_READ], 0);
			printf("Switching...\n");
			execl("./main2","main2",(char*)NULL);
			break;
		default:
			//commander("./commander/input.txt");
			printf("Parent\n");
			close(pipefd[FD_READ]);
			FILE *in = fopen("./commander/input.txt", "r");
			while(!feof(in)){
				fscanf(in, "%c\n", &buf);
				write(pipefd[FD_WRITE], &buf, 1);
				sleep(1); ///A cada segundo um comando é lido
			}
			close(pipefd[FD_WRITE]);
			wait(NULL);
			exit(0);
			break;
	}
	return 0;
}
