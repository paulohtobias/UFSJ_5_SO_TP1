#include "process_manager.h"

///Tabela global de processos.
ArrayList tabela_pcb;
int estado_executando;
ArrayList estado_pronto;
ArrayList estado_blqueado;
extern void escalonador_troca_contexto(ESTADO estado);

ProcessManager pm;

void pm_iniciar(){
	srand( (unsigned)time(NULL) );
	pm.tempo = 0;
	pm.cpu = novo_CPU(FATIA_TEMPO);
	tabela_pcb = novo_ArrayList(sizeof(TabelaPcb));
	estado_executando = 0;
	estado_pronto = novo_ArrayList(sizeof(int));
	estado_blqueado = novo_ArrayList(sizeof(int));

	//Adicionando o processo init na tabela pcb.
	ProcessoSimulado *ps_init = novo_ProcessoSimulado("./processos/init");
	TabelaPcb init = novo_item_TabelaPcb(ps_init, 0, -1, PRIORIDADE_PADRAO, 0);
	cpu_set_processo(&pm.cpu, ps_init);

	arraylist_add_fim(&tabela_pcb, &init);
}

void pm_copiar_processo(ProcessoSimulado *ps) {
	
	//Faz a cópia do processo.
	ProcessoSimulado *copia = ps_copia(ps);
	
	//Descobre o pid do pai.
	TabelaPcb temp;
	arraylist_get_index(tabela_pcb, estado_executando, &temp);
	int ppid = temp.pid;

	//pid do filho.
	int pid = arraylist_posicao_vazia(tabela_pcb, tabela_pcb_valido);

	//Cria uma nova entrada da tabela pcb.
	temp = novo_item_TabelaPcb(copia, pid, ppid, PRIORIDADE_PADRAO, pm.tempo);

	//Adiciona o novo item à tabela.
	arraylist_insere_index(&tabela_pcb, &temp, pid);
	arraylist_add_fim(&estado_pronto, &temp.pid);
}

/* COMANDOS */

void pm_processar_comandos() {
	char comando;
	do {
		comando = getchar();
		if (comando != '\n') {
			printf("Manager Lido: <%c>\n", comando);
			pm_processar_comando(comando);
		}
	} while (comando != 'T');
}

void pm_processar_comando(char comando) {
	switch (comando) {
		case 'Q':
			pm_executar_instrucao();
			pm.tempo++;
			break;
		case 'U':
			pm_desbloquear_processo();
			pm.tempo++;
			break;
		case 'P':
			pm_print_estado_atual_sistema();
			break;
		case 'T':
			pm_finaliza();
			break;
	}
}

void pm_executar_instrucao() {

	if (estado_executando == -1) {
		if (!arraylist_vazio(estado_pronto)) {
			escalonador_troca_contexto(0);
		} else {
			puts("Nao ha processos na fila de pronto!");
			return;
		}
	}
	ESTADO estado = cpu_executar_instrucao(&pm.cpu);

	//Verificar se o processo precisa ser escaonado.
	if ((estado & (FINALIZADO | BLOQUEADO | PRONTO)) != 0) {
		((TabelaPcb *)tabela_pcb.dados)[estado_executando].tempo_cpu += pm.cpu.tempo_total;
		tabela_pcb_atualiza_estados(&tabela_pcb, estado, estado_executando);
		escalonador_troca_contexto(estado);
	}
}

void pm_desbloquear_processo() {
	if (arraylist_vazio(estado_blqueado)) {
		printf("Nao ha processos bloqueados\n");
		return;
	}
	int pid;
	arraylist_get_index(estado_blqueado, 0, &pid);
	arrayList_remove_indice(&estado_blqueado, 0);
	arraylist_add_fim(&estado_pronto, &pid);
	tabela_pcb_atualiza_estados(&tabela_pcb, PRONTO, pid);
}

void pm_print_estado_atual_sistema() {
	int pipefd[2];
	pipe(pipefd);
	int pid = fork();

	switch (pid) {
		case -1:
			perror("Process Manager: Error no fork\n");
			break;
		case 0:
			close(pipefd[FD_WRITE]);
			dup2(pipefd[FD_READ], 0);

			if (execl("./reporter.out", "./reporter.out", (char *) NULL) == -1) {
				perror("pm_reporter_filho");
				exit(0);
			}

			exit(0);
		default:
			close(pipefd[FD_READ]);
			int stdout_old = dup(1);
			dup2(pipefd[FD_WRITE], 1);
			{	
				int i;
				char linha[] = "**********************************************************";
				char cabecalho[] = "pid | ppid | prioridade | valor | tempo_inicio | CPU";
				puts(linha);
				printf("Estado do sistema: %d\n", tabela_pcb.tamanho_atual);
				puts(linha);

				printf("TEMPO ATUAL: %d\n", pm.tempo);
				puts("PROCESSO EXECUTANDO:");
				if (estado_executando != -1) {
					TabelaPcb processo_executando;
					arraylist_get_index(tabela_pcb, estado_executando, &processo_executando);
					puts(cabecalho);
					tabela_pcb_imprime(processo_executando);
				}
				puts("\nBLOQUEADO:");
				TabelaPcb processo_bloqueado;
				int indice;
				puts(cabecalho);
				for (i = 0; i < estado_blqueado.tamanho_atual; i++) {
					arraylist_get_index(estado_blqueado, i, &indice);
					arraylist_get_index(tabela_pcb, indice, &processo_bloqueado);
					tabela_pcb_imprime(processo_bloqueado);
				}

				printf("\nPROCESSOS PRONTOS: %d\n", estado_pronto.tamanho_atual);
				TabelaPcb processo_pronto;
				puts(cabecalho);
				for (i = 0; i < estado_pronto.tamanho_atual; i++) {
					arraylist_get_index(estado_pronto, i, &indice);
					arraylist_get_index(tabela_pcb, indice, &processo_pronto);
					tabela_pcb_imprime(processo_pronto);
				}
				printf("\n");
				puts(linha);

				//Fecha o pipe pra escrita.
				if (close(pipefd[FD_WRITE]) == -1) {
					perror("pm_reporter_pai");
				}
				dup2(stdout_old, 1);
				close(stdout_old);

				//Espera o filho terminar.
				wait(NULL);
			}
			break;
	}
}

void pm_finaliza() {
	pm_print_estado_atual_sistema();
	exit(0);
}
