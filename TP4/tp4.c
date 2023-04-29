#include <stdio.h>
#include <stdlib.h>
#include "lib_conjunto.h"
#define MAX 50

conjunto_t **malloc_vet (int tam)
{
    conjunto_t **p;
    p = malloc(tam * sizeof(conjunto_t));
    int i;

    i = 0;
    while ( i < tam)
    {
        p[i] = NULL;
        i++;
    }

    return p;
}

conjunto_t *ler_unico (int elemento)
{
    conjunto_t *cjt;
    int i;
    int j;
    cjt = cria_cjt(MAX);
    cjt->v[0] = elemento;

    scanf("%d", &j);
    i = 1;
    while (j != 0)
    {
        cjt->v[i] = j;
        i++;
        scanf("%d", &j);
    }
    cjt->card = i;

    return cjt;
}

conjunto_t **ler_heroi_missao ()
{
    conjunto_t **p;
    p = malloc_vet(MAX);
    int i;
    int j;

    i = 0;
    scanf("%d", &j);
    while (j != 0)
    {
        p[i] = ler_unico(j);
        i++;
        scanf("%d", &j);
    }
    
    return p;
}

conjunto_t *ler_missao ()
{
    conjunto_t *ler;
    ler = cria_cjt(MAX);
    int i;
    int j;

    j = 0;
    scanf("%d", &i);
    while (i != 0)
    {
        ler->v[j] = i;
        j++;
        scanf("%d", &i);
    }
    ler->card = j;

    return ler;
}

int conta_indices (conjunto_t **conj)
{
    int i;

    i = 0;
    while (conj[i] != NULL)
    {
        i++;
    }

    return i;
}

void unir (conjunto_t *uniao, conjunto_t *heroi)
{
    int i;

    i = 0;
    while (i < cardinalidade_cjt(heroi))
    {
        if (pertence_cjt(uniao,heroi->v[i]) == 0)
            insere_cjt(uniao,heroi->v[i]);
        i++;
    }
}

conjunto_t *uniao (conjunto_t *equipe, conjunto_t **herois)
{
    conjunto_t *uniao;;
    uniao = cria_cjt(MAX);
    int i;
    int j;

    i = 0;
    while (i < cardinalidade_cjt(equipe))
    {
        j = (equipe->v[i] - 1); /* j = indice do heroi */
        unir(uniao,herois[j]);
        i++;
    }

    return uniao;
}

int contido (conjunto_t *missao, conjunto_t *vet)
{
    int i;
    int cont = 0;

    i = 0;
    while (i < cardinalidade_cjt(missao))
    {
        if (pertence_cjt(vet,missao->v[i]) == 1)
            cont++;
        i++;
    }

    if (cont == cardinalidade_cjt(missao))
        return 1;
    return 0;
}

void ordenar (conjunto_t *equipe)
{
    int i;
    int j;
    int temp;

    i = 0;
    while (i < cardinalidade_cjt(equipe))
    {
        j = i;
        while (j < cardinalidade_cjt(equipe))
        {
            if (equipe->v[j] < equipe->v[i])
            {
                temp = equipe->v[i];
                equipe->v[i] = equipe->v[j];
                equipe->v[j] = temp;
            }
            j++;
        }
        i++;
    }
}

void solucao (conjunto_t **herois, conjunto_t *missao, conjunto_t **equipes)
{
    int numero_equipes;
    numero_equipes = conta_indices(equipes);
    conjunto_t **vet;
    vet = malloc_vet(numero_equipes + 1);
    int i;
    int j;
    int k;
    int l;
    int m;
    int cont;

    /* uniao das habilidades de cada equipe em **vet */
    i = 0;
    while (i < numero_equipes)
    {
        vet[i] = uniao(equipes[i],herois);
        i++;
    }

    /* verifica continencia de **vet[indice] e *missao */
    j = 0;
    k = 0;
    cont = 0;
    while (j < numero_equipes)
    {
        if (contido(missao,vet[j]) == 1)
        {
            if (cardinalidade_cjt(equipes[j]) < cardinalidade_cjt(equipes[k]))
                k = j;
            cont = 1;
        }
        j++;
    }

    ordenar(equipes[k]);

    /* impressao */
    if (cont == 0)
        printf ("NENHUMA");
    else
    {
        l = 0;
        while (l < cardinalidade_cjt(equipes[k]))
        {
            printf ("%d", equipes[k]->v[l]);
            if (l < (cardinalidade_cjt(equipes[k]) - 1))
                printf (" ");
            l++;
        }
        printf ("\n");
    }

    /* libera espaço */
    m = 0;
    while (m < conta_indices(vet))
    {
        destroi_cjt(vet[m]);
        m++;
    }
    free(vet);
}

void libera_espaco (conjunto_t **herois, conjunto_t *missao, conjunto_t **equipes)
{
    int i;
    int j;

    i = 0;
    while (i < conta_indices(herois))
    {
        destroi_cjt(herois[i]);
        i++;
    }
    free(herois);

    j = 0;
    while (j < conta_indices(equipes))
    {
        destroi_cjt(equipes[j]);
        j++;
    }
    free(equipes);

    destroi_cjt(missao);
}

int main ()
{
    conjunto_t **herois;
    conjunto_t *missao;
    conjunto_t **equipes;

    /* ler os herois e suas habilidades */
    herois = ler_heroi_missao();

    /* ler a missao */
    missao = ler_missao();

    /* ler as equipes de herois */
    equipes = ler_heroi_missao();

    /* a solucao eh encontrada se a missao esta contido na uniao das 
     * habilidades de uma equipe, mas tomando-se aquela de menor tamanho. */
    solucao(herois,missao,equipes);

    /* libera toda a memoria alocada dinamicamente */
    libera_espaco(herois,missao,equipes);

    return 0;
}
