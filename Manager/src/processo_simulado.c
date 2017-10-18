#include "processo_simulado.h"

ProcessoSimulado novo_ProcessoSimulado(const char *nome_arquivo){
	ProcessoSimulado processo;// = malloc(sizeof(ProcessoSimulado));

	processo.dado = 0;
	processo.pc = 0;
	processo.array_programa = novo_ArrayList(sizeof(Instrucao));
	ps_replace(&processo, nome_arquivo);

	return processo;
}

ProcessoSimulado ps_copia(ProcessoSimulado ps){
	ProcessoSimulado copia = ps;
	
	copia.array_programa = arraylist_copia(ps.array_programa);
	
	copia.pc++;
	
	return copia;
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
	processo->array_programa.tamanho_atual = 0;
	
	//temp será usada para percorrer a string instrucoes sem perder a referência
	//para o endereço base.
	char *temp = instrucoes;
	int i;
	for(i=0; instrucoes[i] != '\0'; i++){
		Instrucao instrucao;
		sscanf(temp, "%c", &instrucao.tipo);
		temp+=2;
		if(instrucao.tipo != 'B' && instrucao.tipo != 'E'){
			sscanf(temp, "%s\n", instrucao.parametro);
			temp += 1 + strlen(instrucao.parametro);
		}else{
			strcpy(instrucao.parametro,"-");
		}
		arraylist_add_fim(&processo->array_programa, &instrucao);
	}

	free(instrucoes);
}
