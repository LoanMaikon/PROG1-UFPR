#include "lib_racionais.h"
#include <stdio.h>
#include <stdlib.h>

int aleat (int min, int max)
{
    return min + (rand() % (max - min + 1));
}

racional *criar_r ()
{
    return malloc (sizeof(racional));
}

racional *liberar_r (racional *r)
{
    free (r);
    r = NULL;
    return r;
}

racional *sortear_r ()
{
    racional *ptr = criar_r();
    ptr->den = aleat(1,100);
    ptr->num = aleat(0,100);
    simplifica_r(ptr);
    return ptr;
}

int ler_r (racional *r)
{
    if ((! (scanf ("%d %d", &r->num, &r->den))) || (r->den == 0))
        return 0;
    return 1;
}

void imprimir_r (racional *r)
{
    if ((r->den == 1) || (r->num == 0))
        printf("%d", r->num);
    else
        printf("%d/%d", r->num, r->den);    
    
}
 
int mdc (int a, int b)
{
    if (a % b == 0)
        return b;
    return mdc(b,a%b);
}

int mmc (int a, int b)
{
    return ((a * b) / mdc(a, b));
}

int valido_r (racional *r)
{
    if (r->den == 0)
        return 0;
    return 1;
}

void simplifica_r (racional *r)
{
    int a;
    if (r->num == r-> den)
    {
        r->num = 1;
        r->den = 1;
    }
    else
    {
        a = mdc(r->num,r->den);
        r->num = r->num / a;
        r->den = r->den / a;
    }
}

int menor_r (racional *r1, racional *r2)
{
    if ((float)r1->num / r1->den < (float)r2->num / r2->den)
        return 1;
    return 0;
}

int iguais_r (racional *r1, racional *r)
{
    if ((r1->den == r->den) && (r1->num == r->den))
        return 1;
    return 0;
}

racional *somar_r (racional *r1, racional *r2)
{
    racional *resultado;
    resultado = malloc (sizeof(racional));
    resultado->den = r1->den * r2->den;
    resultado->num = ((resultado->den / r1->den) * r1->num) + ((resultado->den / r2->den) * r2->num);
    simplifica_r(resultado);
    if (resultado->den == 0)
        return NULL;
    return resultado;
    
}

racional *subtrair_r (racional *r1, racional *r2)
{
    racional *resultado;
    resultado = malloc (sizeof(racional));
    resultado->den = r1->den * r2->den;
    resultado->num = ((resultado->den / r1->den) * r1->num) - ((resultado->den / r2->den) * r2->num);
    simplifica_r(resultado);
    if (resultado->den == 0)
        return NULL;
    return resultado;
}

racional *multiplicar_r (racional *r1, racional *r2)
{
    racional *resultado;
    resultado = malloc (sizeof(racional));
    resultado->den = r1->den * r2->den;
    resultado->num = r1->num * r2->num;
    simplifica_r(resultado);
    if (resultado->den == 0)
        return NULL;
    return resultado;
}

racional *dividir_r (racional *r1, racional *r2)
{
    racional *resultado;
    resultado = malloc (sizeof(racional));
    resultado->den = r1->den * r2->num;
    resultado->num = r1->num * r2->den;
    simplifica_r(resultado);
    if (resultado->den == 0)
        return NULL;
    return resultado;
}