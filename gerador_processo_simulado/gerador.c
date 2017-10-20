#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*argv[1] == tamanho maximo em linhas que os processos podem ter
 *argv[2] == quantidade de processos a serem gerados
*/
int main(int argc, char *argv[]){
	srand(time(NULL));
	int i, qnt_ps;
	char comandos[5] = {'S','A','D','B','F'};
	char nome_processo[1024];
	
	for(qnt_ps = 0; qnt_ps < atoi(argv[2]); qnt_ps++){
		int num_linhas = rand()%atoi(argv[1]);

		sprintf(nome_processo,"teste/processo%d",qnt_ps+1);
		FILE *saida = fopen(nome_processo,"w");
		for(i=0; i < num_linhas; i++){
			switch(comandos[rand()%5]){
				case 'S':
					fprintf(saida,"S %d\n",rand()%100);
					break;
				case 'A':
					fprintf(saida,"A %d\n",rand()%100);
					break;
				case 'D':
					fprintf(saida,"D %d\n",rand()%100);
					break;
				case 'B':
					fprintf(saida,"B\n");
					break;
				case 'F':
					fprintf(saida,"F %d\n", rand()%(num_linhas-i));
					break;
			}
		}
		fprintf(saida,"E\n");
		fclose(saida);
	}
return 0;
}
