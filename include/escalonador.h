#ifndef ESCALONADOR_H
#define ESCALONADOR_H

#include "process_manager.h"

void escalonador_troca_contexto(ESTADO estado);

/* POLÍTICAS DE ESCALONAMENTO */

int escalonador_fifo();

int escalonador_prioridades();

int escalonador_loteria();

#endif /* ESCALONADOR_H */
