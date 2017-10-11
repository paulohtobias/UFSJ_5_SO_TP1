#ifndef PROCESSO_SIMULADO_H
#define PROCESSO_SIMULADO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Indica o estado de um <code>Processo Simulado</code>.
 */
typedef enum ESTADO{
    FINALIZADO, ///Processo já terminou sua execução e pode ser substituído na
                ///TabelaPcb.
    EXECUTANDO, ///Processo está em execução na CPU.
    PRONTO,     ///Processo está pronto para ser executado.
    BLOQUEADO   ///Processo está bloqueado.
}ESTADO;

typedef struct Instrucao{
	char tipo;
	char parametro[256];
}Instrucao;

typedef struct ProcessoSimulado{
	int pc;
	int dado;
	Instrucao *instrucoes;
}ProcessoSimulado;

ProcessoSimulado novo_ProcessoSimulado(const char *nome_arquivo);

ProcessoSimulado ps_fork(ProcessoSimulado ps);

void ps_replace(ProcessoSimulado *processo, const char *nome_arquivo);

int ps_executar(ProcessoSimulado *processo);

#endif //PROCESSO_SIMULADO_H
