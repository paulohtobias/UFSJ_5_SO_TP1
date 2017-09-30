#include "commander.h"

void *imprime(char valor){
	printf("%c\n",valor);
}

int main(int argc, char *argv[]){
	printf("Main2\n");
	
	char c;
	while(read(0, &c, 1) > 0)
		printf("Main2 lido: %c\n", c);

	return 0;
}
