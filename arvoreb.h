#ifndef ARVOREB_H
#define ARVOREB_H

typedef struct avl {
	char* info;
	int altura;
	struct avl *esq;
	struct avl *dir;
}ArvAvl;

typedef struct ArvAvl* TipoDicionario;

// funcoes
int maior(int a, int b);
void Inicializa(TipoDicionario *Dicionario);
ArvAvl* rotacaoDireita( ArvAvl * K2 );
ArvAvl* rotacaoEsquerda( ArvAvl * K1 );
ArvAvl * rotacaoEsquerdaDireita( ArvAvl * K3 );
ArvAvl * rotacaoDireitaEsquerda( ArvAvl * K1 );
ArvAvl* aloca(int info);
int altura (ArvAvl *a);
ArvAvl* insere( int info, ArvAvl *arv );

#endif
