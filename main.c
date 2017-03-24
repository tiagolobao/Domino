/*
	Aluno: Tiago Britto Lobão
	Professor: Apolinário
	Disciplina: Estrutura de dados e Algoritimos I

	Programa: Jogo de dominó
*/

/* Comentários sobre as estruturas nos arquivos ".h" */

/* ------------------------------------------------------------------------------------------*/
/* --------------------- HEADERS------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------------*/

//Estuturas de dados utilizadas
#include "ListaSimplesmenteEncadeada.h" //Pedras na mesa
#include "Pilha.h" //Pedras a serem compradas (APE)

#define clc 100 //Quantidade de linhas puladas (\n) para limpara tela

/* ------------------------------------------------------------------------------------------*/
/* ------------ CABECALHO PROCEDIMENTOS E FUNÇÕES ------------------------------------------*/
/* ----------------------------------------------------------------------------------------*/

//*********************************************************************
/* Busca número do jogador que deve iniciar a partida */
int buscaIniciante(tListaSimplesEncadeada L[], int num_jogadores);

//*********************************************************************
/* Mostra o título inicial do jogo */
void mostraTitulo();

//*********************************************************************
/* Obtem o número de jogadores */
int perguntaNumeroJodagores();

//*********************************************************************
/* Verifica se o usuário deseja simular uma nova partida */
bool perguntaSeQuerBis();

//*********************************************************************
/* Confere a soma de pontos de forma a achar o vencedor da partida */
int conferePontos(tListaSimplesEncadeada J[], int num_jogadores);

//*********************************************************************
/* muda a variável index para o número do proximo jogador */
void proximoJogador(int* index, int num_jogadores);

//*********************************************************************
/* Gera uma associação de pedras embaralhadas na pilha */
void embaralhaPedras(tPilha* ape);

//*********************************************************************
/* Distribui as pedras do APE para a mão dos jogadores */
void distribuiPedras(tPilha* ape, tListaSimplesEncadeada jogadores[]);

//*********************************************************************
/* Mostra mensagem de erro */
void erro(void);

//*********************************************************************
/* Limpa a tela */
void clear(void);

/* ------------------------------------------------------------------------------------------*/
/* --------------------- MAIN FUNCTON ------------------------------------------------------*/
/* ----------------------------------------------------------------------------------------*/

