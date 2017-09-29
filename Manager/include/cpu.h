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

#endif //CPU_H
