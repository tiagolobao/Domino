#ifndef ___LISTA_SIMPLESMENTE_ENCADEADA___
#define ___LISTA_SIMPLESMENTE_ENCADEADA___

#include "Domino.h"

/* TAD Utilizado para guardar as pedras da mesa e da mão dos jogadores */


/* --------
	A ordenação na mão do jogador é a seguinte:

	- A ordenação é decrescente
	- Prioridade: o lado direito ser maior conta mais do que o esquerdo
	- A ordem relativa a todas as peças é printada na função embaralhaPedras

*/


/* ------
	Não existe ordenação nas pedras da mesa.
	Para ela, só é utilizado as funções insere inicio e insere final
*/





typedef struct NoSimples { tPedra V;
                 	    struct NoSimples* prox;
                } tNoSimples;


typedef struct { tNoSimples* inicio;
                 tNoSimples* final;
                 int numElem;
               } tListaSimplesEncadeada;


// ***********************************************
/*Inicializa a lista */
void initListaSimples(tListaSimplesEncadeada* L);

// ***********************************************
/*Limpa toda a lista, liberanto todo o espaço da memória */
void limpaListaSimples(tListaSimplesEncadeada* L);

// ***********************************************
/* Imprime a lista na ordem Inicio -> final */
void imprimeListaSimples(tListaSimplesEncadeada L);

// ***********************************************
/* Insere um elemento na ultima posição da lista
   Ou melhor, na ponta direita da mesa */
bool insereFinalListaSimples(tListaSimplesEncadeada* L, tPedra pedra);

// ***********************************************
/* Insere um elemento na primeira posição da lista
   Ou melhor, na ponta esquerda da mesa */
bool insereInicioListaSimples(tListaSimplesEncadeada* L, tPedra pedra);

// ***********************************************
/* Aloca um nó. Utilizado nas funções de inserir */
tNoSimples* alocaNoSimples(tPedra pedra);



/* Incluidas na nova versão */


// ***********************************************
/* Retorna o tamanho da lista */
int tamListaSimples(tListaSimplesEncadeada L);

// ***********************************************
/* Busca a pedra de valor especificado
   Usada para remover elemento da lista */
tNoSimples* buscaElementoListaSimples(tListaSimplesEncadeada L, 
  tNoSimples** anterior, int pontas[], bool** esquerda, bool** inicio);

// ***********************************************
/*Insere de forma em que a soma dos valores da pedra na ordem DECRESCENTE
  Necessário para agilizar a busca da melhor pedra*/
bool insereOrdenadoListaSimples(tListaSimplesEncadeada* L, tPedra pedra);

// ***********************************************
/*Remove a pedra de valor especificado
  Usada para fazer um jogador colocar uma pedra na mesa*/
bool removeElementoListaSimples(tListaSimplesEncadeada* L, 
  int pontas[], bool* esquerda, bool* inicio, tPedra* pedra);

// ***********************************************
/*Remove a pedra de um endereço especificado
  Usada para o embaralhamento das pedras*/
tPedra removeElementoPosListaSimples(tListaSimplesEncadeada* L, int index);

// ***********************************************
/*Soma de todos os valores dos elementos da lista 
  Usada para contar a quantidade de pontos de cada jogador*/
int somaListaSimples(tListaSimplesEncadeada L);





#endif // ___LISTA_SIMPLESMENTE_ENCADEADA___