int main() {


	/* ----------Inizializa as Estuturas e variáveis--------------------------- */

	tPilha APE;
	tListaSimplesEncadeada Mesa;
	tListaSimplesEncadeada J[4];

	//Variáveis
	int i,p, j, enderecoJogador, pontas[2], vencedor;
	tPedra pedraBuffer;
	bool esquerda, inicio, flag, denovo;

	/* -----Interface usuário--------------------------------------------------- */


	do{
		initPilha(&APE);
		initListaSimples(&Mesa);
		mostraTitulo();
		
		int numeroJogadores = perguntaNumeroJodagores();

		//Inicia os jogadores
		for(i=0 ; i<numeroJogadores ; i++) 
		  initListaSimples(&J[i]);


		/* -----Inicia o jogo------------------------------------------------------- */

		embaralhaPedras(&APE);


		//Distribui as pedras
		printf(" Computador - Vamos agora distribuir as peças...\n");
		while( tamListaSimples(J[0]) != MAX_MAO ){

			for(i=0 ; i<numeroJogadores ; i++){
				Desempilha(&APE,&pedraBuffer);
				insereOrdenadoListaSimples(&J[i], pedraBuffer);
			}
		}

		for(i=0 ; i<numeroJogadores ; i++){
			printf("\n Computador - Essas são as peças do jogador %d \n ",i+1);
			imprimeListaSimples(J[i]);
		}

		// Pause para análise das pedras
		printf("\n\n Computador - Agora podemos jogar =)\n");
		printf(" Computador - Aperte enter para começar.");
		getchar(); //pause
		clear();
		printf(" Você - Vamos lá! \n");
		printf(" Computador - O primeiro a jogar vai ser o de maior pedra \n");

		//Faz a primeira jogada, procurando o maior peça
		enderecoJogador = buscaIniciante(J,numeroJogadores);
		printf("\n Computador - O primeiro jogador é o número %d\n", enderecoJogador+1);
		pedraBuffer = removeElementoPosListaSimples(&J[enderecoJogador], 0);
		if(!insereInicioListaSimples(&Mesa, pedraBuffer)) erro();
		printf(" Jogador %d - Coloco a pedra ", enderecoJogador+1);
		imprimePedra(pedraBuffer);



		/* -----Loop Jogadas------------------------------------------------------------- */

		//bool esquerda  ==> true para se o lado a ser colocado é pedra.esquerda
		//bool inicio    ==> true para se a pedra deve ser colocada no inicio da mesa

		//bool esquerda  ==> false para se o lado a ser colocado é pedra.direita
		//bool inicio    ==> false para se a pedra deve ser colocada no final da mesa

		//Nessa variável, serão colocadas as pontas livres da mesa
		flag=true;
		p=1; //Garante que a primeira rodada o iniciante não jogue duas vezes
		while(flag){
			j=0; //Contador de pessoas que não possuem pedras pra jogar e não existe mais APE
			for(i=p ; i<numeroJogadores ; i++){
				pontas[0] = Mesa.inicio->V.esquerda;
				pontas[1] = Mesa.final->V.direita;
			 	proximoJogador(&enderecoJogador, numeroJogadores); //Atualiza endereço do proximo jogador
			 	
			 	if(removeElementoListaSimples(&J[enderecoJogador], pontas, &esquerda, &inicio, &pedraBuffer)){
			 		printf("\n Jogador %d - Coloco a pedra ", enderecoJogador+1);
			 		imprimePedra(pedraBuffer);

			 		if(inicio && esquerda)
			 			invertePedra(&pedraBuffer);
			 		if(!inicio && !esquerda)
			 			invertePedra(&pedraBuffer);
			 		if(inicio)
			 			insereInicioListaSimples(&Mesa, pedraBuffer);
			 		else
			 			insereFinalListaSimples(&Mesa, pedraBuffer);
			 	}
			 	else{
			 		if(Desempilha(&APE, &pedraBuffer)){
			 			insereOrdenadoListaSimples(&J[enderecoJogador], pedraBuffer);
			 			printf("\n Jogador %d - Não tenho pedra! vou comprar uma.", enderecoJogador+1);
			 		}
			 		else{
			 			printf("\n Jogador %d - Não tenho pedra e não existe mais pedra pra comprar", enderecoJogador+1);
			 			j++;
			 		}
		 		}
			}
			printf("\n");

			//Imprime a mesa
			printf("\n Computador: Essas São as pedras da mesa\n ");
			imprimeListaSimples(Mesa);

			//Imprime a proxima peça do APE
			if(APE.topo>-1){
				printf("\n Computador: Essa é a proxima pedra a ser comprada: ");
				mostraTopoPilha(APE);
				printf("\n");
			}
			else
				printf("\n Computador - Não há mais pedras para compra \n");

			//Imprime a mão dos jogadores
			for(i=0 ; i<numeroJogadores ; i++){
				printf("\n Computador - Essas são as peças do jogador %d \n ",i+1);
				imprimeListaSimples(J[i]);
			}
			printf("\n\n Computador - aperte enter para ver a próxima rodada");
			getchar();
			clear();


			//Verifica se algum jogador já venceu
			for(i=0 ; i<numeroJogadores ; i++){
				proximoJogador(&enderecoJogador, numeroJogadores);
				if(tamListaSimples(J[enderecoJogador]) == 0){
					flag = false;
					vencedor = enderecoJogador;
					break; 
					/*Com parada forçada, garantimos que o primeiro 
					jogador a terminar as pedras vai ser o ganhador */
				}
			}

			//Verifica se todos os jogadores não possuem peças para jogar
			if(j==numeroJogadores){
				printf("\n Computador - Não há mais jogadas possíveis");
				vencedor = conferePontos(J,numeroJogadores); //Quem tem mais pontos ganha
				flag=false;
			}
			p=0;
		}



		/* -----Termina jogo----------- */

		if(j==numeroJogadores)
			printf("\n\n Computador - Parabéns jogador %d, você ganhou por ter mais pontos!!!", vencedor+1);
		else
			printf("\n\n Computador - Parabéns jogador %d, você ganhou por ter jogado todas as pedras!!!\n", vencedor+1);

		getchar();
		
		//Limpando as listas e a pilha
		limpaPilha(&APE);
		limpaListaSimples(&Mesa);
		for(i=0 ; i<numeroJogadores ; i++)
			limpaListaSimples(&J[i]);


		denovo = perguntaSeQuerBis();
		clear();
	}while(denovo);

	printf(" Computador - Volte sempre!\n\n");

	return 1;
}










/* ------------------------------------------------------------------------------------------*/
/* --------------------- FUNÇOES COMPLEMENTARES---------------------------------------------*/
/* ----------------------------------------------------------------------------------------*/


