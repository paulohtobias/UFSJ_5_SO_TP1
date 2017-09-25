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

int ps_executar(ProcessoSimulado *processo){
	char* valor;
	for(; processo->instrucoes[processo->pc].tipo!='E'; processo->pc++){
		valor = processo->instrucoes[processo->pc].parametro;
		switch(processo->instrucoes[processo->pc].tipo){
			case 'S':
				processo->dado = atoi(valor);
				break;
				
			case 'A':
				processo->dado += atoi(valor);
				break;
			
			case 'D':
				processo->dado -= atoi(valor);
				break;
				
			case 'B':
				//TO-DO: bloquear processo
				break;
				
			case 'E':
				return 1; //Conseguiu terminar sem erros
				break;
			
			case 'F':
				//TO-DO: Faz a copia exata do processo pai
				break;
				
			case 'R':
				//TO-DO: Carrega outro conjunto de instruções para o processo
				break;
		}
	}
	return 0; //Retornou de forma inesperada
}