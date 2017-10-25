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

void cpu_set_processo(CPU *cpu, ProcessoSimulado *ps){
	cpu->ps = ps;
	cpu->tempo_total = 0;
}

ESTADO cpu_executar_instrucao(CPU *cpu){
	Instrucao instrucao;
	arraylist_get_index(cpu->ps->array_programa, cpu->ps->pc++, &instrucao);
	char *parametro = instrucao.parametro;
	
	ESTADO estado;
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
			estado = EXECUTANDO;
			break;
		case 'E':
			return FINALIZADO;
	}
	
	//Verifica se o tempo de CPU acabou.
	cpu->tempo_total++;
	if(cpu->tempo_total >= cpu->fatia_tempo){
		return PRONTO;
	}

	return estado;
}
