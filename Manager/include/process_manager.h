#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include "cpu.h"
#include "tabela_pcb.h"
#include "array_list.h"

#define FATIA_TEMPO 5

typedef struct ProcessManager{
    int tempo;
    CPU cpu;
    TabelaPcb *tabela;
    int *estado_execucao;
    int *estado_pronto;
    int *estado_bloqueado;
}ProcessManager;

ProcessManager novo_ProcessManager();

#endif //PROCESS_MANAGER_H
