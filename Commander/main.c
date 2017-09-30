#include "commander.h"

int main(){
	int pipefd[2];
	pid_t pid;
	char buf;

	pid = fork();
	
	switch(pid){
		case -1:
			perror("has not created a children process");
			break;
		case 0:
			usleep(100);
			execl("./main2","main2",(char*)NULL);
		break;
		default:
			commander("./commander/input.txt");
			break;
	}
	return 0;
}
