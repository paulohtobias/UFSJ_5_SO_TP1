#include "array_list.h"

ArrayList novo_ArrayList(size_t size){
	ArrayList lista;
	
	lista.size = size;
	lista.tamanho_atual = 0;
	lista.tamanho_maximo = LISTA_TAMANHO_MINIMO;
	lista.dados = malloc(lista.tamanho_maximo * lista.size);
	
	return lista;
}

ArrayList arraylist_copia(ArrayList lista){
	ArrayList copia = lista;
	
	copia.dados = malloc(copia.tamanho_maximo * copia.size);
	memcpy(copia.dados, lista.dados, copia.tamanho_maximo * copia.size);
	
	return copia;
}

int arraylist_vazio(const ArrayList lista){
	return (lista.tamanho_atual <= 0);
}

void arraylist_add_fim(ArrayList *lista, const void *dado){
	//Verificando se o dado cabe no array.
	if(lista->tamanho_atual == lista->tamanho_maximo){
		//Aumenta tamanho da lista.
		lista->tamanho_maximo += LISTA_TAMANHO_MINIMO;
		lista->dados = realloc(lista->dados, lista->tamanho_maximo * lista->size);
	}
	
	//Copia o dado para a posição correspondente da lista.
	memcpy(lista->dados + (lista->tamanho_atual * lista->size), dado, lista->size);
	lista->tamanho_atual++;
}

void arraylist_insere_index(ArrayList *lista, const void *dado, int index){
	if(index >= lista->tamanho_atual){
		lista->tamanho_atual = index + 1;
		if(index >= lista->tamanho_maximo){
			lista->tamanho_maximo = index + 1;
			lista->dados = realloc(lista->dados, lista->tamanho_maximo * lista->size);
		}
	}
	memcpy(lista->dados + (index * lista->size), dado, lista->size);
}

void *arraylist_get_index(ArrayList lista, int index, void *dado){
	if(index >= lista.tamanho_atual){
		return NULL;
	}
	return memcpy(dado, lista.dados + (index * lista.size), lista.size);
}

int arraylist_posicao_vazia(ArrayList lista, int (*valido)(const void *)){
	int i;
	for(i=0; i<lista.tamanho_atual; i++){
		void *dado = malloc(lista.size);
		memcpy(dado, lista.dados + (i * lista.size), lista.size);
		if(valido(dado)){
			return i;
		}
	}
	return i;
}

void arrayList_remove_indice(ArrayList *lista, int indice){
	int i;
	for(i = indice; i < lista->tamanho_atual-1; i++){
		arraylist_insere_index(lista, lista->dados+((i+1) * lista->size), i);
	}
	lista->tamanho_atual--;
}