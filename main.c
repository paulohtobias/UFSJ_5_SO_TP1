#include "escalonador.h"

int main(int argc, char** argv) {
	puts("Process Manager");
	extern ProcessManager pm;
	
	pm_iniciar();

	pm_processar_comandos(&pm);

	return 0;
}
