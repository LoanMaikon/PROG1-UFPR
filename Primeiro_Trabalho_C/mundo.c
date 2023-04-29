#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include "libconjunto.h"
#include "libfila.h"
#include "liblef.h"
#define FIM_DO_MUNDO 34944
#define MAX 100

typedef struct herois
{
    int id;
    int exp;
    int paciencia;
    int idade;
    conjunto_t *habilidades;
} herois_t;

typedef struct coordenadas
{
    int x;
    int y;
} coordenadas_t;

typedef struct locais
{
    int id;
    int lot_max;
    coordenadas_t *coord;
    conjunto_t *publico;
    fila_t *fila;
} locais_t;

typedef struct mundo
{
    int tempo;
    int tam_mundo;
    int n_habs;
    int n_herois;
    int n_locais;
    int n_missoes;
    herois_t **v_herois;
    locais_t **v_locais;
    conjunto_t *habs;
} mundo_t;

mundo_t *setar_mundo ()
{
    mundo_t *mundo;

    if (!(mundo = malloc(sizeof(mundo_t))))
        return 0;

    mundo->tempo = 0;
    mundo->tam_mundo = 20000;
    mundo->n_habs = 10;
    mundo->n_herois = mundo->n_habs * 5;
    mundo->n_locais = mundo->n_herois / 6;
    mundo->n_missoes = FIM_DO_MUNDO / 100;

    return mundo;
}

int aleat (int min, int max)
{
    return (min + (rand() % (max - min + 1)));
}

int maximiza (int min, int conta)
{
    if (conta < min)
        return min;
    return conta;
}

herois_t *cria_unico_heroi (mundo_t *mundo, int i)
{
    herois_t *heroi;
    if (!(heroi = malloc(sizeof(herois_t))))
        return 0;

    heroi->habilidades = cria_subcjt_cjt(mundo->habs,aleat(2,5));
    heroi->id = i;
    heroi->exp = 0;
    heroi->paciencia = aleat(0,100);
    heroi->idade = aleat(18,100);

    return heroi;
}

herois_t **cria_herois (mundo_t *mundo)
{
    int i;
    herois_t **vh;
    if (!(vh = malloc(mundo->n_herois * sizeof(herois_t*))))
        return 0;

    i = 0;
    while (i < mundo->n_herois)
    {
        vh[i] = cria_unico_heroi(mundo,i);
        i++;
    }

    return vh;
}

locais_t *cria_unico_local (mundo_t *mundo, int i)
{
    int tam;
    locais_t *local;

    if (!(local = malloc(sizeof(locais_t))))
        return 0;
    
    if (!(local->coord = malloc(sizeof(coordenadas_t))))
        return 0;

    tam = aleat(5,30);
    local->fila = cria_fila();
    local->publico = cria_cjt(tam);
    local->id = i;
    local->lot_max = tam;
    local->coord->x = aleat(0,mundo->tam_mundo-1);
    local->coord->y = aleat(0,mundo->tam_mundo-1);

    return local;
}

locais_t **cria_locais (mundo_t *mundo)
{
    int i;
    locais_t **vl;

    if (!(vl = malloc(mundo->n_locais * sizeof(locais_t*))))
        return 0;

    i = 0;
    while (i < mundo->n_locais)
    {
        vl[i] = cria_unico_local(mundo,i);
        i++;
    }

    return vl;
}

conjunto_t *cria_habs (mundo_t *mundo)
{
    int i;
    conjunto_t *habs;

    habs = cria_cjt(mundo->n_habs);

    i = 0;
    while (i < mundo->n_habs)
    {
        insere_cjt(habs,i);
        i++;
    }

    return habs;
}

lef_t *iniciar_lef (mundo_t *mundo)
{
    int i;
    evento_t *p_evento;
    lef_t *lef;

    lef = cria_lef();

    p_evento = malloc(sizeof(evento_t));
    p_evento->tempo = mundo->tempo;
    p_evento->tipo = 0;
    p_evento->dado1 = 0;
    p_evento->dado2 = 0;
    adiciona_inicio_lef(lef,p_evento);

    i = 0;
    while (i < mundo->n_herois)
    {
        p_evento->tempo = aleat(0,672);
        p_evento->tipo = 1;
        p_evento->dado1 = i;
        p_evento->dado2 = aleat(0,mundo->n_locais-1);
        adiciona_ordem_lef(lef,p_evento);
        i++;
    }

    i = 0;
    while (i < mundo->n_missoes)
    {
        p_evento->tempo = aleat(0,FIM_DO_MUNDO);
        p_evento->tipo = 3;
        p_evento->dado1 = i;
        p_evento->dado2 = 0;
        adiciona_ordem_lef(lef,p_evento);
        i++;
    }

    p_evento->tipo = 4;
    p_evento->tempo = FIM_DO_MUNDO;
    adiciona_ordem_lef(lef,p_evento);

    free(p_evento);

    return lef;
}

