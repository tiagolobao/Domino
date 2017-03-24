#ifndef ___DOMINO___
#define ___DOMINO___

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define NUM_PEDRAS 28 //Número de pedras no jogo
#define MAX_MAO 6 //Número de pedras que começam na mão do jogador


/* ------------------------------------------------------------------*/
/* --------------------- PEDRA NO DOMINO-----------------------------*/
/* ------------------------------------------------------------------*/
typedef struct Pedra { int esquerda;
                       int direita;
                } tPedra;



/*
    ___________
   |          |
   |    O     |  => esquerda
   |__________|                Exemplo para quina de ás
   |  O    O  |                       ( 1 | 5 )
   |     O    |  => direita
   |___O___O__|

Pedra.esquerda = 1
Pedra.direita = 5

*/

/* Quando que uma pedra é maior que a outra?

  - Se o lado direito for maior
  - So o direito for igual, compara-se o esquerdo

  - O lado esquerdo, nessa lógica, sempre será um valor 
  menor ou igual comparando com o lado direito

  - Isso implica que a função invertePedra só podera ser usada
  para colocar uma pedra na mesa no seu lado certo.


  (ESQUERDA <= DIREITA)

*/



/* ------------------------------------------------------------------*/
/* --------------------- CABEÇALHO FUNÇOES DOMINÓ--------------------*/
/* ------------------------------------------------------------------*/

// ***********************************************
/*Imprime a pedra passada como parâmetro*/
void imprimePedra(tPedra rock);

// ***********************************************
/*Inverte a pedra passada como parâmetro*/
void invertePedra(tPedra* rock);

// ***********************************************
/*Compara o conteúdo interno de duas pedras*/
bool comparaPedra(tPedra rock1, tPedra rock2);

/* Realiza soma dos valores esqueda e direita da pedra */
int somaPedra(tPedra rock);




#endif // ___DOMINO___
