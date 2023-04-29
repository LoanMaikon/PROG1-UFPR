#include <stdlib.h>
#include <stdio.h>
#include "libconjunto.h"

int aleatorio (int min, int max)
{
    return min + (rand() % (max - min + 1));
}

/*
 * Cria um conjunto vazio e o retorna, se falhar retorna NULL.
 * max eh o tamanho maximo do conjunto, isto eh, o tamanho maximo do vetor
 */
conjunto_t *cria_cjt (int max)
{
    conjunto_t *conj;

    if (!(conj = malloc(sizeof(conjunto_t))))
        return NULL;

    if (!(conj->v = malloc(max * sizeof(conjunto_t))))
    {
        free(conj);
        return NULL;
    }

    conj->max = max;
    conj->card = 0;

    return conj;
}

/*
 * Remove todos os elementos do conjunto, libera espaco e devolve NULL.
 */
conjunto_t *destroi_cjt (conjunto_t *c)
{
    free(c->v);
    free(c);
    c = NULL;

    return NULL;
}

/*
 * Retorna 1 se o conjunto esta vazio e 0 caso contrario.
 */
int vazio_cjt (conjunto_t *c)
{
    if (cardinalidade_cjt(c) == 0)
        return 1;
    return 0;
}

/*
 * Retorna a cardinalidade do conjunto, isto eh, o numero de elementos presentes nele.
 */
int cardinalidade_cjt (conjunto_t *c)
{
    return c->card;
}

void ordenar (conjunto_t *conj)
{
    int i;
    int j;
    int temp;

    i = 0;
    while (i < cardinalidade_cjt(conj))
    {
        j = i;
        while (j < cardinalidade_cjt(conj))
        {
            if (conj->v[j] < conj->v[i])
            {
                temp = conj->v[i];
                conj->v[i] = conj->v[j];
                conj->v[j] = temp;
            }
            j++;
        }
        i++;
    }
}

/*
 * Insere o elemento no conjunto, garante que nao existam repeticoes.
 * Retorna 1 se a operacao foi bem sucedida. Se tentar inserir elemento existente,
 * nao faz nada e retorna 1 tambem. Retorna 0 em caso de falha por falta de espaco.
 */
int insere_cjt (conjunto_t *c, int elemento)
{
    int i;

    if (cardinalidade_cjt(c) == c->max)
        return 0;

    if (cardinalidade_cjt(c) == 0)
    {
        c->v[0] = elemento;
        c->card++;
        return 1;
    }

    if (!(pertence_cjt(c,elemento)))
    {
        i = cardinalidade_cjt(c);
        c->v[i] = elemento;
        c->card++;
        ordenar(c);
    }

    return 1;
}

int busca_binaria (int x, conjunto_t *c)
{
    int ini, meio, fim;

    ini = 0;
    fim = cardinalidade_cjt(c) - 1;
    meio = (ini + fim) / 2;
    while ((ini <= fim) && (x != c->v[meio]))
    {
        if (x < c->v[meio])
            fim = meio - 1;
        else
            ini = meio + 1;
        meio = (ini + fim) / 2;
    }

    if (fim < ini)
        return -1;
    return meio;
}

/*
 * Remove o elemento 'elemento' do conjunto caso ele exista.
 * Retorna 1 se a operacao foi bem sucedida e 0 se o elemento nao existe.
 */
int retira_cjt (conjunto_t *c, int elemento)
{
    int indice;

    indice = busca_binaria(elemento,c);

    if (indice == -1)
        return 0;
    
    while (indice < cardinalidade_cjt(c))
    {
        c->v[indice] = c->v[indice + 1];
        indice++;
    }
    c->card--;

    return 1;
}

/*
 * Retorna 1 se o elemento pertence ao conjunto e 0 caso contrario.
 */
int pertence_cjt (conjunto_t *c, int elemento)
{
    if (busca_binaria(elemento,c) == -1)
        return 0;
    return 1;
}

/*
 * Retorna 1 se o conjunto c1 esta contido no conjunto c2 e 0 caso contrario.
 */
int contido_cjt (conjunto_t *c1, conjunto_t *c2)
{
    int i;

    if (cardinalidade_cjt(c1) > cardinalidade_cjt(c2))
        return 0;
    
    i = 0;
    while (i < cardinalidade_cjt(c1))
    {
        if (!(pertence_cjt(c2,c1->v[i])))
            return 0;
        i++;
    }

    return 1;
}

/*
 * Retorna 1 se o conjunto c1 eh igual ao conjunto c2 e 0 caso contrario.
 */
int sao_iguais_cjt (conjunto_t *c1, conjunto_t *c2)
{
    int i;

    if (cardinalidade_cjt(c1) != cardinalidade_cjt(c2))
        return 0;
    
    i = 0;
    while ((i < cardinalidade_cjt(c1)) && (c1->v[i] = c2->v[i]))
        i++;
    
    if (i < cardinalidade_cjt(c1))
        return 0;
    return 1;
}

/*
 * Cria e retorna o conjunto diferenca entre c1 e c2, nesta ordem.
 * Retorna NULL se a operacao falhou.
 */
conjunto_t *diferenca_cjt (conjunto_t *c1, conjunto_t *c2)
{
    int i, j, k;
    conjunto_t *dif;
    dif = cria_cjt(100);

    i = 0;
    j = 0;
    k = 0;
    while ((i < cardinalidade_cjt(c1)) && (j < cardinalidade_cjt(c2)))
    {
        if (c1->v[i] < c2->v[j])
        {
            dif->v[k] = c1->v[i];
            i++;
            k++;
        }
        else
        if (c1->v[i] > c2->v[j])
            j++;
        else
        {
            i++;
            j++;
        }
    }

    while (i < cardinalidade_cjt(c1))
    {
        dif->v[k] = c1->v[i];
        k++;
        i++;
    }
    dif->card = k;

    return dif;
}

