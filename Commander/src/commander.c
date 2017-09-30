#include "commander.h"

void commander(char* name){
	mkfifo("/tmp/input",0666); ///Define o fifo para a escrita
	int fd = open("/tmp/input",O_WRONLY); //Abre o fifo (Write)
	FILE *arquivo = fopen(name,"r"); //Abre o arquivo com os comandos
	while(!feof(arquivo)){
		switch(fgetc(arquivo)){
			case 'Q': ///Fim da unidade de tempo
				write(fd,"Q",1);
				break;
			case 'U': ///Desbloqueia o promeiro processo bloqueado
				write(fd,"U",1);
				break;
			case 'P': ///Imprime o estado atual do sistema
				write(fd,"P",1);
				break;
			case 'T': ///Imprimir tempodo de retorno médio e finaliza a simulação
				write(fd,"T",1);
				close(fd);
				unlink("/tmp/input");
				return;
			default: ///Caso um caracter não for reconhecido
				continue;
		}
		sleep(1); ///A cada segundo um comando é lido
	}
}

void comm_reader(void *(*p_manager)(char)){
	int fd = open("/tmp/input",O_RDONLY); ///Abre o fifo (Read)
	char buf; ///Buffer de recebimento
	while(buf!='T'){ //Finaliza a leitura
		read(fd,&buf,MAX_BUFF); //Lê o fifo
		p_manager(buf); ///Executa a funçao determinada
	}
	close(fd);

	return;
}
