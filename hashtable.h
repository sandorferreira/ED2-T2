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
    int pos;
    struct TipoRepeticaoHash *repeticao;
    
} TipoItem;
typedef unsigned int TipoIndice;
typedef TipoItem* TipoDicionario[M];
TipoDicionario Tabela;
TipoPesos p;
TipoItem Elemento;

// Funcoes
void GeraPesos(TipoPesos p);
TipoIndice h(TipoChaveHash Chave);
void InicializaHash(TipoDicionario T);
void criaHash (FILE* indice, TipoDicionario T);
TipoApontadorHash PesquisaHash(TipoChaveHash Ch, TipoDicionario T);
void InsereHash(TipoChaveHash x, TipoDicionario T, int pos);
void novaPalavraHash(TipoChaveHash Chave, TipoDicionario T, int aux, int pos);
void checaPalavraHash(TipoDicionario T, TipoChaveHash x, int nLinha);
void adicionaLinhaHash(TipoDicionario T, int pos, int nLinha);
void RetiraHash(TipoChaveHash Ch, TipoPesos p, TipoDicionario T);
void imprimeLinhas (TipoDicionario T, int i);
void ImprimeHash(TipoDicionario tabela);
void ImprimeHash2(TipoDicionario tabela);
void LerPalavraHash(char *p, int Tam);
void criaRepeticaoHash(int nLinha, TipoItem Item);

#endif
