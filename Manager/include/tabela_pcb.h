#ifndef TABELA_PCB_H
#define TABELA_PCB_H

#include "processo_simulado.h"
#include "array_list.h"

typedef enum ESTADO{
    FINALIZADO, ///Processo já terminou sua execução e pode ser substituído na
                ///TabelaPcb.
    EXECUTANDO, ///Processo está em execução na CPU.
    PRONTO,     ///Processo está pronto para ser executado.
    BLOQUEADO   ///Processo está bloqueado.
}ESTADO;

typedef struct TabelaPcb{
    int pid; ///ID do processo.
    int ppid; ///ID do processo pai.
    int *pc;
    int dado;
    int prioridade;
    ESTADO estado;
    int tempo_inicio; ///"Horário" que o processo foi iniciado.
    int tempo_cpu; ///Tempo total em que o processo passou na CPU.
}TabelaPcb;

TabelaPcb novo_item_TabelaPcb(ProcessoSimulado *ps, int pid, int ppid,
        int prioridade, int tempo_inicio);

void tabelapcb_add_processo(ArrayList *tabela, TabelaPcb *item);

#endif //TABELA_PCB_H
