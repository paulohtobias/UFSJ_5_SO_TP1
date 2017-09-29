#include "processo_simulado.h"

int main(int argc, char** argv) {
	ProcessoSimulado ps = novo_ProcessoSimulado("processos/init.txt");
	
	int i;
	for(i=0; ps.instrucoes[i].tipo != 'E'; i++){
		printf("%c %s\n", ps.instrucoes[i].tipo, ps.instrucoes[i].parametro);
	}
	
	return 0;
}

