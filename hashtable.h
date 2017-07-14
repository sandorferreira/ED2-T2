#ifndef HASHTABLE_C
#define HASHTABLE_C
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define M  1000
#define N  50   /* Tamanho da chave */

typedef unsigned int TipoApontadorHash;
typedef char TipoChaveHash[N];
typedef unsigned TipoPesos[N];

struct TipoRepeticaoHash {
    int linha;
    struct TipoRepeticaoHash *proximo;
};

typedef struct TipoRepeticaoHash TipoRepeticaoHash;

typedef struct TipoItem {
    TipoChaveHash Chave;
    struct TipoRepeticaoHash *repeticao;

} TipoItem;
typedef unsigned int TipoIndice;
typedef TipoItem* TipoDicionario[M];
TipoDicionario Tabela;
TipoPesos p;
TipoItem Elemento;

// Funcoes
TipoIndice h(TipoChaveHash Chave);
void InicializaHash(TipoDicionario T);
TipoApontadorHash Pesquisa(TipoChaveHash Ch, TipoDicionario T);
void InsereHash(TipoChaveHash x, TipoDicionario T);
void novaPalavraHash(TipoChaveHash Chave, TipoDicionario T, int aux);
void checaPalavraHash(TipoDicionario T, TipoChaveHash x, int nLinha);
void adicionaLinhaHash(TipoDicionario T, int pos, int nLinha);
void imprimeLinhas(TipoDicionario T, int i);
void imprimeHash(TipoApontadorHash apontador, TipoDicionario T);
int procuraLinhaHash(int linha, TipoChaveHash palavra, TipoDicionario T);
void criaRepeticaoHash(int nLinha, TipoItem Item);

#endif
