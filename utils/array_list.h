#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdlib.h>
#include <string.h>

#define LISTA_TAMANHO_MINIMO 10

typedef struct ArrayList{
	int tamanho_atual;
    int tamanho_maximo;
	size_t size;
    void *dados;
}ArrayList;

ArrayList novo_ArrayList(size_t size);

/**
 * Insere uma cópia de <code>dado</code> ao final do array de <code>lista</code>.
 * O array da lista se expande quando o tamanho excede o máximo.
 * 
 * @param lista um <code>ArrayList</code>
 * @param dado endereço do dado que será copiado para o final da lista.
 */
void arraylist_add_fim(ArrayList *lista, const void *dado);

/**
 * Substitui o dado na posição <code>index</code> de <code>lista</code> por uma
 * cópia de <code>dado</code>.
 * 
 * @param lista um <code>ArrayList</code>
 * @param dado endereço do dado que será copiado para o final da lista.
 * @param index posição da lista que <code>dado</code> será inserido.
 */
void arraylist_insere_index(ArrayList *lista, const void *dado, int index);

/**
 * Copia o dado na posição <code>index</code> de <code>lista</code> para o
 * endereço apontado por <code>dado</code>.
 * 
 * @param lista um <code>ArrayList</code>
 * @param index posição da lista que <code>dado</code> de onde será feita a
 * cópia.
 * @param dado endereço para onde os dados serão copiados.
 * @return endereço para onde os dados foram copiados. Pode ser
 *         seguramente ignorado.
 */
void *arraylist_get_index(ArrayList *lista, int index, void *dado);

#endif //ARRAY_LIST_H
