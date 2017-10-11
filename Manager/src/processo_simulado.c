#include "processo_simulado.h"

ProcessoSimulado novo_ProcessoSimulado(const char *nome_arquivo){
	ProcessoSimulado processo;

	processo.dado = 0;
	processo.pc = 0;
	processo.instrucoes = NULL;
	ps_replace(&processo, nome_arquivo);

	return processo;
}

ProcessoSimulado ps_fork(ProcessoSimulado ps){
	ProcessoSimulado filho = ps;
	
	//TO-DO: copiar vetor de instruçao.
	
	filho.pc++;
	
	return filho;
}

void ps_replace(ProcessoSimulado *processo, const char *nome_arquivo){
	FILE *arquivo = fopen(nome_arquivo, "r");
	if(arquivo == NULL){
		printf("Nao existe o arquivo %s!\n", nome_arquivo);
		exit(1);
	}

	//Cache do arquivo em string.
	char *instrucoes = NULL;
	int size;
	fseek(arquivo, 0, SEEK_END);
	size = ftell(arquivo) + 1;
	rewind(arquivo);
	instrucoes = malloc(size);
	fread(instrucoes, 1, size, arquivo);
	fclose(arquivo);

	//Obtendo o número de instruções.
	int i, counter = 0;
	for(i=0; i < size; i++){
		if(instrucoes[i] == '\n'){
			counter++;
		}
	}
	
	//Liberando o vetor de instruções do processo anterior.
	if(processo->instrucoes != NULL){
		free(processo->instrucoes);
	}
	processo->instrucoes = malloc(counter * sizeof(Instrucao));
	
	//temp será usada para percorrer a string instrucoes sem perder a referência
	//para o endereço base.
	char *temp = instrucoes;

	for(i=0; i < counter; i++){
		sscanf(temp, "%c %s\n", &processo->instrucoes[i].tipo, processo->instrucoes[i].parametro);
		temp += 3 + strlen(processo->instrucoes[i].parametro);
	}

	free(instrucoes);
}

int ps_executar(ProcessoSimulado *processo){
	char* valor;
	for(; processo->instrucoes[processo->pc].tipo != 'E'; processo->pc++){
		
	}
	return 0; //Execução sem erros
}
