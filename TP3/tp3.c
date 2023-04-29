#include <stdio.h>
#include <stdlib.h>
#include "lib_racionais.h"
#define MAX 100

/* le um inteiro na faixa [0..MAX-1] */
int ler_tamanho ()
{
    int tamanhos;
    scanf("%d", &tamanhos);
    return tamanhos;
}

/* imprime os racionais apontados pelo vetor de ponteiros para racionais */
void imprimir_vetor_racional (racional **w, int tam)
{
    int i = 0;
    while (i <= tam - 1)
    {
        imprimir_r(w[i]);
        if (i != tam - 1)
            printf (" ");
        i++;
    }
    printf ("\n");
}

/* retorna um vetor de tam ponteiros para numeros racionais validos gerados aleatoriamente */
/* retorna NULL em caso de falha                                                           */
racional** aleatorio_vetor_racional (int tam)
{
    racional **vetor = malloc ((tam) * sizeof(racional*));
    int i = 0;
    while (i < tam)
    {
        vetor[i] = sortear_r();
        i++;
    }
    return vetor;
}

/* retorna um vetor de tam ponteiros para numeros racionais que apontam em ordem crescente para os 
 * racionais apontados pelo vetor recebido no parametro. Defina outras funcoes para te ajudar caso
 * ache necessario */
racional** ordenar_vetor_racional (racional **v, int tam)
{
    racional **w;
    w = malloc ((tam) * sizeof(racional*));
    int a = 0;
    while (a <= tam - 1)
    {
        w[a] = v[a];
        a++;
    }
    int b = 0;
    int c = 0;
    racional *temp;
    while (b <= tam - 1)
    {
        c = b;
        while (c <= tam - 1)
        {
            if ((menor_r(w[c],w[b]) == 1))
            {
                temp = w[b];
                w[b] = w[c];
                w[c] = temp;
            }
            c++;
        }
        b++;
    }
    return w;
}

void livrar_vetor_r (racional **r, int tam)
{
    int i = 0;
    while (i <= tam - 1)
    {
        liberar_r(r[i]);
        i++;
    }
    free(r);
    r = NULL;
}

int main ()
{
    racional **v, **w;
    int tam;
    srand (0);
    tam = ler_tamanho ();
    v = aleatorio_vetor_racional (tam);
    w = ordenar_vetor_racional (v,tam);
    imprimir_vetor_racional (w,tam);
    livrar_vetor_r(v,tam);
    free(w);
    w = NULL;
    return 0;
}