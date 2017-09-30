#include "commander.h"

void *imprime(char valor){
	printf("%c\n",valor);
}

int main(int argc, char *argv[]){
	comm_reader(imprime);

	return 0;
}