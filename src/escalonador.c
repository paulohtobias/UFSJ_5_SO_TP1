#include "escalonador.h"
#include "cpu.h"
#include "process_manager.h"

extern ArrayList tabela_pcb;
extern int estado_executando;
extern ArrayList estado_pronto;
extern ArrayList estado_blqueado;
extern ProcessManager pm;

void escalonador_troca_contexto(ESTADO estado){
	//Insere o pid do processo que está saindo na tabela correspondente.
	switch(estado){
		case PRONTO:
			arraylist_add_fim(&estado_pronto, &estado_executando);
			break;
		case BLOQUEADO:
			arraylist_add_fim(&estado_blqueado, &estado_executando);
			break;
		default:
			break;
	}

	/*
	 * Decide quem vai entrar na CPU.
	 * Inicialmente assume-se que o estado em execução continuará na CPU. Se a
	 * fila de processos prontos não estiver vazia, então um novo processo poderá
	 * entrar na CPU.
	 */
	int indice_saida;
	int pid_proximo = estado_executando;
	if(estado_pronto.tamanho_atual > 0){
		indice_saida = escalonador_menor_primeiro(estado_executando);
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

	//Atualiza o índice do novo processo em execução.
	estado_executando = pid_proximo;
}

/* POLÍTICAS DE ESCALONAMENTO */

int escalonador_fifo(int pid_atual){
	return 0;
}

int escalonador_menor_primeiro(int pid_atual){
	int i, indice, menor, possivel_menor;
	
	//Tomando o primeiro elemento como menor
	int pid_do_menor = ((int*)estado_pronto.dados)[0];
	/*Calculo do menor é dado por: quantidade de instruções - pc*/
	menor = ((TabelaPcb*)tabela_pcb.dados)[pid_do_menor].ps->array_programa.tamanho_atual -
			((TabelaPcb*)tabela_pcb.dados)[pid_do_menor].ps->pc;
	
	///Buscando qual é o programa com o menor tamanho
	for(i = 0; i < estado_pronto.tamanho_atual ; i++){
		indice = ((int*)estado_pronto.dados)[i]; //Acessando indices da lista

		possivel_menor =((TabelaPcb*)tabela_pcb.dados)[indice].ps->array_programa.tamanho_atual -
						((TabelaPcb*)tabela_pcb.dados)[indice].ps->pc;
						
		if( menor > possivel_menor ){
			///Atualiza o processo de menor tamanho
			pid_do_menor = ((TabelaPcb*)tabela_pcb.dados)[indice].pid;
			menor = ((TabelaPcb*)tabela_pcb.dados)[pid_do_menor].ps->array_programa.tamanho_atual -
					((TabelaPcb*)tabela_pcb.dados)[pid_do_menor].ps->pc;
		}
	}
	return pid_do_menor;
}