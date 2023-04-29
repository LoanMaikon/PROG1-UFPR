#include <stdlib.h>
#include <stdio.h>
#include "libfila.h"

/* Cria uma fila vazia e a retorna, se falhar retorna NULL. */
fila_t *cria_fila ()
{
    fila_t *fila;

    if (!(fila = malloc(sizeof(fila_t))))
        return NULL;

    fila->tamanho = 0;
    fila->ini = NULL;
    fila->fim = NULL;

    return fila;
}

/* Remove todos os elementos da fila, libera espaco e devolve NULL. */
fila_t *destroi_fila (fila_t *f)
{
    nodo_f_t *aux;

    if (tamanho_fila(f) == 0)
    {
        free(f);
        return NULL;
    }

    while (f->ini != NULL)
    {
        aux = f->ini;
        f->ini = f->ini->prox;
        free(aux);
    }
    
    free(f->ini);
    free(f);

    return NULL;
}

/* Retorna 1 se a fila esta vazia e 0 caso contrario. */
int vazia_fila (fila_t *f)
{
    if (tamanho_fila(f) == 0)
        return 1;
    return 0;
}

/* Retorna o numero de elementos da fila. */
int tamanho_fila (fila_t *f)
{
    return f->tamanho;
}

/* Insere o elemento no final da fila (politica FIFO).
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario. */
int insere_fila (fila_t *f, int elemento)
{
    nodo_f_t *novo;
    
    if (!(novo = malloc(sizeof(nodo_f_t))))
        return 0;
    
    if (f->tamanho != 0)
        f->fim->prox = novo;
    else
        f->ini = novo;

    novo->prox = NULL;
    novo->elem = elemento;
    f->tamanho++;
    f->fim = novo;

    return 1;
}

/* Remove o elemento do inicio da fila (politica FIFO) e o retorna
 * no parametro *elemento. Retorna 1 se a operacao foi bem sucedida
 * e 0 caso contrario. */
int retira_fila (fila_t *f, int *elemento)
{
    nodo_f_t *aux;

    if (f->tamanho == 0)
        return 0;

    *elemento = f->ini->elem;
    f->tamanho--;

    aux = f->ini->prox;
    free(f->ini);
    f->ini = aux;


    return 1;
}

/* para depuracao */
void imprime_fila (fila_t *f)
{
    int i;
    nodo_f_t *aux;

    aux = f->ini;

    i = 1;
    while (i <= tamanho_fila(f))
    {
        printf ("%d ", aux->elem);
        aux = aux->prox;
        i++;
    }
    printf ("\n");
}