void chegada (evento_t *evento, mundo_t *mundo, lef_t *lef)
{
    int id_heroi = evento->dado1;
    int id_local = evento->dado2;
    int teste_paciencia, teste_tamanho;
    int lot, lot_max;
    int tpl;

    lot = cardinalidade_cjt(mundo->v_locais[id_local]->publico);
    lot_max = mundo->v_locais[id_local]->lot_max;

    printf("%d:CHEGA HEROI %d Local %d ( %d/ %d), ", evento->tempo,id_heroi,
    id_local,cardinalidade_cjt(mundo->v_locais[id_local]->publico),lot_max);

    if (lot == lot_max) /*lotado*/
    {
        teste_paciencia = mundo->v_herois[id_heroi]->paciencia / 4;
        teste_tamanho = tamanho_fila(mundo->v_locais[id_local]->fila);

        if (teste_paciencia - teste_tamanho > 0) /*teve paciencia*/
        {
            insere_fila(mundo->v_locais[id_local]->fila,id_heroi);

            printf("FILA %d\n", mundo->v_locais[id_local]->fila->tamanho);
        }
        else /*nao teve paciencia*/
        {
            evento->tipo = 2;
            adiciona_inicio_lef(lef,evento);

            printf("DESISTE\n");
        }
    }
    else /*nao lotado*/
    {
        printf("ENTRA\n");

        insere_cjt(mundo->v_locais[id_local]->publico,id_heroi);

        tpl = maximiza(1,(mundo->v_herois[id_heroi]->paciencia / 10 + aleat(-2,6)));
        evento->tempo = mundo->tempo + tpl;
        evento->tipo = 2;
        adiciona_ordem_lef(lef,evento);
    }
}

int calculo_tdl (mundo_t *mundo, int novo, int id_heroi, int id_local)
{
    int tdl;
    int x1, x2, y1, y2, quad_p, quad_s, dist, vel;

    x1 = mundo->v_locais[id_local]->coord->x;
    x2 = mundo->v_locais[novo]->coord->x;
    y1 = mundo->v_locais[id_local]->coord->y;
    y2 = mundo->v_locais[novo]->coord->y;
    quad_p = (x2 - x1) * (x2 - x1);
    quad_s = (y2 - y1) * (y2 - y1);
    dist = sqrt(quad_p + quad_s);
    vel = 100 - maximiza(0,mundo->v_herois[id_heroi]->idade - 40);
    tdl = dist / vel;

    return tdl;
}

void saida (evento_t *evento, mundo_t *mundo, lef_t *lef)
{
    int id_heroi = evento->dado1;
    int id_local = evento->dado2;
    int novo, tdl;
    int dado;

    printf("%d:SAIDA HEROI %d Local %d ( %d/ %d)",evento->tempo,
    id_heroi,id_local,cardinalidade_cjt(mundo->v_locais[id_local]->publico),
    mundo->v_locais[id_local]->lot_max);

    if (pertence_cjt(mundo->v_locais[id_local]->publico,id_heroi) == 1) /*heroi dentro*/
    {
        retira_cjt(mundo->v_locais[id_local]->publico,id_heroi);

        if (mundo->v_locais[id_local]->fila->tamanho > 0) /*tem fila*/
        {
            printf(", REMOVE FILA HEROI %d\n",mundo->v_locais[id_local]->fila->ini->elem);

            retira_fila(mundo->v_locais[id_local]->fila,&dado);
            evento->tipo = 1;
            evento->dado1 = dado;
            adiciona_inicio_lef(lef,evento);
        }
        else
            printf("\n");
    }
    else
        printf("\n");

    novo = aleat(0,mundo->n_locais-1); /*novo local*/
    tdl = calculo_tdl(mundo,novo,id_heroi,id_local);

    evento->tipo = 1;
    evento->dado1 = id_heroi;
    evento->dado2 = novo;
    evento->tempo += tdl / 15;
    adiciona_ordem_lef(lef,evento);
}

conjunto_t **setar_missoes (mundo_t *mundo, lef_t *lef)
{
    int i, tam;
    conjunto_t **missoes;

    if (!(missoes = malloc(mundo->n_missoes * sizeof(conjunto_t*))))
        return 0;

    i = 0;
    while (i < mundo->n_missoes)
    {
        tam = aleat(3,6);
        missoes[i] = cria_subcjt_cjt(mundo->habs,tam);
        i++;
    }

    return missoes;
}

conjunto_t *uniao (mundo_t *mundo, lef_t *lef, int id_local)
{
    int i, ind;
    conjunto_t *uni, *aux;

    uni = cria_cjt(mundo->n_habs);

    inicia_iterador_cjt(mundo->v_locais[id_local]->publico);

    i = 0;
    while (i < cardinalidade_cjt(mundo->v_locais[id_local]->publico))
    {
        aux = uni;

        incrementa_iterador_cjt(mundo->v_locais[id_local]->publico,&ind);

        uni = uniao_cjt(uni,mundo->v_herois[ind]->habilidades);
        aux = destroi_cjt(aux);      

        i++;
    }

    return uni;
}

