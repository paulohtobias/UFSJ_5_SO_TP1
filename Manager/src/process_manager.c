#include "process_manager.h"

ProcessManager novo_ProcessManager(){
	ProcessManager pm;
	
	pm.tempo = 0;
	pm.cpu = novo_CPU_processo(FATIA_TEMPO, novo_ProcessoSimulado("../Manager/processos/init.txt"));
	pm.tabela = novo_ArrayList(sizeof(TabelaPcb));
	pm.estado_executando = 0;
	pm.estado_pronto = novo_ArrayList(sizeof(int));
	pm.estado_blqueado = novo_ArrayList(sizeof(int));
	
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
			puts("Fim de uma unidade de tempo.");
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
