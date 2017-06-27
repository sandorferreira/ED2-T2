#ifndef HASHTABLE_C
#define HASHTABLE_C

typedef unsigned int TipoApontador;
typedef char TipoChave[N];
typedef unsigned TipoPesos[N];
typedef struct TipoItem {
  /* outros componentes */
  TipoChave Chave;
} TipoItem;
typedef unsigned int TipoIndice;
TipoDicionario Tabela;
TipoPesos p;
TipoItem Elemento;

// Funcoes
void GeraPesos(TipoPesos p);
TipoIndice h(TipoChave Chave, TipoPesos p);
void Inicializa(TipoDicionario T);
TipoApontador Pesquisa(TipoChave Ch, TipoPesos p, TipoDicionario T);
void Insere(TipoItem x, TipoPesos p, TipoDicionario T);
void Retira(TipoChave Ch, TipoPesos p, TipoDicionario T);
void Imprime(TipoDicionario tabela);
void LerPalavra(char *p, int Tam);

#endif
