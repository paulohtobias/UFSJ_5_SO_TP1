#ifndef _PROCESSO_SIMULADO_H_
#define _PROCESSO_SIMULADO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Instrucao{
	char tipo;
	char *parametro;
}Instrucao;

typedef struct ProcessoSimulado{
	int pc;
	int dado;
	Instrucao *instrucoes;
}ProcessoSimulado;

int Set(int ){
	
}

ProcessoSimulado* novo_processo_simulado(const char * nome_arquivo);
#endif //_PROCESSO_SIMULADO_H_