conjunto_t **uniao_habilidades (mundo_t *mundo, lef_t *lef)
{
    int i;
    conjunto_t **uni_habs;

    if (!(uni_habs = malloc(mundo->n_locais * sizeof(conjunto_t*))))
        return 0;

    i = 0;
    while (i < mundo->n_locais)
    {
        uni_habs[i] = uniao(mundo,lef,i);
        i++;
    }

    return uni_habs;
}

void liberar_vetor_habs (conjunto_t **habs, mundo_t *mundo)
{
    int i;

    i = 0;
    while (i < mundo->n_locais)
    {
        destroi_cjt(habs[i]);
        i++;
    }
    free(habs);
}

void missao (evento_t *evento, mundo_t *mundo, lef_t *lef, conjunto_t *missoes)
{
    int i, j, id;
    conjunto_t **habs;

    habs = uniao_habilidades(mundo,lef);

    i = 0;
    j = -1;
    while ((i < mundo->n_locais) && (j == -1))
    {
        if (contido_cjt(missoes,habs[i]) == 1)
            j = i;
        i++;
    }

    if (j > -1)
    {
        i = j;
        while (i < mundo->n_locais)
        {
            if (contido_cjt(missoes,habs[i]) == 1)
                if (cardinalidade_cjt(mundo->v_locais[i]->publico) < cardinalidade_cjt(mundo->v_locais[j]->publico))
                    j = i;
            i++;
        }
    }

    printf("%d:MISSAO %d HAB_REQ ",evento->tempo,evento->dado1);
    imprime_cjt(missoes);

    i = 0;
    while (i < mundo->n_locais)
    {
        printf("%d:MISSAO %d HAB_EQL %d:",evento->tempo,evento->dado1,i);
        imprime_cjt(habs[i]);
        i++;
    }

    if (j == -1)
    {
        printf("%d:MISSAO %d IMPOSSIVEL\n",evento->tempo,evento->dado1);
        evento->tempo = aleat(mundo->tempo,FIM_DO_MUNDO);
        adiciona_ordem_lef(lef,evento);
    }
    else
    {
        printf("%d:MISSAO %d HER_EQS %d:",evento->tempo,evento->dado1,j);
        imprime_cjt(mundo->v_locais[j]->publico);

        i = 0;
        while (i < cardinalidade_cjt(mundo->v_locais[j]->publico))
        {
            id = mundo->v_locais[j]->publico->v[i];
            mundo->v_herois[id]->exp++;
            i++;
        }
    }

    liberar_vetor_habs(habs,mundo);
}

void msg_final (mundo_t *mundo)
{
    int i;

    printf("%d:FIM\n",mundo->tempo);

    i = 0;
    while (i < mundo->n_herois)
    {
        printf("HEROI %d EXPERIENCIA %d\n",i,mundo->v_herois[i]->exp);
        i++;
    }
}

void liberar_vetor_missoes (conjunto_t **missoes, mundo_t *mundo)
{
    int i;

    i = 0;
    while (i < mundo->n_missoes)
    {
        destroi_cjt(missoes[i]);
        i++;
    }
    free(missoes);
}

void andar_lef (lef_t *lef, mundo_t *mundo)
{
    evento_t *evento;
    nodo_lef_t *aux1;
    conjunto_t **missoes;

    missoes = setar_missoes(mundo,lef);

    while (lef->Primeiro != NULL)
    {
        aux1 = lef->Primeiro;
        evento = obtem_primeiro_lef(lef);
        mundo->tempo = evento->tempo;
        switch(evento->tipo)
        {
            case 0:
                break;
            case 1:
                chegada(evento,mundo,lef);
                break;
            case 2:
                saida(evento,mundo,lef);
                break;
            case 3:
                missao(evento,mundo,lef,missoes[evento->dado1]);
                break;
            case 4:
                msg_final(mundo);
                destroi_lef(lef);
                break;
        }
        free(evento);
        free(aux1);
    }

    free(lef);
    liberar_vetor_missoes(missoes,mundo);
}

void liberar_mundo (mundo_t *mundo)
{
    int i;

    destroi_cjt(mundo->habs);

    i = 0;
    while (i < mundo->n_herois)
    {
        destroi_cjt(mundo->v_herois[i]->habilidades);
        free(mundo->v_herois[i]);
        i++;
    }
    free(mundo->v_herois);

    i = 0;
    while (i < mundo->n_locais)
    {
        free(mundo->v_locais[i]->coord);
        destroi_cjt(mundo->v_locais[i]->publico);
        destroi_fila(mundo->v_locais[i]->fila);
        free(mundo->v_locais[i]);
        i++;
    }
    free(mundo->v_locais);

    free(mundo);
}

int main()
{
    lef_t *lef;
    mundo_t *mundo;
    mundo = setar_mundo();

    srand(0);

    mundo->habs = cria_habs(mundo);
    mundo->v_herois = cria_herois(mundo);
    mundo->v_locais = cria_locais(mundo);

    lef = iniciar_lef(mundo);
    andar_lef(lef,mundo);

    liberar_mundo(mundo);

    return 0;
}