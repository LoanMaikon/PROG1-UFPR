#include <stdlib.h>
#include <stdio.h>
#include "lib_conjunto.h"

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
    return 1;
}

/*
 * Retorna a cardinalidade do conjunto, isto eh, o numero de elementos presentes nele.
 */
int cardinalidade_cjt (conjunto_t *c)
{
    return c->card;
}

/*
 * Insere o elemento no conjunto, garante que nao existam repeticoes.
 * Retorna 1 se a operacao foi bem sucedida. Se tentar inserir elemento existente,
 * nao faz nada e retorna 1 tambem. Retorna 0 em caso de falha por falta de espaco.
 */
int insere_cjt (conjunto_t *c, int elemento)
{
    int i;
    i = cardinalidade_cjt(c);

    if (!(c->v[i] = elemento))
        return 0;
    else
    {
        c->card = c->card + 1;
        return 1;
    }
}

/*
 * Remove o elemento 'elemento' do conjunto caso ele exista.
 * Retorna 1 se a operacao foi bem sucedida e 0 se o elemento nao existe.
 */
int retira_cjt (conjunto_t *c, int elemento)
{
    return 1;
}

/*
 * Retorna 1 se o elemento pertence ao conjunto e 0 caso contrario.
 */
int pertence_cjt (conjunto_t *c, int elemento)
{
    int i;

    i = 0;
    while (i < cardinalidade_cjt(c))
    {
        if (c->v[i] == elemento)
            return 1;
        i++;
    }

    return 0;
}

/*
 * Retorna 1 se o conjunto c1 esta contido no conjunto c2 e 0 caso contrario.
 */
int contido_cjt (conjunto_t *c1, conjunto_t *c2)
{
    int card1 = cardinalidade_cjt(c1);
    int card2 = cardinalidade_cjt(c2);
    int i;
    int j;
    int k;

    i = 0;
    while (i < (card2 - card1 + 1))
    {
        j = 0;
        k = i;
        while (k < (k + card1))
        {
            if (c1->v[k] == c2->v[k])
                j++;
            k++;
        }
        if (j == card1)
            return 1;
        i++;
    }
    return 0;
}

/*
 * Retorna 1 se o conjunto c1 eh igual ao conjunto c2 e 0 caso contrario.
 */
int sao_iguais_cjt (conjunto_t *c1, conjunto_t *c2)
{
    return 1;
}

/*
 * Cria e retorna o conjunto diferenca entre c1 e c2, nesta ordem.
 * Retorna NULL se a operacao falhou.
 */
conjunto_t *diferenca_cjt (conjunto_t *c1, conjunto_t *c2)
{
    return NULL;
}

/*
 * Cria e retorna o conjunto interseccao entre os conjuntos c1 e c2.
 * Retorna NULL se a operacao falhou.
 */
conjunto_t *interseccao_cjt (conjunto_t *c1, conjunto_t *c2)
{
    return NULL;
}

/*
 * Cria e retorna o conjunto uniao entre os conjunto c1 e c2.
 * Retorna NULL se a operacao falhou.
 */
conjunto_t *uniao_cjt (conjunto_t *c1, conjunto_t *c2)
{
    return NULL;
}

/*
 * Cria e retorna uma copia do conjunto c e NULL em caso de falha.
 */
conjunto_t *copia_cjt (conjunto_t *c)
{
    conjunto_t *copia = cria_cjt(50);
    int i;
    copia->card = cardinalidade_cjt(c);
    copia->max = c->max;

    i = 0;
    while (i < cardinalidade_cjt(copia))
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
    return NULL;
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
    int i = 1;
    i++;
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
    int i = 1;
    i++;
}

/*
 * Devolve no parametro ret_iterador o elemento apontado e incrementa o iterador.
 * A funcao retorna 0 caso o iterador ultrapasse o ultimo elemento, ou retorna
 * 1 caso o iterador aponte para um elemento valido (dentro do conjunto).
 */
int incrementa_iterador_cjt (conjunto_t *c, int *ret_iterador)
{
    return 1;
}

/*
 * Escolhe um elemento qualquer do conjunto para ser removido, o remove e
 * o retorna.
 * Nao faz teste se conjunto eh vazio, deixa para main fazer isso       
 */
int retira_um_elemento_cjt (conjunto_t *c)
{
    return 1;
}