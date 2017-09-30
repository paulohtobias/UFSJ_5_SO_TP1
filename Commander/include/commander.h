#ifndef _COMMANDER_H_
#define _COMMANDER_H_

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_BUFF 1 ///Tamanho máximo do buffer de recebimento

void commander(char* name); ///Faz a leitura dos comandos em arquivo
void comm_reader(void *(*p_manager)(char)); ///Lê os comandos enviados pela rede
#endif //_COMMANDER_H_