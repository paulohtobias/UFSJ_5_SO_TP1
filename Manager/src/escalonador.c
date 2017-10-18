#include "escalonador.h"
#include "cpu.h"
#include "process_manager.h"

extern ArrayList tabela_pcb;
extern int estado_executando;
extern ArrayList estado_pronto;
extern ArrayList estado_blqueado;
extern ProcessManager pm;

void escalonador_troca_contexto(ESTADO estado){
	
	//Decide quem vai entrar na CPU.
	int indice;
	int pid_proximo = estado_executando;
	if(estado_pronto.tamanho_atual > 0){
		indice = escalonador_fifo(estado_executando);
		arraylist_get_index(estado_pronto,indice,&pid_proximo);
	}else {
		printf("Vazio %d\n", estado);
		if(estado == FINALIZADO){
			printf("FIM DO PROGRAMA CARALHOU\n");
			return;
		}
	}
	printf("\npid_proximo:%d\n",pid_proximo);
	//Atualizando o estado do processo que saiu na tabela PCB.
	tabela_pcb_atualiza_estados(&tabela_pcb,EXECUTANDO,pid_proximo);
	
	arrayList_remove_indice(&estado_pronto,indice);
	
	TabelaPcb tabela;
	arraylist_get_index(tabela_pcb,pid_proximo,&tabela);
	
	ProcessoSimulado *ps = malloc(sizeof(ProcessoSimulado));
	ps->array_programa = arraylist_copia(tabela.array_programa);
	ps->dado = tabela.dado;
	ps->pc = tabela.pc;
	
	cpu_set_processo(&pm.cpu,ps);
	
	estado_executando = pid_proximo;
}

/* FIFO */

int fifo = 0;

int escalonador_fifo(int pid_atual){
	return 0;
	
	if(fifo + 1 >= estado_pronto.tamanho_atual){
		fifo = 0;
	}
	return fifo++;
}
