#include "cpu.h"

CPU novo_CPU(int fatia_tempo){
	CPU cpu;
	
	cpu.pc = 0;
	cpu.fatia_tempo = fatia_tempo;
	cpu.array_programa = NULL;
	
	return cpu;
}

CPU novo_CPU_processo(int fatia_tempo, ProcessoSimulado ps){
	CPU cpu = novo_CPU(fatia_tempo);
	
	CPU_set_processo(cpu, ps);
	
	return cpu;
}

void CPU_set_processo(CPU cpu, ProcessoSimulado ps){
	cpu.pc = ps.pc;
	cpu.dado = ps.dado;
	cpu.array_programa = ps.instrucoes;
	cpu.tempo_total = 0;
}
