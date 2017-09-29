#include "process_manager.h"

ProcessManager novo_ProcessManager(){
	ProcessManager pm;
	
	pm.tempo = 0;
	pm.cpu = novo_CPU_processo(FATIA_TEMPO, novo_ProcessoSimulado("processos/init.txt"));
	pm.tabela = novo_ArrayList(sizeof(TabelaPcb));
	pm.estado_executando = 0;
	pm.estado_pronto = novo_ArrayList(sizeof(int));
	pm.estado_blqueado = novo_ArrayList(sizeof(int));
	
	return pm;
}

void pm_processar_comandos(ProcessManager *pm){
	
}

void pm_processar_comando(ProcessManager *pm, char comando){
	
}
