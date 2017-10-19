#include "cpu.h"

extern ArrayList tabela_pcb;
extern int estado_executando;
extern ArrayList estado_pronto;
extern ArrayList estado_blqueado;
extern void pm_copiar_processo(ProcessoSimulado ps);

CPU novo_CPU(int fatia_tempo){
	CPU cpu;
	
	cpu.pc = 0;
	cpu.fatia_tempo = fatia_tempo;
	cpu.array_programa = novo_ArrayList(sizeof(Instrucao));
	
	return cpu;
}

CPU novo_CPU_processo(int fatia_tempo, ProcessoSimulado ps){
	CPU cpu = novo_CPU(fatia_tempo);
	
	cpu_set_processo(&cpu, ps);
	
	return cpu;
}

void cpu_set_processo(CPU *cpu, ProcessoSimulado ps){
	cpu->pc = ps.pc;
	cpu->dado = ps.dado;
	cpu->array_programa = arraylist_copia(ps.array_programa);
	cpu->tempo_total = 0;
}

ESTADO cpu_executar_instrucao(CPU *cpu){
	Instrucao instrucao;
	arraylist_get_index(cpu->array_programa, cpu->pc++, &instrucao);
	char *parametro = instrucao.parametro;
	
	ESTADO estado;
	printf("CPU (%d): %c - %s\n", cpu->pc - 1, instrucao.tipo, instrucao.parametro);
	switch(instrucao.tipo){
		case 'S':
			cpu->dado = atoi(parametro);
			estado = EXECUTANDO;
			break;
		case 'A':
			cpu->dado += atoi(parametro);
			estado = EXECUTANDO;
			break;
		case 'D':
			cpu->dado -= atoi(parametro);
			estado = EXECUTANDO;
			break;
		case 'B':
			//TO-DO: bloquear processo
			estado = BLOQUEADO;
			break;
		case 'F':
			pm_copiar_processo(*((ProcessoSimulado *)cpu));
			cpu->pc += atoi(parametro);
			estado = EXECUTANDO;
			break;
		case 'R':
			ps_replace((ProcessoSimulado *)cpu, parametro);
			//Atualizando o PC pra primeira instrução.
			cpu->pc = 0;
			estado = EXECUTANDO; //TO-DO: talvez seja EXECUTANDO.
			break;
		case 'E':
			printf("FIM: %d\n", cpu->dado);
			return FINALIZADO;
	}
	
	//Verifica se o tempo de CPU acabu.
	cpu->tempo_total++;
	
	printf("Tempo: %d/%d\n", cpu->tempo_total, cpu->fatia_tempo);
	
	if(cpu->tempo_total >= cpu->fatia_tempo){
		return PRONTO;
	}

	return estado;
}
