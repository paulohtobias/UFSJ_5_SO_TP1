#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include "cpu.h"
#include "tabela_pcb.h"
#include "array_list.h"

#define FATIA_TEMPO 5

typedef struct ProcessManager{
    int tempo;
    CPU cpu;
    ArrayList tabela;
    ArrayList estado_execucao;
    ArrayList estado_pronto;
    ArrayList estado_blqueado;
}ProcessManager;

ProcessManager novo_ProcessManager();

#endif //PROCESS_MANAGER_H
