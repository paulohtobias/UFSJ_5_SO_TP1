#include "processo_simulado.h"

ProcessoSimulado *novo_processo_simulado(const char *nome_arquivo){
	ProcessoSimulado *processo = calloc(1, sizeof(ProcessoSimulado));

	ps_replace(processo, nome_arquivo);

	return processo;
}

void ps_replace(ProcessoSimulado *processo, const char *nome_arquivo){
	FILE *arquivo = fopen(nome_arquivo, "r");
	if(arquivo == NULL){
		printf("Nao existe o arquivo %s!\n", nome_arquivo);
		exit(1);
	}

	//Cache do arquivo em string.
	fseek(arquivo, 0, SEEK_END);
	int size = ftell(arquivo) + 1;
	rewind(arquivo);

	char *instrucoes = malloc(size);
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
	
	char *temp = instrucoes;

	for(i=0; i < counter; i++){
		processo->instrucoes[i].parametro = malloc(256);
		sscanf(temp, "%c %s\n", &processo->instrucoes[i].tipo, processo->instrucoes[i].parametro);
		temp += 3 + strlen(processo->instrucoes[i].parametro);
	}

	free(instrucoes);
}

int ps_executar(ProcessoSimulado *processo){
	char* valor;
	for(; processo->instrucoes[processo->pc].tipo != 'E'; processo->pc++){
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

			case 'F':
				//TO-DO: Faz a copia exata do processo pai
				break;

			case 'R':
				ps_replace(processo, valor);
				//Atualizando o PC pra primeira instrução.
				processo->pc = -1;
				break;
		}
	}
	return 0; //Execução sem erros
}
