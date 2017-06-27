// Trabalho 2
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#import "arvoreb.h"
#import "hashtable.h"

int main() {
	// Por arvore

	// pegar tamanho da árvore? Calcular por tamanho do arquivo?
	ArvAvl* arv;
	int x; int vetor[MAX];
	int i, j, k, n;

	for(i = 0; i<MAX; i++) {
		vetor[i] = insere(i, arv);
	}
}
