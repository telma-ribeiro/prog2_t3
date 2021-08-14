#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"
#include "movies.h"

//Adiciona cliente na tabela de dispersao
void adicionaCliente(colecaoClientes *td, elementoCliente *e_cliente)
{
    unsigned long index;
    /* exercicio 1.2 */
    if (!td) //acrescentar mais verificacoes
        return NULL;
    elemento *elem;
    /* calcula hash para a string a adicionar */
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
