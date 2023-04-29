#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "liblef.h"

/* 
 * Cria uma LEF vazia 
 */
lef_t *cria_lef ()
{
    lef_t *lef;

    if (!(lef = malloc(sizeof(lef_t))))
        return 0;

    lef->Primeiro = NULL;

    return lef;
}

/* 
 * Destroi a LEF e retorna NULL. 
 */ 
lef_t *destroi_lef (lef_t *l)
{
    nodo_lef_t *aux;

    while (l->Primeiro != NULL)
    {
        aux = l->Primeiro;
        l->Primeiro = l->Primeiro->prox;
        free(aux->evento);
        free(aux);
    }

    return NULL;
}

/* 
 * Adiciona um evento na primeira posicao da LEF. Uma nova copia
 * da estrutura evento sera feita. 
 * Retorna 1 em caso de sucesso, 0 caso contrario.
 */ 
int adiciona_inicio_lef (lef_t *l, evento_t *evento)
{
    evento_t *novo;
    nodo_lef_t *nodo;

    if (!(nodo = malloc(sizeof(nodo_lef_t))))
        return 0;

    if (!(novo = malloc(sizeof(evento_t))))
        return 0;

    memcpy(novo,evento,sizeof(evento_t));

    if (l->Primeiro == NULL)
        nodo->prox = NULL;
    else
        nodo->prox = l->Primeiro;

    l->Primeiro = nodo;
    nodo->evento = novo;

    return 1;
}

/* 
 * Adiciona um evento de acordo com o valor evento->tempo na LEF. 
 * Uma nova copia da estrutura evento sera feita 
 * Retorna 1 em caso de sucesso, 0 caso contrario.
 */
int adiciona_ordem_lef (lef_t *l, evento_t *evento)
{
    nodo_lef_t *novo, *aux;
    evento_t *ev;

    if (evento->tempo < l->Primeiro->evento->tempo)
        return adiciona_inicio_lef(l,evento);

    if (l->Primeiro == NULL)
        return adiciona_inicio_lef(l,evento);

    if (!(novo = malloc(sizeof(nodo_lef_t))))
        return 0;

    if (!(ev = malloc(sizeof(evento_t))))
        return 0;

    memcpy(ev,evento,sizeof(evento_t));
    aux = l->Primeiro;

    while ((aux->prox != NULL) && (evento->tempo >= aux->prox->evento->tempo))
        aux = aux->prox;

    novo->prox = aux->prox;
    aux->prox = novo;
    novo->evento = ev;

    return 1;
}

/* 
 * Retorna e retira o primeiro evento da LEF. 
 * A responsabilidade por desalocar
 * a memoria associada eh de quem chama essa funcao.
 */
evento_t *obtem_primeiro_lef (lef_t *l)
{
    evento_t *evento;

    evento = l->Primeiro->evento;
    l->Primeiro = l->Primeiro->prox;

    return evento;
}