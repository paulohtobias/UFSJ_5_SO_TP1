#include "process_manager.h"

ArrayList tabela_pcb;
int estado_executando;
ArrayList estado_pronto;
ArrayList estado_blqueado;

ProcessManager novo_ProcessManager(){
	ProcessManager pm;
	
	pm.tempo = 0;
	pm.cpu = novo_CPU_processo(FATIA_TEMPO, novo_ProcessoSimulado("../Manager/processos/init.txt"));
	tabela_pcb = novo_ArrayList(sizeof(TabelaPcb));
	estado_executando = 0;
	estado_pronto = novo_ArrayList(sizeof(int));
	estado_blqueado = novo_ArrayList(sizeof(int));
	
	return pm;
}

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

void pm_print_estado_atual_sistema(ProcessManager *pm){
	//TO-DO
}
