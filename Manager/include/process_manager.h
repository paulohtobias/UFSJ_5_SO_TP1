#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include "cpu.h"
#include "tabela_pcb.h"
#include "array_list.h"

#define FATIA_TEMPO 5

typedef struct ProcessManager{
    int tempo;
    CPU cpu;
    int tabela_pcb;
}ProcessManager;

ProcessManager novo_ProcessManager();

void pm_processar_comandos(ProcessManager *pm);

void pm_processar_comando(ProcessManager *pm, char comando);

void pm_print_estado_atual_sistema(ProcessManager *pm);

#endif //PROCESS_MANAGER_H