/*
 * Cria e retorna o conjunto interseccao entre os conjuntos c1 e c2.
 * Retorna NULL se a operacao falhou.
 */
conjunto_t *interseccao_cjt (conjunto_t *c1, conjunto_t *c2)
{
    int i, j, k;
    conjunto_t *inter;
    inter = cria_cjt(100);

    i = 0;
    j = 0;
    k = 0;
    while ((i < cardinalidade_cjt(c1)) && (j < cardinalidade_cjt(c2)))
    {
        if (c1->v[i] < c2->v[j])
            i++;
        else
        if (c1->v[i] > c2->v[j])
            j++;
        else
        {
            inter->v[k] = c1->v[i];
            k++;
            i++;
            j++;
        }
    }
    inter->card = k;

    return inter;
}

/*
 * Cria e retorna o conjunto uniao entre os conjunto c1 e c2.
 * Retorna NULL se a operacao falhou.
 */
conjunto_t *uniao_cjt (conjunto_t *c1, conjunto_t *c2)
{
    int i, j, k, l;
    conjunto_t *uniao;
    uniao = cria_cjt(10);

    i = 0;
    j = 0;
    k = 0;
    while ((i < cardinalidade_cjt(c1)) && (j < cardinalidade_cjt(c2)))
    {
        if (c1->v[i] < c2->v[j])
        {
            uniao->v[k] = c1->v[i];
            i++;
        }
        else
        if (c1->v[i] > c2->v[j])
        {
            uniao->v[k] = c2->v[j];
            j++;
        }
        else
        {
            uniao->v[k] = c1->v[i];
            i++;
            j++;
        }
        k++;
    }

    l = i;
    while (l < cardinalidade_cjt(c1))
    {
        uniao->v[k] = c1->v[l];
        k++;
        l++;
    }

    l = j;
    while (l < cardinalidade_cjt(c2))
    {
        uniao->v[k] = c2->v[l];
        k++;
        l++;
    }
    uniao->card = k;

    return uniao;
}

/*
 * Cria e retorna uma copia do conjunto c e NULL em caso de falha.
 */
conjunto_t *copia_cjt (conjunto_t *c)
{
    int i;
    conjunto_t *copia;
    copia = cria_cjt(10);
    
    copia->card = c->card;

    i = 0;
    while (i < cardinalidade_cjt(c))
    {
        copia->v[i] = c->v[i];
        i++;
    }

    return copia;
}

/*
 * Cria e retorna um subconjunto com elementos aleatorios do conjunto c.
 * Se o conjunto for vazio, retorna um subconjunto vazio.
 * Se n >= cardinalidade (c) entao retorna o proprio conjunto c.
 * Supoe que a funcao srand () tenha sido chamada antes.
 */
conjunto_t *cria_subcjt_cjt (conjunto_t *c, int n)
{
    int i, indice;
    conjunto_t *sub;
    sub = cria_cjt(n);

    if (cardinalidade_cjt(c) == 0)
    {
        destroi_cjt(sub);
        return c;
    }

    if (n >= cardinalidade_cjt(c))
    {
        destroi_cjt(sub);
        return c;
    }

    i = 0;
    while (i < n)
    {
        indice = aleatorio(0,cardinalidade_cjt(c)-1);
        insere_cjt(sub,c->v[indice]);
        i++;
    }

    return sub;
}

/*
 * Imprime os elementos do conjunto sempre em ordem crescente,
 * mesmo que a estrutura interna nao garanta isso.
 * Na impressao os elementos sao separados por um unico espaco
 * em branco entre os elementos, sendo que apos o ultimo nao
 * deve haver espacos em branco. Ao final imprime um \n.
 */
void imprime_cjt (conjunto_t *c)
{
    int i;

    if (vazio_cjt(c) == 1)
    {
        printf("VAZIO\n");
        return;
    }

    i = 0;
    while (i < (cardinalidade_cjt(c) - 1))
    {
        printf ("%d ", c->v[i]);
        i++;
    }
    printf ("%d\n", c->v[i]);
}

/*
 * As funcoes abaixo implementam um iterador que vao permitir
 * percorrer os elementos do conjunto.
 * O ponteiro ptr da struct (iterador) pode ser inicializado para apontar 
 * para o primeiro elemento e incrementado ate' o ultimo elemento 
 * do conjunto.
 */

/*
 * Inicializa ptr usado na funcao incrementa_iterador 
 */
void inicia_iterador_cjt (conjunto_t *c)
{
    c->ptr = 0;
}

/*
 * Devolve no parametro ret_iterador o elemento apontado e incrementa o iterador.
 * A funcao retorna 0 caso o iterador ultrapasse o ultimo elemento, ou retorna
 * 1 caso o iterador aponte para um elemento valido (dentro do conjunto).
 */
int incrementa_iterador_cjt (conjunto_t *c, int *ret_iterador)
{
    if (c->ptr == cardinalidade_cjt(c))
        return 0;

    *ret_iterador = c->v[c->ptr];
    c->ptr++;

    return 1;
}

/*
 * Escolhe um elemento qualquer do conjunto para ser removido, o remove e
 * o retorna.
 * Nao faz teste se conjunto eh vazio, deixa para main fazer isso       
 */
int retira_um_elemento_cjt (conjunto_t *c)
{
    int indice;
    int elemento;

    indice = cardinalidade_cjt(c) - 1;
    elemento = c->v[indice];
    retira_cjt(c,elemento);

    return elemento;
}