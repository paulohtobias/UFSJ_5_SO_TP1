#include "process_manager.h"

///Tabela global de processos.
ArrayList tabela_pcb;
int estado_executando;
ArrayList estado_pronto;
ArrayList estado_blqueado;

ProcessManager pm;

void pm_iniciar(){
	pm.tempo = 0;
	pm.cpu = novo_CPU_processo(FATIA_TEMPO, novo_ProcessoSimulado("../Manager/processos/init.txt"));
	pm.pid_count = 0;
	tabela_pcb = novo_ArrayList(sizeof(TabelaPcb));
	estado_executando = 0;
	estado_pronto = novo_ArrayList(sizeof(int));
	estado_blqueado = novo_ArrayList(sizeof(int));
}

void pm_copiar_processo(ProcessoSimulado *ps){
	TabelaPcb temp;
	//pid do processo em execução.
	arraylist_get_index(tabela_pcb, estado_executando, &temp);
	int ppid = temp.pid;
	
	//pid do filho.
	int pid = arraylist_posicao_vazia(tabela_pcb, tabela_pcb_valido);
	
	//Cria uma nova entrada da tabela pcb.
	temp = novo_item_TabelaPcb(ps, pid, ppid, PRIORIDADE_PADRAO, pm.tempo);
	
	//Adiciona o novo item à tabela.
	arraylist_insere_index(&tabela_pcb, &temp, pid);
	arraylist_add_fim(&estado_pronto, &temp.pid);
}


/* COMANDOS */

void pm_processar_comandos(){
	char comando;
	do{
		comando = getchar();
		if(comando != '\n'){
			printf("Manager Lido: <%c>\n", comando);
			pm_processar_comando(comando);
		}
	}while(comando != 'T');
}

void pm_processar_comando(char comando){
	switch(comando){
		case 'Q':
			pm_executar_instrucao();
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

void pm_executar_instrucao(){
	
	ESTADO estado = cpu_executar_instrucao(&pm.cpu);
	
	//Verificar se o processo precisa ser escaonado.
	if(estado & (FINALIZADO | BLOQUEADO | PRONTO) != 0){
		
	}
	
	//TO-DO: verificar se fatia de tempo acabou, foi bloqueado, etc.
}

void pm_desbloquear_processo(){
	//TO-DO
}

void pm_print_estado_atual_sistema(){
	//TO-DO: precisa abrir um pipe e chamar o reporter.
}

void pm_finaliza(){
	//TO-DO: chama a pm_print_estado_atual_sistema e finaliza
}
