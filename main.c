#include "processo_simulado.h"

int main(){
	ProcessoSimulado *processo = novo_processo_simulado("./processos/teste.txt");
	printf("%d %d %c %s\n", processo->pc, processo->dado, 
							processo->instrucoes[0].tipo,
							processo->instrucoes[0].parametro);
	
	return 0;
}
