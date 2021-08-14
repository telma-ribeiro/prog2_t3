/*****************************************************************/
/*           Movies | PROG2 | MIEEC | 2018/19                */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "auxiliar.h"
#include "movies.h"

#define RAIZ        (1)
#define PAI(x)      (x/2)
#define FILHO_ESQ(x)    (x*2)
#define FILHO_DIR(x) (x*2+1)

arvore_avl *avl_aux; //esta variavel sera usada na funcao 6. e na funcao 9

//Declaracao funcoes auxiliares//
//adiciona um cliente na tabela de dispersao
void adicionaCliente(colecaoClientes *td, elementoCliente *e_cliente)
{
    unsigned long index;
    if (!td || !e_cliente) //acrescentar mais verificacoes
        return;

    elementoCliente *elem;
    /* calcula hash para cliente a adicionar */
    index = hash_cliente(e_cliente->clien->username, td->tamanho);

    elementoCliente *aux = td->elementos[index], *auxanterior = NULL;
    if (aux == NULL)
    { //a lista esta vazia
        td->elementos[index] = e_cliente;
    }

    else{
        while (aux != NULL)
        {
            auxanterior = aux;
            aux = aux->proximo;
        }
        auxanterior->proximo = e_cliente;
    }

    e_cliente->proximo = NULL;

    return;

}


//////   Implementacao Tabela de Dispersão - Clientes  ///////
colecaoClientes* colecaoClientesNova(int tamanho)
{
    /* aloca memoria para a estrutura tabela_dispersao */

    colecaoClientes *t = (colecaoClientes*) malloc(sizeof (colecaoClientes));
    if (t == NULL)
        return NULL;

    /* aloca memoria para os elementos */
    t->elementos = (elementoCliente **) calloc(tamanho, sizeof (elementoCliente*));
    if (t->elementos == NULL) {
        free(t);
        return NULL;
    }

    t->tamanho = tamanho;

    return t;
}

void colecaoClientesApaga(colecaoClientes *td)
{
    int i;
    elementoCliente *elem, *aux;

    if (td == NULL) return ;

    /* para cada entrada na tabela */
    for (i = 0; i < td->tamanho; i++)
    {
        /* e enquanto existirem elementos nessa entrada */
        elem = td->elementos[i];
        while (elem != NULL)
        {
            /* liberta cada elemento */
            aux = elem->proximo;
            vetor_apaga(elem->clien->vistos);
            free(elem->clien->username);
            elem->clien->username=NULL;
            free(elem->clien);
            free(elem);
            elem = aux;
        }
    }

    /* liberta vector e estrutura */
    free(td->elementos);
    free(td);
}

int clienteAdiciona(colecaoClientes *td, const char *username, unsigned int filmId)
{
   // Resolução do exercicio 1
    int id = hash_cliente(username, td->tamanho), i;



    elementoCliente *elem = (elementoCliente *)malloc(sizeof(elementoCliente));



    elem = td->elementos[id];



    if (clienteExiste(td, username) == 1)

    { //o cliente ja existe



        // verificar se o filme ja existe (temos que percorrer o vetor vistos)



        for (i = 0; i < vetor_tamanho(elem->clien->vistos); i++)

        {

            if (vetor_elemento(elem->clien->vistos, i) == filmId)



                return 0; //a entrada ja existe (o cliente existe e ja viu o filme)

        }



        vetor_insere(elem->clien->vistos, filmId, -1);



        return 1;

    }



    else

    { //o cliente nao existe



        elementoCliente *novocliente = (elementoCliente *)malloc(sizeof(elementoCliente));



        novocliente->clien = (cliente *)malloc(sizeof(cliente));



        novocliente->clien->username = malloc(strlen(username) + 1);



        strcpy(novocliente->clien->username, username);



        novocliente->clien->vistos = vetor_novo();



        if (novocliente->clien->vistos == NULL)



            return -1;



        adicionaCliente(td, novocliente);



        if (filmId == 0)



        {



            return 1;

        }



        else



        {



            if (vetor_insere(novocliente->clien->vistos, filmId, -1) == -1)



            {



                printf("n inseriu o novo cliente na tabela\n");



                return -1;

            }



            return 1; //fez a adicao

        }

    }



    return -1;

}





int colecaoNumClientes(colecaoClientes *td)
{
	// resolução do exercicio 2
     if (!td)



    {

        return -1;

    }



    int i, count = 0;



    elementoCliente *elem;



    for (i = 0; i < td->tamanho; i++)



    {



        elem = td->elementos[i];



        while (elem != NULL)



        {



            elem = elem->proximo;



            count++;

        }

    }



    return count;

}


int clienteExiste(colecaoClientes *td, const char *username)
{
    // resolução do exercicio 3
    if (!td || !username)



        return -1;



    unsigned long index;



    /* calcula hash para o cliente a pesquisados */



    index = hash_cliente(username, td->tamanho);



    elementoCliente *aux = td->elementos[index], *auxanterior = NULL;



    if (aux == NULL) //a lista esta vazia, ou seja, nao existe o cliente



        return 0;



    else



    {



        while (aux != NULL)



        {



            if (strcmp(aux->clien->username, username) == 0)



                return 1; //o cliente foi encontrado



            else



                aux = aux->proximo;

        }



        return 0; //se chegar aqui o cliente nao consta na tabela

    }

}