// ***********************************************
// ******                                   ******
// ***********************************************
int buscaIniciante(tListaSimplesEncadeada L[], int num_jogadores){

	int i=0,j=1,iniciante = 0;
	tPedra pedras[num_jogadores];
	for(i=0 ; i<num_jogadores ; i++){
		pedras[i].direita = L[i].inicio->V.direita;
		pedras[i].esquerda = L[i].inicio->V.esquerda;
	}
	i=0;

	//Busca maior valor entre as maiores encontradas em cada mão
	while(j<num_jogadores){
		if(somaPedra(pedras[i]) == somaPedra(pedras[j])){
			if(pedras[i].direita < pedras[j].direita){ //Na soma igual, Direita vence
				iniciante = j;
				i = j;
				j++;
			}
			else j++;
		}
		else if(somaPedra(pedras[i]) < somaPedra(pedras[j])){
			iniciante = j;
			i = j;
			j++;
		}
		else j++; //Se somaPedra(pedras[i]) for maior
	}


	return iniciante;
}

// ***********************************************
// ******                                   ******
// ***********************************************
void proximoJogador(int* index, int num_jogadores){
	if(*index == (num_jogadores-1))
		*index = 0;
	else
		(*index)++;
}

// ***********************************************
// ******                                   ******
// ***********************************************
void embaralhaPedras(tPilha* ape){

	srand ( time(NULL) );

	tPedra unid;
	tListaSimplesEncadeada pedras;
	int j,k;

	initListaSimples(&pedras);

	//Gera as peças
	printf("\n Computador - Gerando as peças...\n");
	for(j=0 ; j<7 ; j++){          //Linha de peças
		for(k=0 ; k<=j ; k++){    //Coluna de peças
			unid.esquerda = k;
			unid.direita = j;
			if(!insereInicioListaSimples(&pedras,unid))
				erro();
		}
	}
	imprimeListaSimples(pedras);


	//Colocando na pilha de forma aleatória
	printf("\n Computador - Embaralhando...\n");
	while(tamListaSimples(pedras)>0){
		int index = rand();
		index = index % tamListaSimples(pedras);
		unid = removeElementoPosListaSimples(&pedras,index);
		Empilha(&ape, unid);
	}

	limpaListaSimples(&pedras);
}


// ***********************************************
// ******                                   ******
// ***********************************************
void mostraTitulo(){
	clear();
	printf("-------------------------- DOMINO --------------------\n");
	printf("------------------ por: Tiago Britto Lobão -----------\n");
	printf("-----------------    Estrutura de dados   -----------\n\n");
	printf("   ___________\n");
	printf("  |    .|.   .|\n");
	printf("  |  .  |  .  |\n");
	printf("  |.    |.   .|\n");
	printf("  |_____|_____|\n\n");
}

// ***********************************************
// ******                                   ******
// ***********************************************
int perguntaNumeroJodagores(){

	int num_jogadores=0;
	bool bandeira;

	do{
		printf("\n\n Computador - Quantas pessoas vão jogar?");
		printf("\n Você - ");
		scanf("%d%*c", &num_jogadores);
		bandeira = (num_jogadores < 2) || (num_jogadores > 4);
		if(bandeira)
			printf(" Computador - Só é possível jogar de 2 a 4 pessoas!");

	}
	while(bandeira);

	printf(" Computador - Beleza, vamos começar!\n");
	return num_jogadores;

}



// ***********************************************
// ******                                   ******
// ***********************************************
bool perguntaSeQuerBis(){

	char resposta;
	bool bandeira;

	do{
		printf("\n\n Computador - Deseja realizar outra partida? [Y/N]");
		printf("\n Você - ");
		scanf("%c%*c", &resposta);
		bandeira = (resposta != 'Y') && (resposta != 'N');
		if(bandeira)
			printf(" Computador - Não entendi...");

	}
	while(bandeira);

	if(resposta == 'Y')
		return true;
	else
		return false;

}

// ***********************************************
// ******                                   ******
// ***********************************************
int conferePontos(tListaSimplesEncadeada J[], int num_jogadores){
	
	int i=0, j=1, winner=0;

	//Busca maior valor do somatório de pedras
	while(j<num_jogadores){
		if(somaListaSimples(J[i]) < somaListaSimples(J[j])){
			winner = j;
			i = j;
			j++;
		}
		else j++;
	}

	return winner;
}


// ***********************************************
// ******                                   ******
// ***********************************************
void erro(void){
	printf("\n\nComputador - Ocorreu algum problema... =/\n");
	printf("Computador - Tchau!\n\n");
	exit(1);
}

// ***********************************************
// ******                                   ******
// ***********************************************
void clear(void){
	int v;
	for(v=0 ; v<=clc ; v++)
		printf("\n");
}
