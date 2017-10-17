#include "process_manager.h"

int main(int argc, char** argv) {
	extern ProcessManager pm;
	
	pm_iniciar();

	pm_processar_comandos(&pm);

	return 0;
}
