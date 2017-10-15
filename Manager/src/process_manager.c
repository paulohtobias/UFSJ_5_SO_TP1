#include "process_manager.h"

///Tabela global de processos.
ArrayList tabela_pcb;
int estado_executando;
ArrayList estado_pronto;
ArrayList estado_blqueado;

ProcessManager novo_ProcessManager(){
	ProcessManager pm;

	pm.tempo = 0;
	pm.cpu = novo_CPU_processo(FATIA_TEMPO, novo_ProcessoSimulado("../Manager/processos/init.txt"));
	pm.pid_count = 0;
	tabela_pcb = novo_ArrayList(sizeof(TabelaPcb));
	estado_executando = 0;
	estado_pronto = novo_ArrayList(sizeof(int));
	estado_blqueado = novo_ArrayList(sizeof(int));

	return pm;
}

void pm_add_processo(ProcessManager *pm, ProcessoSimulado *processo){
	TabelaPcb novo_processo;
}


/* COMANDOS */

void pm_processar_comandos(ProcessManager *pm){
	char comando;
	do{
		comando = getchar();
		if(comando != '\n'){
			printf("Manager Lido: <%c>\n", comando);
			pm_processar_comando(pm, comando);
		}
	}while(comando != 'T');
}

void pm_processar_comando(ProcessManager *pm, char comando){
	switch(comando){
		case 'Q':
			cpu_executar_instrucao(&pm->cpu);
			//TO-DO: verificar se fatia de tempo acabou, foi bloqueado, etc.
			break;
		case 'U':
			
			puts("Desbloqueie o primeiro processo simulado que está na fila de bloqueados.");
			break;
		case 'P':
			puts("Imprima o estado atual do sistema.");
			break;
		case 'T':
			puts("Imprima o tempo de retorno médio e finalize o simulador.");
			break;
	}
}

void pm_executar_instrucao(ProcessManager *pm){
	//TO-DO: chamar o cpu_executar instruçao antes.
	//O escalonamento é feito aqui. Devem ter outras coisas tbm.
}

void pm_desbloquear_processo(ProcessManager *pm){
	//TO-DO
}

void pm_print_estado_atual_sistema(ProcessManager *pm){
	//TO-DO: precisa abrir um pipe e chamar o reporter.
}

void pm_finaliza(ProcessManager *pm){
	//TO-DO: chama a pm_print_estado_atual_sistema e finaliza
}
