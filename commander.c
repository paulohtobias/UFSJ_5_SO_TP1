#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#define FD_READ 0
#define FD_WRITE 1

int main(){
	puts("Process Commander");
	int pipefd[2];
	pid_t pid;

	pipe(pipefd);
	pid = fork();
	
	switch(pid){
		case -1:
			perror("has not created a children process");
			break;
		case 0:
			//fd de escrita não será usado.
			close(pipefd[FD_WRITE]);
			
			//Trocando a entrada padrão do filho pelo fd de leitura aberto no pipe.
			dup2(pipefd[FD_READ], 0);
			
			//Trocando o código pelo código do Process Manager.
			execl("./manager.out", "./manager.out", (char*)NULL);
			break;
		default:
			//fd de leitura não será usado.
			close(pipefd[FD_READ]);
			
			char comando;
			do{
				scanf("%c", &comando);
				if(comando != '\n'){
					write(pipefd[FD_WRITE], &comando, 1);
					sleep(1); ///A cada segundo um comando é lido
				}
			}while(comando != 'T');
			
			//Fecha o pipe pra escrita.
			close(pipefd[FD_WRITE]);
			
			//Espera o filho terminar.
			wait(NULL);
			exit(0);
			break;
	}
	return 0;
}
