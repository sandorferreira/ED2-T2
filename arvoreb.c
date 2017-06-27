//Arvore Balanceada

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <sys/time.h>

#define MAX 64

// *char info = palavra
typedef struct avl {
	char* info;
	int altura;
	struct avl *esq;
	struct avl *dir;
}ArvAvl;

typedef struct ArvAvl* TipoDicionario;

int maior(int a, int b) {
	if (a > b) {
		return a;
	} else {
		return b;
	}
}

void Inicializa(TipoDicionario *Dicionario) {
	*Dicionario = NULL;
}

ArvAvl* rotacaoDireita( ArvAvl * K2 ) {
	ArvAvl * K1;
	K1 = K2->esq;
	K2->esq = K1->dir;
	K1->dir = K2;
	K2->altura = maior( altura( K2->esq ), altura( K2->dir ) ) + 1; 
	K1->altura = maior( altura( K1->esq ), K2->altura ) + 1;
	
	return K1;  //nova raiz
}

ArvAvl* rotacaoEsquerda( ArvAvl * K1 ) {
	ArvAvl * K2;
	K2 = K1->dir;
	K1->dir = K2->esq;
	K2->esq = K1;
	K1->altura = maior( altura( K1->esq ), altura( K1->dir ) ) + 1; 
	K2->altura = maior( altura( K2->dir ), K1->altura ) + 1;
	
	return K2;  //nova raiz
}

ArvAvl * rotacaoEsquerdaDireita( ArvAvl * K3 ) {
	K3->esq = rotacaoEsquerda( K3->esq );
	return rotacaoDireita( K3 ); 
}

ArvAvl * rotacaoDireitaEsquerda( ArvAvl * K1 ) {
	K1->dir = rotacaoDireita( K1->dir );
	return rotacaoEsquerda( K1 ); 
}

ArvAvl* aloca(int info) {
	ArvAvl *arv;
	arv = (ArvAvl*)malloc(sizeof(ArvAvl)); arv->info = info;
	arv->altura = 0;
	arv->esq = arv->dir = NULL;
	return arv;
}

int altura (ArvAvl *a) {
	if( a == NULL) return -1;
	return a->altura; 
}

ArvAvl* insere( int info, ArvAvl *arv ) {
	if( arv == NULL ) {
		arv = aloca(info); 
	}
	else if( info < arv->info ) {
		arv->esq = insere( info, arv->esq );
		if( altura( arv->esq ) - altura( arv->dir ) == 2 ) {
			if( info < arv->esq->info )
				arv = rotacaoDireita( arv );
			else
				arv = rotacaoEsquerdaDireita( arv );
		}
	}
	else if( info > arv->info ) {
		arv->dir = insere( info, arv->dir );
		if( altura( arv->dir ) - altura( arv->esq ) == 2 ) {
			if( info > arv->dir->info )
				arv = rotacaoEsquerda( arv );
			else
				arv = rotacaoDireitaEsquerda( arv );
		}	
	}
	arv->altura = maior( altura( arv->esq ), altura( arv->dir ) ) + 1;
	return arv;
}