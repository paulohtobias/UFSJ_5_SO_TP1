#include "tabela_pcb.h"

TabelaPcb novo_item_TabelaPcb(ProcessoSimulado *ps, int pid, int ppid, int prioridade, int tempo_inicio){
	TabelaPcb item;

	item.pid = pid;
	item.ppid = ppid;
	item.ps = ps;
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

void tabela_pcb_imprime_item(TabelaPcb item_tabela, FILE *out){
	fprintf(out, "%3d | %4d | %10d | %5d | %12d | %3d\n",
			item_tabela.pid, item_tabela.ppid, item_tabela.prioridade,
			item_tabela.ps->dado, item_tabela.tempo_inicio, item_tabela.tempo_cpu);
}

void tabela_pcb_imprime(const ArrayList *tabela_pcb){
	FILE *out = fopen("saida.txt", "w");
	if(out == NULL){
		perror("Erro ao criar saida.txt");
		return;
	}
	
	int i;
	for(i=0; i<tabela_pcb->tamanho_atual; i++){
		fprintf(out, "%d;%d;%d\n",
					((TabelaPcb *)tabela_pcb->dados)[i].pid,
					((TabelaPcb *)tabela_pcb->dados)[i].tempo_inicio,
					((TabelaPcb *)tabela_pcb->dados)[i].tempo_final);
	}
	fclose(out);
}
