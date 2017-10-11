#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include "cpu.h"
#include "tabela_pcb.h"

#define FATIA_TEMPO 5

typedef struct ProcessManager{
    int tempo;
    CPU cpu;
    int tabela_pcb;
}ProcessManager;

ProcessManager novo_ProcessManager();

void pm_processar_comandos(ProcessManager *pm);

void pm_processar_comando(ProcessManager *pm, char comando);

void pm_executar_instrucao(ProcessManager *pm);

void pm_desbloquear_processo(ProcessManager *pm);

void pm_print_estado_atual_sistema(ProcessManager *pm);

void pm_finaliza(ProcessManager *pm);

#endif //PROCESS_MANAGER_H
