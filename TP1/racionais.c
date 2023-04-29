#include <stdio.h>

typedef struct
{
    int numerador;
    int denominador;
} racional;

racional leitura ()
{
    racional x;
    printf ("Escolha o numerador e o denominador: ");
    scanf ("%d %d", &x.numerador, &x.denominador);
    return x;
}

racional soma (racional x, racional y)
{
    int num, den;
    racional resultado;
    den = x.denominador * y.denominador;
    num = (((den / x.denominador) * x.numerador) + ((den / y.denominador) * y.numerador));
    resultado.numerador = num;
    resultado.denominador = den;
    return resultado;
}

racional subtracao (racional x, racional y)
{
    int num, den;
    racional resultado;
    den = x.denominador * y.denominador;
    num = (((den / x.denominador) * x.numerador) - ((den / y.denominador) * y.numerador));
    resultado.numerador = num;
    resultado.denominador = den;
    return resultado;
}

racional multiplicacao (racional x, racional y)
{
    int num, den;
    racional resultado;
    den = x.denominador * y.denominador;
    num = x.numerador * y.numerador;
    resultado.numerador = num;
    resultado.denominador = den;
    return resultado;
}

racional divisao (racional x, racional y)
{
    int num, den;
    racional resultado;
    num = x.numerador * y.denominador;
    den = x.denominador * y.numerador;
    resultado.numerador = num;
    resultado.denominador = den;
    return resultado;
}

racional mdc (racional x)
{
    int resto, maiordivisor;
    racional xlinha;
    xlinha.numerador = x.numerador;
    xlinha.denominador = x.denominador;
    resto = xlinha.numerador % xlinha.denominador;
    while (resto != 0)
    {
        xlinha.numerador = xlinha.denominador;
        xlinha.denominador = resto;
        resto = xlinha.numerador % xlinha.denominador;
    }
    maiordivisor = xlinha.denominador;
    x.numerador = x.numerador / maiordivisor;
    x.denominador = x.denominador / maiordivisor;
    return x;
}

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