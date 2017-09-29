#ifndef CPU_H
#define CPU_H

#include "processo_simulado.h"

typedef struct CPU{
    int dado;
	int pc;
	Instrucao *array_programa;
    int tempo_total; ///Tempo usado na fatia de tempo.
    int fatia_tempo;
}CPU;

CPU novo_CPU(int fatia_tempo);

CPU novo_CPU_processo(int fatia_tempo, ProcessoSimulado ps);

void CPU_set_processo(CPU cpu, ProcessoSimulado ps);

#endif //CPU_H
