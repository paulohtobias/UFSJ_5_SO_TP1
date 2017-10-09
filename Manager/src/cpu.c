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
	
	cpu_set_processo(cpu, ps);
	
	return cpu;
}

void cpu_set_processo(CPU cpu, ProcessoSimulado ps){
	cpu.pc = ps.pc;
	cpu.dado = ps.dado;
	cpu.array_programa = ps.instrucoes;
	cpu.tempo_total = 0;
}

int cpu_executar_instrucao(CPU *cpu){
	char *valor = cpu->array_programa[cpu->pc].parametro;
	switch(cpu->array_programa[cpu->pc].tipo){
		case 'S':
			cpu->dado = atoi(valor);
			break;
		case 'A':
			cpu->dado += atoi(valor);
			break;
		case 'D':
			cpu->dado -= atoi(valor);
			break;
		case 'B':
			//TO-DO: bloquear processo
			break;
		case 'F':
			//TO-DO: Faz a copia exata do processo pai
			break;
		case 'R':
			//ps_replace(cpu, valor);
			//Atualizando o PC pra primeira instrução.
			cpu->pc = -1;
			break;
	}
	cpu->pc++;
}
