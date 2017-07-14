#ifndef ARVORE_H
#define ARVORE_H

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/time.h>
#define TRUE  1
#define FALSE 0
int i;

typedef char* TipoChave;
struct TipoRepeticao {
    int linha;
    struct TipoRepeticao *proximo;
};
typedef struct TipoRepeticao TipoRepeticao;
typedef struct TipoRegistro {
  TipoChave Chave;
  struct TipoRepeticao *repeticao;
  /* outros componentes */
} TipoRegistro;
typedef struct TipoNo * TipoApontador;
typedef struct TipoNo {
  TipoRegistro Reg;
  TipoApontador Esq, Dir;
} TipoNo;
typedef TipoApontador TipoDicionarioArv;

// funcoes
void PesquisaArv(TipoRegistro *x, TipoApontador *p);
void Insere(TipoRegistro x, TipoApontador *p);
void Inicializa(TipoApontador *Dicionario);
void Antecessor(TipoApontador q, TipoApontador *r);
void Retira(TipoRegistro x, TipoApontador *p);
void Central(TipoApontador p);
void TestaI(TipoNo *p, char* pai);
void Testa(TipoNo *p);
double rand0a1();
void Permut( int A[], int n);
void imprimeArvore(TipoNo* arv);
short adicionaLinhaArv(char *Palavra, int nLinha, TipoNo* Arvore);
void criaRepeticaoArv(int nLinha, TipoNo* Arvore);
TipoNo* criaArvore();
void imprimeNo(TipoNo* Arvore);

#endif
