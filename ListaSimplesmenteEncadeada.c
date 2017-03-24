
#include "ListaSimplesmenteEncadeada.h"


// ***********************************************
// ******                                   ******
// ***********************************************
void initListaSimples(tListaSimplesEncadeada* L){

	L->inicio = NULL;
	L->final = NULL;
	L->numElem = 0;
}

// ***********************************************
// ******                                   ******
// ***********************************************
void limpaListaSimples(tListaSimplesEncadeada* L){

	tNoSimples* cor = L->inicio;
	tNoSimples* buff = NULL;

	while(cor != NULL){
		buff = cor->prox;
		free(cor);
		cor = buff;
	}

	L->inicio = NULL;
	L->final = NULL;
	L->numElem = 0;
}

// ***********************************************
// ******                                   ******
// ***********************************************
void imprimeListaSimples(tListaSimplesEncadeada L) {

	tNoSimples* proximo = L.inicio;

	if(proximo != NULL){
		while( proximo->prox != NULL ){
			imprimePedra(proximo->V);
			proximo = proximo->prox;
		}
		imprimePedra(proximo->V);
	}

	else
		printf("Não ha elementos na lista");
	printf("\n__________________________________________________________\n");
}

// ***********************************************
// ******                                   ******
// ***********************************************
bool insereFinalListaSimples(tListaSimplesEncadeada* L, tPedra pedra) {

	tNoSimples* aInserir = alocaNoSimples(pedra);
	if(aInserir == NULL)
		return false;



	tNoSimples* ultimo = L->final;
	if(ultimo == NULL)      //Lista vazia
		L->inicio = aInserir;
	else					          //Lista não vazia
		ultimo->prox = aInserir;

	L->final = aInserir;
	L->numElem++;
	return true;
}

// ***********************************************
// ******                                   ******
// ***********************************************
bool insereInicioListaSimples(tListaSimplesEncadeada* L, tPedra pedra) {

	//Aloca um novo nó
	tNoSimples* aInserir = alocaNoSimples(pedra);
	if(aInserir == NULL)
		return false;

	if(L->final != NULL)        //Lista Não Vazia
		aInserir->prox = L->inicio;
	else                        //Lista Vazia
		L->final = aInserir;


	L->inicio = aInserir;
	L->numElem++;
	return true;
}

// ***********************************************
// ******                                   ******
// ***********************************************
tNoSimples* alocaNoSimples(tPedra pedra){

	tNoSimples* novo = (tNoSimples*) malloc(sizeof(tNoSimples));

	if(novo != NULL){
		novo->V.esquerda = pedra.esquerda;
    	novo->V.direita = pedra.direita;
		novo->prox = NULL;
	}

  return novo;
}



// ***********************************************
// ******                                   ******
// ***********************************************
int tamListaSimples(tListaSimplesEncadeada L){
	return L.numElem;
}

// ***********************************************
// ******                                   ******
// ***********************************************
tNoSimples* buscaElementoListaSimples(tListaSimplesEncadeada L, 
	tNoSimples** anterior, int pontas[], bool** esquerda, bool** inicio){

	(**esquerda) = false; //indica se o lado da pedra a ser colocado é o esquerdo
	(**inicio) = false;   //indica se deve ser colocado na ponta esquerda da mesa
	(*anterior) = NULL;      //elemento anterior ao achado
    tNoSimples* onde = L.inicio;
    int i;


    for(i=0 ; i<2 ; i++){            //Alterna entre ponta esquerda e direita
    	while( onde!=NULL ){         //Para caso acabe a lista


    		if(onde->V.direita > pontas[i]){       //Caso o lado direito seja maior
    			if(onde->V.esquerda == pontas[i]){ //Caso o lado esquerdo seja igual
    				(**esquerda) = true;
    				if(i==0)
    					(**inicio) = true;
    				return onde; 
    			}
    		}

    		else if(onde->V.direita == pontas[i]){ //Caso o lado direito seja igual
    			if(i==0)
    				(**inicio) = true;
    			return onde;
    		}
    		(*anterior) = onde;
    		onde = onde->prox;


    		//Fim do while
    	}
    	//Fim do for
    }


	return NULL; //Não foi encontrado
}

