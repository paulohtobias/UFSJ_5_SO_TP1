#include "process_manager.h"

///Tabela global de processos.
ArrayList tabela_pcb;
int estado_executando;
ArrayList estado_pronto;
ArrayList estado_blqueado;
extern void escalonador_troca_contexto();

ProcessManager pm;

void pm_iniciar(){
	pm.tempo = 0;
	pm.cpu = novo_CPU(FATIA_TEMPO);
	pm.pid_count = 0;
	tabela_pcb = novo_ArrayList(sizeof(TabelaPcb));
	estado_executando = 0;
	estado_pronto = novo_ArrayList(sizeof(int));
	estado_blqueado = novo_ArrayList(sizeof(int));
	
	//Adicionando o processo init na tabela pcb.
	ProcessoSimulado *ps_init = novo_ProcessoSimulado("../Manager/processos/init");
	TabelaPcb init = novo_item_TabelaPcb(ps_init, 0, -1, PRIORIDADE_PADRAO, 0);
	cpu_set_processo(&pm.cpu, ps_init);
	
	arraylist_add_fim(&tabela_pcb, &init);
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
	
	printf("%d copiar %d -> ", pid, tabela_pcb.tamanho_atual);
	
	//Adiciona o novo item à tabela.
	arraylist_insere_index(&tabela_pcb, &temp, pid);
	arraylist_add_fim(&estado_pronto, &temp.pid);
	
	printf("%d\n", tabela_pcb.tamanho_atual);
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
			pm_desbloquear_processo();
			break;
		case 'P':
			pm_print_estado_atual_sistema();
			break;
		case 'T':
			pm_finaliza();
			break;
	}
}

void pm_executar_instrucao(){
	
	ESTADO estado = cpu_executar_instrucao(&pm.cpu);
	
	printf("Apos execucao: %d\n", estado);
	
	//Verificar se o processo precisa ser escaonado.
	if((estado & (FINALIZADO | BLOQUEADO | PRONTO)) != 0){
		tabela_pcb_atualiza_estados(&tabela_pcb,estado,estado_executando);
		escalonador_troca_contexto(estado);
	}
	
	
}

void pm_desbloquear_processo(){
	if(arraylist_vazio(estado_blqueado)){
		perror("Nao ha processos bloqueados\n");
		return;
	}
	int pid;
	arraylist_get_index(estado_blqueado,0,&pid);
	arraylist_add_fim(&estado_pronto,&pid);
	arrayList_remove_indice(&estado_blqueado,0);
}

void pm_print_estado_atual_sistema(){
	//TO-DO: atualizar o processo em execuçao com os dados da cpu.
	int i;
	char linha[] = "**********************************************************";
	puts(linha);
	printf("Estado do sistema: %d\n", tabela_pcb.tamanho_atual);
	puts(linha);
	
	printf("TEMPO ATUAL: %d\n", pm.tempo);
	puts("PROCESSO EXECUTANDO:");
	TabelaPcb processo_executando;
	arraylist_get_index(tabela_pcb, estado_executando, &processo_executando);
	printf("pid | ppid | prioridade | valor | tempo_inicio | CPU\n");
	printf("%3d | %4d | %10d | %5d | %12d | %3d\n", processo_executando.pid, processo_executando.ppid,
													processo_executando.prioridade, processo_executando.dado,
													processo_executando.tempo_inicio, processo_executando.tempo_cpu);
	
	puts("BLOQUEADO:");
	TabelaPcb processo_bloqueado;
	int indice;
	for(i=0; i<estado_blqueado.tamanho_atual; i++){
		arraylist_get_index(estado_blqueado, i, &indice);
		arraylist_get_index(tabela_pcb, indice, &processo_bloqueado);
		printf("pid | ppid | prioridade | valor | tempo_inicio | CPU\n");
		printf("%3d | %4d | %10d | %5d | %12d | %3d\n", processo_bloqueado.pid, processo_bloqueado.ppid,
														processo_bloqueado.prioridade, processo_bloqueado.dado,
														processo_bloqueado.tempo_inicio, processo_bloqueado.tempo_cpu);
	}
	
	printf("PROCESSOS PRONTOS: %d\n", estado_pronto.tamanho_atual);
	TabelaPcb processo_pronto;
	for(i=0; i<estado_pronto.tamanho_atual; i++){
		arraylist_get_index(estado_pronto, i, &indice);
		arraylist_get_index(tabela_pcb, indice, &processo_pronto);
		printf("pid | ppid | prioridade | valor | tempo_inicio | CPU\n");
		printf("%3d | %4d | %10d | %5d | %12d | %3d\n", processo_pronto.pid, processo_pronto.ppid,
														processo_pronto.prioridade, processo_pronto.dado,
														processo_pronto.tempo_inicio, processo_pronto.tempo_cpu);
	}
	puts(linha);
	
	/*int pipe[2];
	int pid = fork();
	if(pid == 0){
		close(pipe[FD_WRITE]); 
		dup2(pipe[FD_READ], 0);
		
		//TO-DO - passar os dados para o reporter
		execl("../Reporter/report.out","Passar dados por aki", (char*)NULL);
		perror("Nao criou o reporter");
		exit(-1);
	}*/
}

void pm_finaliza(){
	pm_print_estado_atual_sistema();
	exit(0);
}
