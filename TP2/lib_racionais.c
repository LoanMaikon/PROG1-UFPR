#include "lib_racionais.h"
#include <stdio.h>

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
