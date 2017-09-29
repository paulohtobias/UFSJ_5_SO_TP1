#include "process_manager.h"

ProcessManager novo_ProcessManager(){
	ProcessManager pm;
	
	pm.tempo = 0;
	//pm.cpu = novo_CPU_processo(FATIA_TEMPO, novo_processo_simulado("processos/init.txt"));
	
	ArrayList list = novo_ArrayList(sizeof(int));
	
	return pm;
}
