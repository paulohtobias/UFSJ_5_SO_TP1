#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include "cpu.h"
#include "tabela_pcb.h"

#define FATIA_TEMPO 5
#define PRIORIDADE_PADRAO 10

typedef struct ProcessManager{
    int tempo;
    CPU cpu;
    int tabela_pcb;
	int pid_count;
}ProcessManager;

void pm_iniciar();

void pm_copiar_processo(ProcessoSimulado *ps);

/* COMANDOS */

void pm_processar_comandos();

void pm_processar_comando(char comando);

void pm_executar_instrucao();

void pm_desbloquear_processo();

void pm_print_estado_atual_sistema();

void pm_finaliza();

#endif //PROCESS_MANAGER_H
