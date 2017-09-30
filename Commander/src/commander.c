#include "commnader.h"

void commander(char* name){
	mkfifo("/tmp/input",0666);
	char comando;
	int fd = open("/tmp/input",O_WRONLY);
	FILE *arquivo = fopen(name,"r");
	while(!feof(arquivo)){
		comando=fgetc(arquivo);
		switch(comando){
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
				///printf("%c",'\n');
				continue;
		}
		sleep(1);
	}
}

void comm_reader(void *(*p_manager)(char)){
	int fd = open("/tmp/input",O_RDONLY);
	char buf;
	while(buf!='T'){
		read(fd,&buf,MAX_BUFF);
		printf("%c\n",buf);
		p_manager(buf);
	}
	close(fd);

	return 0;
}