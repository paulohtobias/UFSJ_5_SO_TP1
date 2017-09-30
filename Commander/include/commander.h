#ifndef _COMMANDER_H_
#define _COMMANDER_H_

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

void commander(char* name);
void comm_reader(void *(*p_manager)(char));
#endif //_COMMANDER_H_