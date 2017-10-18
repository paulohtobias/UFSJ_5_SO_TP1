#ifndef TABELA_PCB_H
#define TABELA_PCB_H

#include "processo_simulado.h"

typedef struct TabelaPcb{
	int pid; ///ID do processo.
	int ppid; ///ID do processo pai.
	int pc;
	int dado;
	ArrayList array_programa;
	int prioridade;
	ESTADO estado;
	int tempo_inicio; ///"Horário" que o processo foi iniciado.
	int tempo_cpu; ///Tempo total em que o processo passou na CPU.
	
}TabelaPcb;

TabelaPcb novo_item_TabelaPcb(ProcessoSimulado *ps, int pid, int ppid,
							  int prioridade, int tempo_inicio);

int tabela_pcb_valido(const void *item);

void tabela_pcb_atualiza_estados(ArrayList *tabela_pcb, ESTADO estado, int indice);

#endif //TABELA_PCB_H
