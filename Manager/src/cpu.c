#include "cpu.h"

extern ArrayList tabela_pcb;

CPU novo_CPU(int fatia_tempo){
	CPU cpu;
	
	cpu.pc = 0;
	cpu.fatia_tempo = fatia_tempo;
	cpu.array_programa = novo_ArrayList(sizeof(Instrucao));
	
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
	cpu.array_programa = arraylist_copia(ps.instrucoes);
	cpu.tempo_total = 0;
}

ESTADO cpu_executar_instrucao(CPU *cpu){
	Instrucao instrucao;
	arraylist_get_index(cpu->array_programa, cpu->pc, &instrucao);
	char *parametro = instrucao.parametro;
	switch(instrucao.tipo){
		case 'S':
			cpu->dado = atoi(parametro);
			return EXECUTANDO;
		case 'A':
			cpu->dado += atoi(parametro);
			break;
		case 'D':
			cpu->dado -= atoi(parametro);
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
		case 'E':
			return FINALIZADO;
	}
	cpu->pc++;
}