// ***********************************************
// ******                                   ******
// ***********************************************
bool insereOrdenadoListaSimples(tListaSimplesEncadeada* L, tPedra pedra){
	
	tNoSimples* aInserir = alocaNoSimples(pedra);

	//Não alocado
	if(aInserir == NULL)
		return false;

	tNoSimples* anterior = NULL;
	tNoSimples* correr= L->inicio;

	//Lista Vazia
	if(correr==NULL) 
		L->inicio = aInserir;

	//Lista Não Vazia
	else{

		//Enquanto for menor ou a lista não acabar
		while(pedra.direita < correr->V.direita){
			anterior = correr;
			correr = correr->prox;
			if(correr == NULL)
				break;
		}
		
		//Ajusta o valor da posição caso o lado direito seja igual
		if( correr != NULL){
			if( pedra.direita == correr->V.direita ){
				while(correr->V.esquerda > pedra.esquerda){
					anterior = correr;
					correr = correr->prox;
					if(correr == NULL )
						break;
					if(pedra.direita != correr->V.direita)	
						break;
				}
			}
		}


		if(anterior == NULL){      //Colocar na primeira posição da lista
			L->inicio = aInserir;
			aInserir->prox = correr;
		}

		else if(correr == NULL){  //Colocar no final da lista
			anterior->prox = aInserir;
		}

		else{                    //Meio da lista
			anterior->prox = aInserir;
			aInserir->prox = correr;
		}
	}

	L->numElem++;
	return true;
}

// ***********************************************
// ******                                   ******
// ***********************************************
bool removeElementoListaSimples(tListaSimplesEncadeada* L, 
	int pontas[], bool* esquerda, bool* inicio, tPedra* pedra){

	tNoSimples* anterior;
	tNoSimples* achei = buscaElementoListaSimples(*L, &anterior, pontas, &esquerda, &inicio);

	if(achei == NULL)
		return false;

	tNoSimples* proximo = achei->prox;

	if(tamListaSimples(*L)==1){ //O Único elemento
		L->inicio = NULL;
	}
	else if(anterior == NULL){ //Primeiro da lista
		L->inicio = proximo;
	}
	else if(proximo == NULL){ //Final da lista
		anterior->prox = proximo;
	}

	else{                     //Meio da lista
		anterior->prox = proximo;
	}

	*pedra = achei->V; //Retornando a pedra
	free(achei);
	L->numElem--;
	return true;
}

// ***********************************************
// ******                                   ******
// ***********************************************
tPedra removeElementoPosListaSimples(tListaSimplesEncadeada* L, int index){

	tNoSimples* achei = L->inicio;
	tNoSimples* anterior = NULL;
	tNoSimples* proximo = NULL;
	tPedra pedra;

	//Procura ponteiro do indice especificado
	int p;
	for(p=0 ; p<index ; p++){
		anterior = achei;
		achei = achei->prox;
	}

	if(achei == NULL)
		return pedra;

	proximo = achei->prox;


	if(anterior == NULL){      //Primeiro ou único da lista
		L->inicio = achei->prox;
		if(proximo == NULL) //Se for o unico da lista
			L->final = NULL;
	}
	else if(proximo == NULL){ //Final da lista
		anterior->prox = proximo;
		L->final = anterior;
	}
	else{                     //Meio da lista
		anterior->prox = proximo;
		
	}

	pedra = achei->V;

	free(achei);
	L->numElem--;
	return pedra;
}

// ***********************************************
// ******                                   ******
// ***********************************************
int somaListaSimples(tListaSimplesEncadeada L){
	int soma=0, i;
	tNoSimples* temp = L.inicio;
	for(i=0 ; i<tamListaSimples(L) ; i++){
		soma = soma + somaPedra(temp->V);
		temp = temp->prox; 
	}
	return soma;
}