unsigned long hash_cliente(const char* username, int tamanho)
{
    int c, t = strlen(username);
    unsigned long hash = 7;

    for(c = 0; c < t; c++)
    {
        hash += (int) username[c]*powf(2,c);
    }

    return hash % tamanho;

}

/*================================================================================*/
void mostraTabela(colecaoClientes *td)
{
    int i;
    elementoCliente * elem;


    printf("TABELA DE CLIENTES (%d Clientes)\n", colecaoNumClientes(td));
    for (i = 0; i < td->tamanho; i++)
    {
        if (td->elementos[i])
        {
            printf("\t[%2d]", i);
            elem = td->elementos[i];
            while (elem)
            {
                printf(" : [\"%s\" Filmes: ", elem->clien->username);
                if (elem->clien->vistos->tamanho>0)
                {

                    for (int j=0; j<elem->clien->vistos->tamanho; j++)
                    {
                        printf(" (%d)", elem->clien->vistos->elementos[j]);
                    }

                }
                printf("]");
                elem = elem->proximo;
            }
            printf("\n");
        }
    }
    printf("\n");
}



///////////////////////////////////////////////////



/* inserir um Novo Filme*/
int inserirNovoFilme(colecaoFilmes* colecFilmes, char* titulo, char* categoria, int filmId, float rating)
{
    // resolução do exercicio 5
    fprintf(stderr, "inicio do inserir novo filme \n");
    no_colecFilmes *no_aux=colecFilmes_pesquisa(colecFilmes->raiz, categoria);
    filme *fnovo=(filme*)malloc(sizeof(filme));
    if(fnovo==NULL){
        printf("5. Nao conseguiu criar um filme aux \n");
        return -1;
    }

    strcpy(fnovo->titulo, titulo);
    strcpy(fnovo->categoria, categoria);
    fnovo->filmId=filmId;
    fnovo->rating=rating;
    
    
    if(!no_aux) //a categoria ainda nao existe
    {
        heap *h=heap_nova(100);
        if(!h){
            printf("5. Nao foi criada a heap");
            return -1;
        }
        if(!heap_insere(h, fnovo)){
            printf("5. Nao conseguiu inserir na heap nova \n");
            return -1;
        }
        category_t *cnova=novaCategoria(h, categoria);
        if(!cnova){
            heap_apaga(h);
            printf("5. Nao criou a categoria nova \n");
            return -1;
        }
        colecFilmes->raiz=colecFilmes_insere(colecFilmes->raiz, cnova);    
        if(!colecFilmes->raiz){
            categoriaApaga(cnova);
            return -1;
        }
    return 1;
    } 
    else{
        //a categoria existe, queremos adicionar o filme a heap que ja esta nesse no
        //ACRESCENTAR VERIFICAO SE A HEAP TEM ESPACO
        if(!heap_insere(no_aux->categ->itemTree, fnovo)){ //FALTA FAZER A HEAP INSERE
            heap_apaga(no_aux->categ->itemTree);
            return -1;
        }
        else
            return 1;
    }

}

colecaoFilmes* filmesCarrega(const char *nomeFicheiro)
{
   // resolução do exercicio 6
   if (!nomeFicheiro)
        return NULL;
   colecaoFilmes* colecao=colecFilmes_nova(); 
   if(!colecao){
       printf("6.A arvore com a colec filmes nao foi criada \n");
       return NULL;
   }

   avl_aux=avl_nova();
   if(avl_aux==NULL){
       printf("6.A avl aux nao foi criada \n");
       return NULL;
   }

   char titulo[500], categoria[100], linha[500];
   char* token;
   int id;
   float rating;
   FILE *f=fopen(nomeFicheiro, "r");
   if(f==NULL){
       printf("6. Nao conseguiu abrir o ficheiro \n");
       return NULL;
   }
   while (fgets(linha, 5000, f) != NULL)
    {
        token = strtok(linha, "|");
        strcpy(titulo, token);
        token = strtok(NULL, "|");
        strcpy(categoria, token);
        token = strtok(NULL, "|");
        id = atoi(token);
        token = strtok(NULL, "|");
        rating = atof(token);
        if(avl_insere(avl_aux, "id", categoria, rating)==-1){ //queremos inserir todos os filmes, por ordem crescente de id
            printf("6. Nao inseriu o filme com o id: %d na avl aux", id);
            return NULL;
        }
        inserirNovoFilme(colecao, titulo, categoria, id, rating); //dentro desta funcao e que temos que verificar se a categoria e o filme ja existem
    }


   return colecao;


}

