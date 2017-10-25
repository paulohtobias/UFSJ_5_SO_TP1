#ifndef TABELA_PCB_H
#define TABELA_PCB_H

#include "processo_simulado.h"

typedef struct TabelaPcb{
	int pid; ///ID do processo.
	int ppid; ///ID do processo pai.
	ProcessoSimulado *ps;
	int prioridade;
	ESTADO estado;
	int tempo_inicio; ///"Horário" que o processo foi iniciado.
	int tempo_final;///"Horário" que o processo foi terminado..
	int tempo_cpu; ///Tempo total em que o processo passou na CPU.
	
}TabelaPcb;

///Cria um novo item da tabela PCB.
TabelaPcb novo_item_TabelaPcb(ProcessoSimulado *ps, int pid, int ppid,
							  int prioridade, int tempo_inicio);

///Atualiza o estado de um item da tabela PCB indicado por <code>indice</code>.
void tabela_pcb_atualiza_estados(ArrayList *tabela_pcb, ESTADO estado, int indice);

///Imprime os dados do item da tabela no arquivo indicado.
void tabela_pcb_imprime_item(TabelaPcb item_tabela, FILE *out);

#endif //TABELA_PCB_H
