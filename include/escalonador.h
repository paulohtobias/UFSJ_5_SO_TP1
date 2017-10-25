#ifndef ESCALONADOR_H
#define ESCALONADOR_H

#include "process_manager.h"

void escalonador_troca_contexto(ESTADO estado);

/* 
 * POLÍTICAS DE ESCALONAMENTO 
 * 
 * As funções de escalonamento retornam o índice da tabela de índices de pronto.
 */

int escalonador_circular();

int escalonador_prioridades();

int escalonador_loteria();

int escalonador_menor_primeiro();

#endif /* ESCALONADOR_H */
