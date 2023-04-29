#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "libpilha.h"

/* Cria uma pilha com espaço para n elementos do tipo double. 
   Retorna um ponteiro para a pilha ou NULL em caso de erro na 
   alocacao de memoria. */
t_pilha* cria_pilha(int n)
{
    t_pilha *p;

    if (!(p = malloc(sizeof(t_pilha))))
        return NULL;
    if (!(p->v = malloc(n * sizeof(double))))
    {
        free(p);
        return NULL;
    }
    p->tam = n;
    p->topo = -1;

    return p;
}

/* Desaloca a memoria usada pela pilha e retorna NULL */
t_pilha* destroi_pilha(t_pilha *p)
{
    free(p->v);
    free(p);
    p = NULL;

    return NULL;
}

/* Retorna 1 se a pilha p esta vazia e 0 caso contrario. */
int pilha_vazia(t_pilha *p)
{
    if (p->topo == -1)
        return 1;
    return 0;
}

/* Empilha o double x na pilha p. Retorna 1 se a operacao foi 
   realizada com sucesso e 0 caso contrario. */
int empilha (double x, t_pilha *p)
{
    if (p->topo == p->tam - 1)
        return 0;

    p->topo = p->topo + 1;
    p->v[p->topo] = x;
    return 1;
}

/* Retorna em t o elemento do topo da pilha e o desempilha. A funcao 
   retorna 1 se a operacao foi bem sucedida e 0 caso contrario. */
int desempilha(double *t, t_pilha *p)
{
    if (p->topo == -1)
        return 0;
    
    *t = p->v[p->topo];
    p->topo--;
    return 1;
}

/* Retorna em t o elemento do topo da pilha, sem desempilhar. 
   A funcao retorna 1 se a operacao foi bem sucedida e 0 caso 
   contrario.   */
int topo(double *t, t_pilha *p)
{
    if (pilha_vazia(p))
        return 0;
    *t = p->v[p->topo];
    return 1;
}