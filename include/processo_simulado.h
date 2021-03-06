#ifndef PROCESSO_SIMULADO_H
#define PROCESSO_SIMULADO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array_list.h"

/**
 * Indica o estado de um <code>Processo Simulado</code>.
 */
typedef enum ESTADO{
    FINALIZADO = 1, ///Processo já terminou sua execução e pode ser substituído na
					///TabelaPcb.
    EXECUTANDO = 2, ///Processo está em execução na CPU.
    PRONTO = 4,     ///Processo está pronto para ser executado.
    BLOQUEADO = 8   ///Processo está bloqueado.
}ESTADO;

typedef struct Instrucao{
	char tipo;
	char parametro[256];
}Instrucao;

typedef struct ProcessoSimulado{
	int pc;
	int dado;
	ArrayList array_programa;
}ProcessoSimulado;

///Cria um no processo simulado a partir de <code>nome_arquivo</code>.
ProcessoSimulado *novo_ProcessoSimulado(const char *nome_arquivo);

///Faz uma cópia do processo.
ProcessoSimulado *ps_copia(ProcessoSimulado *ps);

/**
 * Sobrescreve o array de programa do processo pelo contido em
 * <code>nome_arquivo</code>.
 */
void ps_replace(ProcessoSimulado *processo, const char *nome_arquivo);

#endif //PROCESSO_SIMULADO_H
