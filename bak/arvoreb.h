#ifndef ARVOREB_H
#define ARVOREB_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef char *TipoChave[256];

struct TipoRepeticao {
    int linha;
    struct TipoRepeticao *proximo;
};

typedef struct TipoRepeticao TipoRepeticao;

typedef struct TipoRegistro {
    /* outros componentes */
    char Chave[250];
    struct TipoRepeticao *repeticao;
} TipoRegistro;

typedef enum {
    Vertical, Horizontal
} TipoInclinacao;
typedef struct TipoNo* TipoApontadorArv;

typedef struct TipoNo {
    TipoRegistro Reg;
    TipoApontadorArv Esq, Dir;
    TipoInclinacao BitE, BitD;
} TipoNo;

// funcoes
void EE(TipoApontadorArv *Ap);
void ED(TipoApontadorArv *Ap);
void DD(TipoApontadorArv *Ap);
void DE(TipoApontadorArv *Ap);
void IInsere(TipoRegistro x, TipoApontadorArv *Ap,
        TipoInclinacao *IAp, short *Fim);
void InsereArv(TipoRegistro x, TipoApontadorArv *Ap);
void Inicializa(TipoApontadorArv *Dicionario);
void EsqCurto(TipoApontadorArv *Ap, short *Fim);
void DirCurto(TipoApontadorArv *Ap, short *Fim);
void Antecessor(TipoApontadorArv q, TipoApontadorArv *r, short *Fim);
void IRetira(TipoRegistro x, TipoApontadorArv *Ap, short *Fim);
void Retira(TipoRegistro x, TipoApontadorArv *Ap);
void PesquisaArv(TipoRegistro *x, TipoApontadorArv *p);
void Testa1(TipoApontadorArv p, int nivel, int *NivelFolhas, short *PrimeiraFolha);
void Testa2(TipoApontadorArv p, int *NivelFolhas, short *PrimeiraFolha);
void Testa(TipoApontadorArv Arvore);
double rand0a1();
void Permut(int *A, int n);
TipoRegistro* criaRegistro(char *Palavra);
void imprimeArvore(TipoApontadorArv Arvore);
void imprimeArv2(TipoApontadorArv Arvore, FILE* ArqSaida);
void imprimeArv(TipoApontadorArv Arvore, FILE* ArqSaida);
void criaRepeticaoArv(int nLinha, TipoApontadorArv Arvore);
short adicionaLinhaArv(char *Palavra, int nLinha, TipoApontadorArv Arvore);
TipoApontadorArv criaArvore(FILE* indice);

#endif
