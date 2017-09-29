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
    int estado_executando;
    ArrayList estado_pronto;
    ArrayList estado_blqueado;
}ProcessManager;

ProcessManager novo_ProcessManager();

void pm_processar_comandos(ProcessManager *pm);

void pm_processar_comando(ProcessManager *pm, char comando);

#endif //PROCESS_MANAGER_H
