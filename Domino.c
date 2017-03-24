
#include "Domino.h"


// ***********************************************
// ******                                   ******
// ***********************************************
void imprimePedra(tPedra rock){
  printf("[%d|%d] ", rock.esquerda, rock.direita);
}

// ***********************************************
// ******                                   ******
// ***********************************************
void invertePedra(tPedra* rock){
  tPedra temp;
  temp.direita = rock->direita;
  temp.esquerda = rock->esquerda;

  rock->esquerda = temp.direita;
  rock->direita = temp.esquerda;
}

// ***********************************************
// ******                                   ******
// ***********************************************
bool comparaPedra(tPedra rock1, tPedra rock2){
	if(rock1.esquerda == rock2.esquerda){
		if(rock1.direita == rock2.direita){
			return true;
		}
	}
	return false;
}

// ***********************************************
// ******                                   ******
// ***********************************************
int somaPedra(tPedra rock){
	return (rock.direita+rock.esquerda);
}


