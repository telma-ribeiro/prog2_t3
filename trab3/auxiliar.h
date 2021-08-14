/**** Este ficheiro inclui bibliotecas dadas nas aulas de Progamacao 2, no entanto, algumas fizemos umas pequenas alteracoes
 * e como nao precisavamos de todas as funcoes que tinham nas bibliotecas decidimos juntar todas as bibliotecas que usamos neste auxiliar***/

#ifndef AUXILIAR_H
#define AUXILIAR_H



typedef struct 
{
	char* titulo;
	char* categoria;
	unsigned int filmId;
	float rating;
} filme;

typedef struct{
	int tamanho;
	int capacidade;
	struct filme** filmes;
} heap;

typedef struct categoria{
	char* categName;
	heap* itemTree;
} category_t;


typedef struct no_colecFilmes_
{
	category_t *categ;
	int count;
	float soma;
	float media;
	struct no_colecFilmes_ *esquerda;
	struct no_colecFilmes_ *direita;
	int altura;
}no_colecFilmes;

/** Estrutura colecaoFilmes deverá ser completada de forma a ser possivel guardar os filmes em memoria
 * */
typedef struct{
	no_colecFilmes *raiz;
} colecaoFilmes;


//cria a arvore para armazenar os filmes, em cada no tera uma heap
colecaoFilmes* colecFilmes_nova();
no_colecFilmes* colecFilmes_novo_no(category_t *categ);
no_colecFilmes* colecFilmes_insere(no_colecFilmes *no, category_t * categ);
filme* filme_novo(char *titulo, char *categoria, int filmId, float rating);
no_colecFilmes* colecFilmes_no_valormin(no_colecFilmes* no);
no_colecFilmes *colecFilmes_no_valormax(no_colecFilmes *no);
void colecFilmesNoApaga(no_colecFilmes* no);
void colecFilmesNoCopia(no_colecFilmes* nodeDest, no_colecFilmes* nodeSrc);
no_colecFilmes* colecFilmes_remove(no_colecFilmes *no, const char* categStr);
no_colecFilmes* colecFilmes_pesquisa(no_colecFilmes *no, const char* categStr);
int colecFilmes_altura(no_colecFilmes *no);
int calc_balanceamento(no_colecFilmes *N);
no_colecFilmes *roda_direita(no_colecFilmes *y);
no_colecFilmes *roda_esquerda(no_colecFilmes *x);
int max(int a, int b);
int min(int a, int b);
void colecFilmes_apagarecur(no_colecFilmes *no);
void colecFilmes_apaga(colecaoFilmes *colecFilmes);


heap* heap_nova(int tamanho_maximo);
void heap_apaga(heap *h);
void mostraHeap(heap *h);
category_t* novaCategoria(heap* itemTree, char* categName);
void categoriaApaga(category_t* categ);
int heap_insere(heap *h, filme *f);
int maior_que(filme *f1, filme *f2);

#endif