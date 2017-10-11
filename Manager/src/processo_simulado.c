#include "processo_simulado.h"

ProcessoSimulado novo_ProcessoSimulado(const char *nome_arquivo){
	ProcessoSimulado processo;

	processo.dado = 0;
	processo.pc = 0;
	processo.instrucoes = novo_ArrayList(sizeof(Instrucao));
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
	
	//Zerando o vetor de instruções.
	processo->instrucoes.tamanho_atual = 0;
	
	//temp será usada para percorrer a string instrucoes sem perder a referência
	//para o endereço base.
	char *temp = instrucoes;
	int i;
	for(i=0; instrucoes[i] != '\0'; i++){
		Instrucao instrucao;
		sscanf(temp, "%c %s\n", &instrucao.tipo, instrucao.parametro);
		temp += 3 + strlen(instrucao.parametro);
		arraylist_add_fim(&processo->instrucoes, &instrucao);
	}

	free(instrucoes);
}
