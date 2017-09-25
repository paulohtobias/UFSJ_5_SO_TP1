#include "processo_simulado.h"

int main(){
	ProcessoSimulado *processo = novo_processo_simulado("./processos/teste.txt");
	if(!ps_executar(processo)){
		exit(1);
	}
	printf("%d %d %c %s\n", processo->pc, processo->dado, 
							processo->instrucoes[0].tipo,
							processo->instrucoes[0].parametro);
	
	return 0;
}
