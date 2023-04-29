#include <stdio.h>
#include "lib_racionais.h"

int main()
{
    racional a, b;
    racional resultado_soma, resultado_multiplicacao;
    racional resultado_divisao, resultado_subtracao;
    a = leitura();
    b = leitura();
    while (a.denominador != 0 && b.denominador != 0)
    {
        resultado_subtracao = mdc(subtracao(a,b));
        resultado_divisao = mdc(divisao(a,b));
        resultado_soma = mdc(soma(a,b));
        resultado_multiplicacao = mdc(multiplicacao(a,b));
        printf ("Soma: %d", resultado_soma.numerador);
        if (resultado_soma.denominador != 1)
            printf ("/%d", resultado_soma.denominador);
        printf ("\n\n");
        printf ("Subtração: %d", resultado_subtracao.numerador);
        if (resultado_subtracao.denominador != 1)
            printf ("/%d", resultado_subtracao.denominador);
        printf ("\n\n");
        printf ("Multiplicação: %d", resultado_multiplicacao.numerador);
        if (resultado_multiplicacao.denominador != 1)
            printf ("/%d", resultado_multiplicacao.denominador);
        printf ("\n\n");
        printf ("Divisão: %d", resultado_divisao.numerador);
        if (resultado_divisao.denominador != 1)
            printf ("/%d", resultado_divisao.denominador);
        printf ("\n\n");
        a = leitura();
        b = leitura();
    }
    return 0;
}
