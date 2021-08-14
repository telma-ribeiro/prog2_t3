#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxiliar.h"

#define RAIZ        (1)
#define PAI(x)      (x/2)
#define FILHO_ESQ(x)    (x*2)
#define FILHO_DIR(x) (x*2+1)

colecaoFilmes* colecFilmes_nova(){
    colecaoFilmes *colecFilmes = (colecaoFilmes*)malloc(sizeof(colecaoFilmes));
    if (colecFilmes == NULL)
        return NULL;

    colecFilmes->raiz = NULL; /* arvore vazia */
    return colecFilmes;
}

no_colecFilmes* colecFilmes_novo_no(category_t *categ){
    no_colecFilmes *no = (no_colecFilmes *)malloc(sizeof(no_colecFilmes));
    if (no == NULL)
        return NULL;

    no->categ = categ;
    no->count=0;
    no->media=0;
    no->soma=0;
    no->esquerda = NULL;
    no->direita = NULL;
    no->altura = 0; /* novo no e' inicialmente uma folha */

    return no;
}
    
no_colecFilmes *colecFilmes_insere(no_colecFilmes *no, category_t *categ)
{
    if (categ == NULL)
        return NULL;

    if (no == NULL)
        return colecFilmes_novo_no(categ);

    if (strcmp(categ->categName, no->categ->categName) < 0)
    {
        no->esquerda = colecFilmes_insere(no->esquerda, categ);
    }
    else if (strcmp(categ->categName, no->categ->categName) > 0)
        no->direita = colecFilmes_insere(no->direita, categ);
    else
        return no;

    /* 2. atualiza a altura deste no ancestral */

    no->altura = max(colecFilmes_altura(no->esquerda), colecFilmes_altura(no->direita)) + 1;

    /* 3. calcula o fator de balanceamento deste no ancestral para verificar
       se deixou de estar balanceado */

    int balance = calc_balanceamento(no);

    /* se o no deixou de estar balanceado, existem 4 casos */

    if (balance > 1)
    {

        /* Arvore e' right-heavy */

        if (calc_balanceamento(no->direita) < 0)
        {

            /* Sub-arvore direita é left-heavy */

            /* Rotacao RL */

            no->direita = roda_direita(no->direita);

            return roda_esquerda(no);
        }
        else
        {

            /* Rotacao L */

            return roda_esquerda(no);
        }
    }

    else if (balance < -1)
    {

        /* Arvore e' left-heavy */

        if (calc_balanceamento(no->esquerda) > 0)
        {

            /* Sub-arvore esquerda é right-heavy */

            /* Rotacao LR */

            no->esquerda = roda_esquerda(no->esquerda);

            return roda_direita(no);
        }
        else
        {

            /* Rotacao R */

            return roda_direita(no);
        }
    }

    /* caso esteja balanceada retorna o apontador para o no (inalterado) */

    return no;
}

int colecFilmes_altura(no_colecFilmes *no)
{
    if (no == NULL)
        return -1;
    return no->altura;
}


int calc_balanceamento(no_colecFilmes *N)

{

    if (N == NULL)

        return 0;

    return colecFilmes_altura(N->direita) - colecFilmes_altura(N->esquerda);
}

no_colecFilmes *roda_direita(no_colecFilmes *y)
{
    no_colecFilmes *x = y->esquerda;
    no_colecFilmes *T2 = x->direita;
    /* efetua rotacao */
    x->direita = y;
    y->esquerda = T2;
    /* atualiza alturas */
    y->altura = max(colecFilmes_altura(y->esquerda), colecFilmes_altura(y->direita)) + 1;
    x->altura = max(colecFilmes_altura(x->esquerda), colecFilmes_altura(x->direita)) + 1;
    /* retorna novo no' */
    return x;
}

no_colecFilmes *roda_esquerda(no_colecFilmes *x)
{
    no_colecFilmes *y = x->direita;
    no_colecFilmes *T2 = y->esquerda;
    /* efetua rotacao */
    y->esquerda = x;
    x->direita = T2;
    /*  atualiza alturas */
    x->altura = max(colecFilmes_altura(x->esquerda), colecFilmes_altura(x->direita)) + 1;
    y->altura = max(colecFilmes_altura(y->esquerda), colecFilmes_altura(y->direita)) + 1;
    /* retorna novo no' */
    return y;
}


no_colecFilmes *colecFilmes_no_valormin(no_colecFilmes *no)
{
    no_colecFilmes *curr = no;
    /* percorre a arvore para encontrar o filho mais 'a esquerda */
    while (curr->esquerda != NULL)
        curr = curr->esquerda;
    return curr;
}

no_colecFilmes *colecFilmes_no_valormax(no_colecFilmes *no)
{
    no_colecFilmes *curr = no;
    /* percorre a arvore para encontrar o filho mais 'a direita */
    while (curr->direita != NULL)
        curr = curr->direita;
    return curr;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int min(int a, int b)
{
    return (a < b) ? a : b;
}

heap *heap_nova(int capacidade)
{

    heap *nova =malloc(sizeof(heap));

    if (nova == NULL)
    {
        return NULL;
    }

    nova->tamanho = 0;
    nova->capacidade = capacidade;
    nova->filmes = malloc((capacidade + 1) * sizeof(filme*));
    if (nova->filmes == NULL)
    {
        return NULL;
    }

    return nova;
}

void heap_apaga(heap *h)
{
    int i;
    for (i = 1; i <= h->tamanho; i++)
    {
        free(h->filmes[i]);
    }
    free(h->filmes);
    free(h);
}


category_t *novaCategoria(heap *itemTree, char *categName)
{

    category_t *retCat = (category_t *)malloc(sizeof(category_t));

    if (retCat == NULL)

    {

        return NULL;
    }

    retCat->itemTree = itemTree;

    retCat->categName = (char *)malloc((strlen(categName) + 1) * sizeof(char));

    if (retCat->categName == NULL)

    {

        return NULL;
    }

    strcpy(retCat->categName, categName);

    return retCat;

    //Default

    return NULL;
}