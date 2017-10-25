#ifndef CPU_H
#define CPU_H

#include "processo_simulado.h"

typedef struct CPU{
	ProcessoSimulado *ps;
    int tempo_total;	///Tempo usado na fatia de tempo.
    int fatia_tempo;	///Tempo máximo que um processo pode ficar na CPU.
}CPU;

///Cria uma nova CPU vazia.
CPU novo_CPU(int fatia_tempo);

///Insere um processo na CPU.
void cpu_set_processo(CPU *cpu, ProcessoSimulado *ps);

///Executa a próxima instrução do processo que está na CPU.
ESTADO cpu_executar_instrucao(CPU *cpu);

#endif //CPU_H
