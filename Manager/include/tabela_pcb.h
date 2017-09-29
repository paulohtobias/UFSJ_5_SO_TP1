#ifndef TABELA_PCB_H
#define TABELA_PCB_H

typedef enum ESTADO{
    PRONTO,
    BLOQUEADO,
    EXECUTANDO
}ESTADO;

typedef struct TabelaPcb{
    int pid; ///ID do processo.
    int ppid; ///ID do processo pai.
    int *pc;
    int dado;
    int prioridade;
    ESTADO estado;
    int tempo_inicio; ///"Horario" que o processo foi iniciado.
    int tempo_cpu; ///Tempo total em que o processo passou na CPU.
}TabelaPcb;

#endif //TABELA_PCB_H
