#include "cpu.h"

extern ArrayList tabela_pcb;
extern int estado_executando;
extern ArrayList estado_pronto;
extern ArrayList estado_blqueado;
extern void pm_copiar_processo(ProcessoSimulado *ps);

CPU novo_CPU(int fatia_tempo){
	CPU cpu;
	
	cpu.ps = NULL;
	cpu.fatia_tempo = fatia_tempo;
	
	return cpu;
}

CPU novo_CPU_processo(int fatia_tempo, ProcessoSimulado *ps){
	CPU cpu = novo_CPU(fatia_tempo);
	
	cpu_set_processo(&cpu, ps);
	
	return cpu;
}

void cpu_set_processo(CPU *cpu, ProcessoSimulado *ps){
	cpu->ps = ps;
	cpu->tempo_total = 0;
}

ESTADO cpu_executar_instrucao(CPU *cpu){
	Instrucao instrucao;
	arraylist_get_index(cpu->ps->array_programa, cpu->ps->pc++, &instrucao);
	char *parametro = instrucao.parametro;
	
	ESTADO estado;
	printf("CPU (%d): %c - %s\n", cpu->ps->pc - 1, instrucao.tipo, instrucao.parametro);
	switch(instrucao.tipo){
		case 'S':
			cpu->ps->dado = atoi(parametro);
			estado = EXECUTANDO;
			break;
		case 'A':
			cpu->ps->dado += atoi(parametro);
			estado = EXECUTANDO;
			break;
		case 'D':
			cpu->ps->dado -= atoi(parametro);
			estado = EXECUTANDO;
			break;
		case 'B':
			//TO-DO: bloquear processo
			estado = BLOQUEADO;
			break;
		case 'F':
			pm_copiar_processo(cpu->ps);
			cpu->ps->pc += atoi(parametro);
			estado = EXECUTANDO;
			break;
		case 'R':
			ps_replace(cpu->ps, parametro);
			//Atualizando o PC pra primeira instrução.
			cpu->ps->pc = 0;
			estado = EXECUTANDO; //TO-DO: talvez seja EXECUTANDO.
			break;
		case 'E':
			printf("FIM: %d\n", cpu->ps->dado);
			return FINALIZADO;
	}
	
	//Verifica se o tempo de CPU acabou.
	cpu->tempo_total++;
	
	printf("Tempo: %d/%d\n", cpu->tempo_total, cpu->fatia_tempo);
	
	if(cpu->tempo_total >= cpu->fatia_tempo){
		return PRONTO;
	}

	return estado;
}
