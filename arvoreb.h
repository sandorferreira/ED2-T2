#ifndef ARVOREB_H
#define ARVOREB_H

typedef char *TipoChave[256];

struct TipoRepeticao{
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
typedef struct TipoNo* TipoApontador;

typedef struct TipoNo {
    TipoRegistro Reg;
    TipoApontador Esq, Dir;
    TipoInclinacao BitE, BitD;
} TipoNo;

// funcoes
void EE(TipoApontador *Ap);
void ED(TipoApontador *Ap);
void DD(TipoApontador *Ap);
void DE(TipoApontador *Ap);
void IInsere(TipoRegistro x, TipoApontador *Ap,
        TipoInclinacao *IAp, short *Fim);
void Insere(TipoRegistro x, TipoApontador *Ap);
void Inicializa(TipoApontador *Dicionario);
void EsqCurto(TipoApontador *Ap, short *Fim);
void DirCurto(TipoApontador *Ap, short *Fim);
void Antecessor(TipoApontador q, TipoApontador *r, short *Fim);
void IRetira(TipoRegistro x, TipoApontador *Ap, short *Fim);
void Retira(TipoRegistro x, TipoApontador *Ap);
void Pesquisa(TipoRegistro *x, TipoApontador *p);
void Testa1(TipoApontador p, int nivel, int *NivelFolhas, short *PrimeiraFolha);
void Testa2(TipoApontador p, int *NivelFolhas, short *PrimeiraFolha);
void Testa(TipoApontador Arvore);
double rand0a1();
void Permut(int *A, int n);

#endif
