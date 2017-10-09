#include "processo_simulado.h"
#include "process_manager.h"

int main(int argc, char** argv) {
	ProcessManager pm = novo_ProcessManager();

	pm_processar_comandos(&pm);

	return 0;
}

