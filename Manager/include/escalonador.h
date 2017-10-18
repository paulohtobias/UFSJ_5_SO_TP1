#ifndef ESCALONADOR_H
#define ESCALONADOR_H

#include "process_manager.h"

void escalonador_troca_contexto();

/* FIFO */
typedef ArrayList FIFO;

int escalonador_fifo(int pid_atual);

#endif /* ESCALONADOR_H */
