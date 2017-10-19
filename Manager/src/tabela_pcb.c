#include "tabela_pcb.h"

TabelaPcb novo_item_TabelaPcb(ProcessoSimulado ps, int pid, int ppid, int prioridade, int tempo_inicio){
	TabelaPcb item;

	item.pid = pid;
	item.ppid = ppid;
	item.pc = ps.pc;
	item.dado = ps.dado;
	item.array_programa = arraylist_copia(ps.array_programa);
	item.prioridade = prioridade;
	item.estado = PRONTO;
	item.tempo_inicio = tempo_inicio;
	item.tempo_cpu = 0;

	return item;
}

int tabela_pcb_valido(const void *item){
	return (((TabelaPcb *)item)->estado == FINALIZADO);
}

void tabela_pcb_atualiza_estados(ArrayList *tabela_pcb, ESTADO estado, int indice){
	TabelaPcb processo;
	arraylist_get_index(*tabela_pcb, indice, &processo);
	processo.estado = estado;
	arraylist_insere_index(tabela_pcb,&processo,indice);
}

void tabela_pcb_imprime(TabelaPcb item_tabela){
	printf("%3d | %4d | %10d | %5d | %12d | %3d\n",
		   item_tabela.pid, item_tabela.ppid, item_tabela.prioridade,
		   item_tabela.dado, item_tabela.tempo_inicio, item_tabela.tempo_cpu);
}