// Remover um filme///
int removerFilme(colecaoFilmes *colecFilmes, colecaoClientes *td, int filmId)
{
    /*Questao 7*/
    int i, filho_maior;
    filme* aux;
    char* ret;
    heap* h = (heap*) malloc(sizeof(heap));
    //h = colecFilmes_pesquisa TEMOS QUE SABER A CATEGORIA DO FILMEID   

    /* se heap estiver vazia, nao remove elemento */
    if (!h || h->tamanho <= 0 || !td || !colecFilmes)
        return -1;
    elementoCliente *elem;
    /* coloca ultimo elemento da heap na raiz */
    h->filmes[RAIZ] = h->filmes[h->tamanho];
    h->filmes[h->tamanho] = NULL;
    h->tamanho--;

    i = RAIZ;

    /* enquanto nao chegar 'a base da heap */
    while(FILHO_ESQ(i) <= h->tamanho)
    {
        filho_maior = FILHO_ESQ(i);

        /* verifica se existe filho 'a direita e se este e' mais prioritario do que 'a esquerda */
        if (FILHO_DIR(i) <= h->tamanho && maior_que(h->filmes[FILHO_DIR(i)], h->filmes[FILHO_ESQ(i)]))
            filho_maior = FILHO_DIR(i);

        /* enquanto elemento for mais prioritario do que o respetivo pai, troca-os */
        if (maior_que(h->filmes[filho_maior], h->filmes[i]))
        {
            aux = h->filmes[filho_maior];
            h->filmes[filho_maior] = h->filmes[i];
            h->filmes[i] = aux;
            i = filho_maior;
        }
        else
            break;
    }

    
    for (int j = 0; j < td->tamanho; j++)
    {
        elem = td->elementos[j];
        while (elem != NULL)
        {
            for (int count = 0; count < vetor_tamanho(elem->clien->vistos); count ++)
            {
                if (vetor_elemento(elem->clien->vistos, count) == filmId)
                    vetor_remove(elem->clien->vistos, count);
            }
            elem = elem->proximo;
        }
    }
    return 1;
}


// Remover a estrutura colecaoFilmes

void colecaoFilmesApaga(colecaoFilmes *colecFilmes, colecaoClientes *td)
{
    /*Questao 8*/
    if (!colecFilmes)
        return;

    while (colecFilmes->raiz != NULL)
    {
        heap_apaga(colecFilmes->raiz->categ->itemTree);
        colecFilmes->raiz = colecFilmes_remove(colecFilmes->raiz, colecFilmes->raiz->categ->categName);
    }
    colecFilmes_apaga(colecFilmes);
}
 


//Sugestões //////////////////////////////


vetor* sugestoes(colecaoFilmes* colecFilmes, colecaoClientes *td,char* username, int nFilmes, float limiar)
{
	// resolução do exercicio 9
    if(!colecFilmes || !td || nFilmes==0 || limiar>10 || limiar<0){
        return NULL;
    }
    if(!clienteExiste(td, username)){
        printf("9. o cliente nao existe na tab. dispersao \n");
        return NULL;
    }
    vetor *v_sugestoes=vetor_novo(); //este vai ser o vetor retornado
    if(v_sugestoes==NULL){
        printf("9. o vetor sugestoes nao foi criado \n");
        return NULL;
    }
    vetor *vistosaux=vetor_novo();
    if(vistosaux==NULL){
        return NULL;
    }
    no_avl* no_avl_aux;
    no_colecFilmes* no_colecao;
    //Procurar na tab. o cliente com o username dado
    int index=hash_cliente(username, td->tamanho);
    int flag=0;
    char *id;
    elementoCliente *aux=td->elementos[index];
    while(aux!=NULL){ //neste ciclo estamos a percorrer a lista da posicao index da tabela
        if(strcmp(username, aux->clien->username)==0){
            flag=1; //encontrou o cliente
            for(int i=0; i<vetor_tamanho(aux->clien->vistos); i++){
                vetor_insere(vistosaux, vetor_elemento(aux->clien->vistos, i), -1);
            }
            break;
        }
        aux=aux->proximo;
    }

    if(flag!=1){
        printf("9.Nao conseguimos encontrar o cliente na tabela \n");
        return NULL;
    }

    for(int i=0; i<vetor_tamanho(vistosaux); i++){
        sprintf(id, "%d", vetor_elemento(vistosaux, i)); // o elemento da posicao i corresponde ao id
        no_avl_aux=avl_pesquisa(avl_aux, id); //AQUI TEMOS QUE FAZER PRIMEIRO AVL NOVO NO?
        no_colecao=colecFilmes_pesquisa(colecFilmes->raiz, no_avl_aux->str);
        no_colecao->count+=1;
        no_colecao->soma+=no_avl_aux->rating;
    }
    //percorrer a arvore colecfilmes e preencher o campo media
    //Agora temos que percorrer a arvore colecFilmes e a medida que vamos percorrendo vemos qual o no com o maior contador e guardamos
    //se houver dois contadores iguais ver qual e o que tem maior media rating
    //criar um no aux que sera o nosso no maior e vamos a heap desse no
    //fazer heap remove e copiar uma heap aux e ver se o utilizador ja viu esse filme
    //se nao viu, copia para o vetor sugestoes e faz heap insere novamente na original
    //se ja viu, guarda se esse filme e so quando se passar para outra categoria e que inserimos novamente
    //ter atencao ao nfilmes e ao limiar
    return NULL;
}



///////////////////////////////////////
