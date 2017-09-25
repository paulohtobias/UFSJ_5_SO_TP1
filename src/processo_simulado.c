#include "processo_simulado.h"

ProcessoSimulado* novo_processo_simulado(const char * nome_arquivo){
	FILE *arquivo = fopen(nome_arquivo,"r");
	ProcessoSimulado *processo = calloc(sizeof(ProcessoSimulado),1);
	
	if(arquivo == NULL){
		printf("Nao existe o arquivo!\n");
		exit(1);
	}
	
	fseek(arquivo,0,SEEK_END);
	int size = ftell(arquivo)+1;
	rewind(arquivo);

	char *instrucoes = malloc(size);
	fread(instrucoes, 1, size, arquivo);
	fclose(arquivo);

	int i, counter = 1;
	for(i=0; i< size;i++ ){
		if(instrucoes[i]=='\n') {counter++;}
	}

	processo->instrucoes = malloc(sizeof(Instrucao)*counter);
	
	for(i=0; i< counter; i++){
		processo->instrucoes[i].parametro = malloc(150);
		sscanf(instrucoes,"%c %s\n", &processo->instrucoes[i].tipo,processo->instrucoes[i].parametro);
		instrucoes += 3 + strlen(processo->instrucoes[i].parametro);
	}

	return processo;
}