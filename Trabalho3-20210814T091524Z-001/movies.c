/*****************************************************************/
/*           Movies | PROG2 | MIEEC | 2018/19                */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "movies.h"
#include "vetor.h"


//Declaracao funcoes auxiliares//
//Adiciona cliente na tabela de dispersao
void adicionaCliente(colecaoClientes *td, elementoCliente *e_cliente)
{
    unsigned long index;
    if (!td || !e_cliente) //acrescentar mais verificacoes
        return;
    /* calcula hash para o cliente a adicionar */
    index = hash_cliente(username, td->tamanho);
    
    elementoCliente *aux = td->elementos[index], *auxanterior = NULL;
    if (aux == NULL)
    { //a lista esta vazia
        td->elementos[index] = e_cliente;
    }
    else
    {
        while (aux != NULL)
        {
            auxanterior = aux;
            aux = aux->proximo:
        }
        auxanterior->proximo = e_cliente;
    }
    e_cliente->proximo = NULL;
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
   //IMPORTANTE: FALTA A NOTA 3, APENAS TEM NO ULTIMO ELSE
   // verificar se o cliente existe com a funcao clienteexiste (devolve 1 se existe)
   char titulo[500], categoria[100], char linha[5000]; //ver melhor o tamanho
   char *token;
   int id;
   float rating;
   if(!td || !username)
    return -1;
   if(clienteExiste(td, username)==1){ //o cliente ja existe
        //verificar se o filme ja existe (temos que percorrer o vetor vistos)
        for(int i=0; i<vetor_tamanho(td->elementos->clien->vistos); i++){
            if(td->elementos->clien->vistos[i]==filmId){
                return 0; //a entrada ja existe(o cliente existe e ja viu o filme)
            }
        }
        else{ //senao faz o seguinte
        FILE *f_filmes=fopen("filmesShort.txt", "r");
        if(f==NULL)
            return -1;

            while(fgets(linha, 5000, f)!=EOF){
                token=strtok(linha, "|");
                strcpy(titulo, token);
                token=strtok(NULL, "|");
                strcpy(categoria, token);
                token=strtok(NULL, "|");
                filmId=atoi(token);
                token=strtok(NULL, "|");
                rating=atof(token);

                if(id==filmId){ 
                    inserirNovoFilme(/*colecFilmes*/, titulo, categoria, id, rating);
                    break;
                }
            }
        }
   }    
   else{ //o cliente nao existe
        cliente *novocliente;       
        novocliente->username=malloc(strlen(username)+1);
        strcpy(novocliente->username, username);
        novocliente->vistos=vetor_novo();
        if(vistos==NULL)
            return -1; 
        if(filmId==0)
            return 1; //cliente nao tem vizualicacoes
        
        elementoCliente *novoelemento;
        novoelemento->clien=novocliente;
        novoelemento->proximo=NULL;
        adcionaCliente(td, novoelemento);
        return 1; //fez a adicao
   }

}

int clienteRemove(colecaoClientes *td, const char *username)
{
    int index;
    elementoCliente * elem, * aux;

    if (!td) return -1;

    /* calcula hash para a string a remover */
    index = hash_cliente(username, td->tamanho);

    elem = td->elementos[index];
    aux = NULL;

    /* para cada elemento na posicao index */
    while(elem != NULL)
    {
        /* se for a string que se procura, e' removida */
        if (strcmp(elem->clien->username, username) == 0)
        {
            /* se nao for a primeira da lista */
            if (aux != NULL)
                aux->proximo = elem->proximo;
            else
                td->elementos[index] = elem->proximo;
            free(elem->clien);
            free(elem);

            return 1;
        }

        aux = elem;
        elem = elem->proximo;
    }
    return 0;
}


int colecaoNumClientes(colecaoClientes *td)
{
	// resolução do exercicio 2
    if(!td)
        return -1;
    
    int i, count=0;
    elementoCliente *elem;

    //percorre todos os elementos da tabela
    for(i=0; i<td->tamanho; i++){
        elem=td->elementos[i];
        while(elem!=NULL){
            elem=elem->proximo;
            count++;
        }
    }
    return count;
}

int clienteExiste(colecaoClientes *td, const char *username)
{
    //resolucao do exercicio 3
    if(!td || !username)
        return -1;
          unsigned long index;

    /* calcula hash para o cliente a pesquisaros */
    index = hash_cliente(username, td->tamanho);
    
    elementoCliente *aux = td->elementos[index], *auxanterior = NULL;
    if (aux == NULL) //a lista esta vazia, ou seja, nao existe o cliente
        return 0; 
    
    else
    {
        while (aux != NULL)
        {
            if(strcmp(aux->clien->username, username)==0)
                return 1; //o cliente foi encontrado
            
            else
                aux=aux->proximo;
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
    if(!colecFilmes || !titulo || !categoria)
        return -1;


}

colecaoFilmes* filmesCarrega(const char *nomeFicheiro)
{
   // resolução do exercicio 6
    if(!nomeFicheiro)
        return NULL;
    
    char titulo[500], categoria[100], char linha[5000]; //ver melhor o tamanho
    char *token;
    int id;
    float rating;
    colecaoFilmes* colecmovies;
    colecmovies->itemTree=heap_nova();
    if(heapfilmes==NULL)
        return NULL;

    if(!td || !username)
        return -1;
    
    FILE *f;
    if(!f){
        printf("Nao foi possivel abrir o ficheiro \n");
        return NULL;
    }
    
    while(fgets(linha, 5000, f)!=EOF){
        token=strtok(linha, "|");
        strcpy(titulo, token);
        token=strtok(NULL, "|");
        strcpy(categoria, token);
        token=strtok(NULL, "|");
        filmId=atoi(token);
        token=strtok(NULL, "|");
        rating=atof(token);
        inserirNovoFilme(/*colecfilmes*/, titulo, categoria, filmId, rating);
    }
    
    


}


// Remover um filme///
int removerFilme(colecaoFilmes* colecFilmes, colecaoClientes *td, int filmId)
{
    // resolução do exercicio 7
   return -1;
}

// Remover a estrutura colecaoFilmes
void colecaoFilmesApaga(colecaoFilmes* colecFilmes, colecaoClientes *td)
{
    // resolução do exercicio 8
 
}

//Sugestões //////////////////////////////


vetor* sugestoes(colecaoFilmes* colecFilmes, colecaoClientes *td,char* username, int nFilmes, float limiar)
{
	// resolução do exercicio 9
   return NULL;
}



///////////////////////////////////////
