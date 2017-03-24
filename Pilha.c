
#include "Pilha.h"

// ***********************************************
// ******                                   ******
// ***********************************************
bool initPilha(tPilha* P){
	P->topo = -1;
	P->V = (tPedra*) malloc(NUM_PEDRAS*sizeof(tPedra));

	if(P->V == NULL)
		return false; //Não conseguiu alocar
	else
		return true;  //Conseguiu alocar
}

// ***********************************************
// ******                                   ******
// ***********************************************
void limpaPilha(tPilha* P){
	P->topo = -1;
	free(P->V);
}

// ***********************************************
// ******                                   ******
// ***********************************************
bool Empilha(tPilha** P, tPedra pedra){
	if((**P).topo < NUM_PEDRAS-1){
		(**P).topo++;
		(**P).V[(**P).topo] = pedra;
		return true;
	}
	else
		return false;
}

// ***********************************************
// ******                                   ******
// ***********************************************
bool Desempilha(tPilha* P, tPedra* pedra){
	if(P->topo > -1){

		//Retornando a pedra do topo
		pedra->esquerda = P->V[ P->topo ].esquerda;
		pedra->direita = P->V[ P->topo ].direita;

		P->topo--;
		return true;
	}
	else
		return false;
}

void mostraTopoPilha(tPilha P){
	imprimePedra(P.V[P.topo]);
}
