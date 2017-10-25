#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include "cpu.h"
#include "tabela_pcb.h"
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>


#define FATIA_TEMPO 10
#define PRIORIDADE_PADRAO 10

#define FD_READ 0
#define FD_WRITE 1

typedef struct ProcessManager{
    int tempo;
    CPU cpu;
}ProcessManager;

///Inicializa as estruturas principais do programa.
void pm_iniciar();

///Faz a cópia de um processo simulado e o adiciona na tabela de pronto.
void pm_copiar_processo(ProcessoSimulado *ps);

/* COMANDOS */

///Lê comandos da entrada padrão.
void pm_processar_comandos();

///Interpreta os comandos e chama as funções correspondentes.
void pm_processar_comando(char comando);

/**
 * Executa a próxima instrução do processo em execução e faz o escalonamento,
 * caso necessário.
 */
void pm_executar_instrucao();

///Move o primeiro processo bloqueado para a lista de prontos.
void pm_desbloquear_processo();

///Exibe na saída padrão o estado atual do sistema.
void pm_print_estado_atual_sistema();

///Exibe o estado atual e finaliza.
void pm_finaliza();

#endif //PROCESS_MANAGER_H
