#include "escalonador.h"

extern ProcessManager pm;
extern ArrayList tabela_pcb;
extern int estado_executando;
extern ArrayList estado_pronto;
extern ArrayList estado_blqueado;

void escalonador_troca_contexto(ESTADO estado){
	
	//Decide quem vai entrar na CPU.
	int pid_proximo = estado_executando;
	if(estado_pronto.tamanho_atual > 0){
		pid_proximo = escalonador_fifo(estado_executando);
	}
	
	
	
	//Faz a troca de contexto.
	if(estado == FINALIZADO){
		arrayList_remove_indice(&tabela_pcb,estado_executando);
	}
	
	//Atualizando o estado do processo que saiu na tabela PCB.
	tabela_pcb_atualiza_estados(&tabela_pcb,estado,estado_executando);
	tabela_pcb_atualiza_estados(&tabela_pcb,EXECUTANDO,pid_proximo);
	
	arrayList_remove_indice(&estado_pronto,pid_proximo);
	estado_executando = pid_proximo;
	
	
	//((TabelaPcb *)tabela_pcb.dados)[estado_executando] = estado;
	
}

/* FIFO */

int fifo = 0;

int escalonador_fifo(int pid_atual){
	if(fifo + 1 >= estado_pronto.tamanho_atual){
		fifo = 0;
	}
	return fifo++;
}
