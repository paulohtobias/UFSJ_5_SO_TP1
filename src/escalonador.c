#include "escalonador.h"
#include "cpu.h"
#include "process_manager.h"

extern ArrayList tabela_pcb;
extern int estado_executando;
extern ArrayList estado_pronto;
extern ArrayList estado_blqueado;
extern ProcessManager pm;

void escalonador_troca_contexto(ESTADO estado){
	/*
	 * Decide quem vai entrar na CPU.
	 * Inicialmente assume-se que o estado em execução continuará na CPU. Se a
	 * fila de processos prontos não estiver vazia, então um novo processo poderá
	 * entrar na CPU.
	 */
	int indice_saida;
	int pid_proximo = estado_executando;
	if(!arraylist_vazio(estado_pronto)){
		//indice_saida = escalonador_prioridades();
		indice_saida = escalonador_loteria();
		arraylist_get_index(estado_pronto, indice_saida, &pid_proximo);
	}else{
		/*
		 * Se a fila de prontos estiver vazia, é preciso checar se o estado em
		 * execução já terminou.
		 */
		if(estado == FINALIZADO){
			//arrayList_remove_indice(&tabela_pcb, estado_executando);
			estado_executando = -1;
			printf("Estado em execucao acabou e nao ha mais estados na fila de pronto.\n");
			return;
		}
	}
	printf("ESCALONADOR: %d ===> %d\n", estado_executando, pid_proximo);
	
	//Atualizando o estado na tabela TCB do processo que vai entrar na CPU.
	tabela_pcb_atualiza_estados(&tabela_pcb, EXECUTANDO, pid_proximo);

	//Retira o índice do processo que vai entrar da tabela de pronto.
	arrayList_remove_indice(&estado_pronto, indice_saida);

	//Insere o processo elegido na CPU.
	TabelaPcb tabela;
	arraylist_get_index(tabela_pcb, pid_proximo, &tabela);
	cpu_set_processo(&pm.cpu, tabela.ps);

	//Insere o pid do processo que está saindo na tabela correspondente.
	switch(estado){
		case PRONTO:
			arraylist_add_fim(&estado_pronto, &estado_executando);
			break;
		case BLOQUEADO:
			arraylist_add_fim(&estado_blqueado, &estado_executando);
			break;
		case FINALIZADO:
			((TabelaPcb *)tabela_pcb.dados)[estado_executando].tempo_final=pm.tempo;
			break;
		default:
			break;
	}
	
	//Atualiza o índice do novo processo em execução.
	estado_executando = pid_proximo;
}

/* POLÍTICAS DE ESCALONAMENTO */

int escalonador_fifo(){
	return 0;
}

int escalonador_loteria(){
	return rand() % estado_pronto.tamanho_atual;
}

int escalonador_prioridades(){
	int i, maior = 0;

	int indice, indice_maior;
	//Descobre o processo com a maior prioridade.
	for(i=1; i<estado_pronto.tamanho_atual; i++){
		indice_maior = ((int *)estado_pronto.dados)[maior];
		indice = ((int *)estado_pronto.dados)[i];
		
		//Compara com a prioridade na tabela pcb.
		if(((TabelaPcb *)tabela_pcb.dados)[indice].prioridade > ((TabelaPcb *)tabela_pcb.dados)[indice_maior].prioridade){
			maior = i;
		}
	}
	
	//Diminuindo a prioridade do processo escolhido para evitar starvation.
	((TabelaPcb *)tabela_pcb.dados)[maior].prioridade--;
	
	return maior;
}
