#include "escalonador.h"

int main(int argc, char** argv) {
	puts("Process Manager");
	
	pm_iniciar();

	pm_processar_comandos();

	return 0;
}
