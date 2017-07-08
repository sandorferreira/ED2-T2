// Trabalho 2
/* Informar nomes dos arquivos teste.txt e alfabeto.txt na linha de
comando */
/* Exemplo: a.out teste.txt alfabeto.txt
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "arvoreb.h"
#include "hashtable.h"

#define MAXALFABETO 255
#define TRUE 1
#define FALSE 0
typedef short TipoAlfabeto[MAXALFABETO + 1];
int palavrasIndice;
FILE *ArqTxt, *ArqAlf, *ArqPalavras, *ArqTeste;
TipoAlfabeto Alfabeto;
char Palavra[256];
char Linha[1250];
int i;
short aux;

void indiceArvore() {
    TipoApontadorArv arvore = criaArvore(ArqPalavras);
    int nLinha = 0;
    aux = FALSE;
    short teste;
    while (fgets(Linha, 1250, ArqTxt) != NULL) { //ENQUANTO PEGAR LINHA DO LISTA
        nLinha++;
        for (i = 1; i <= strlen(Linha); i++) {
            if (Alfabeto[Linha[i - 1] + 127]) {
                sprintf(Palavra + strlen(Palavra), "%c", Linha[i - 1]);
                aux = TRUE;
            } else {
                if (aux) {
                    //                    puts(Palavra);
                    teste = adicionaLinhaArv(Palavra, nLinha, arvore);
                    *Palavra = '\0';
                    aux = FALSE;
                }
            }
        }
    }
    int pos = 0;
    teste = 1;
    while (teste != 0) {
        pos++;
        teste = imprimeArv(arvore, pos, ArqTeste);
    }
    if (aux) {
        puts(Palavra);
        *Palavra = '\0';
    }
    fclose(ArqTxt);
    fclose(ArqAlf);
}

void indiceHash() {
    TipoDicionario hash;
    criaHash(ArqPalavras, hash);
    int nLinha = 0;
    aux = FALSE;
    short teste = FALSE;
    while (fgets(Linha, 1250, ArqTxt) != NULL) { //ENQUANTO PEGAR LINHA DO LISTA
        nLinha++;
        for (i = 1; i <= strlen(Linha); i++) {
            if (Alfabeto[Linha[i - 1] + 127]) {
                sprintf(Palavra + strlen(Palavra), "%c", Linha[i - 1]);
                aux = TRUE;
            } else {
                if (aux) {
                    checaPalavraHash(hash, Palavra, nLinha);
                    *Palavra = '\0';
                    aux = FALSE;
                }
            }
        }
    }
    ImprimeHash(hash, ArqTeste);
    if (aux) {
        puts(Palavra);
        *Palavra = '\0';
    }
    fclose(ArqTxt);
    fclose(ArqAlf);
}

void buscaArvore() {
    char palavra1[50], palavra2[50];
    scanf("%s %s", palavra1, palavra2);
    TipoApontadorArv arvore = criaArvore(ArqPalavras);
    int nLinha = 0;
    aux = FALSE;
    short teste;
    while (fgets(Linha, 1250, ArqTxt) != NULL) { //ENQUANTO PEGAR LINHA DO LISTA
        nLinha++;
        for (i = 1; i <= strlen(Linha); i++) {
            if (Alfabeto[Linha[i - 1] + 127]) {
                sprintf(Palavra + strlen(Palavra), "%c", Linha[i - 1]);
                aux = TRUE;
            } else {
                if (aux) {
                    //                    puts(Palavra);
                    teste = adicionaLinhaArv(Palavra, nLinha, arvore);
                    *Palavra = '\0';
                    aux = FALSE;
                }
            }
        }
    }
    TipoRegistro* aux1 = pesquisaArv(arvore, palavra1);
    TipoRegistro* aux2 = pesquisaArv(arvore, palavra2);
    imprimeLinhasArv(aux1, aux2);
    fclose(ArqTxt);
    fclose(ArqAlf);
}

void imprimeLinhasArv(TipoRegistro* no1, TipoRegistro* no2) {
    TipoRepeticao* aux1 = no1->repeticao;
    TipoRepeticao* aux2 = no2->repeticao;
    while (aux1 != NULL) {
        while (aux2 != NULL) {
            if (aux1->linha == aux2->linha) {
                rewind(ArqTxt);
                imprimeLinha(aux1->linha);
            }
            aux2 = aux2->proximo;
        }
        aux2 = no2->repeticao;
        aux1 = aux1->proximo;
    }
}

void imprimeLinha(int nLinha) {
    int aux = 0;
    while (fgets(Linha, 1250, ArqTxt) != NULL) { //ENQUANTO PEGAR LINHA DO LISTA
        aux++;
        if (aux == nLinha) {
            puts(Linha);
        }
    }
}

void buscaHash() {
    char palavra1[50], palavra2[50];
    scanf("%s %s", palavra1, palavra2);
    TipoDicionario hash;
    criaHash(ArqPalavras, hash);
    int nLinha = 0;
    aux = FALSE;
    short teste;
    while (fgets(Linha, 1250, ArqTxt) != NULL) { //ENQUANTO PEGAR LINHA DO LISTA
        nLinha++;
        for (i = 1; i <= strlen(Linha); i++) {
            if (Alfabeto[Linha[i - 1] + 127]) {
                sprintf(Palavra + strlen(Palavra), "%c", Linha[i - 1]);
                aux = TRUE;
            } else {
                if (aux) {
                    checaPalavraHash(hash, Palavra, nLinha);
                    *Palavra = '\0';
                    aux = FALSE;
                }
            }
        }
    }
    int aux1 = Pesquisa(palavra1, hash);
    int aux2 = Pesquisa(palavra2, hash);
    imprimeLinhasHash(hash[aux1]->repeticao, hash[aux2]->repeticao);
    fclose(ArqTxt);
    fclose(ArqAlf);
}

void imprimeLinhasHash (TipoRepeticaoHash* aux1, TipoRepeticaoHash* aux2){
    TipoRepeticaoHash* item1 = aux1;
    TipoRepeticaoHash* item2 = aux2;
    while (item1 != NULL){
        while (item2 != NULL){
            if (item1->linha == item2->linha){
                rewind(ArqTxt);
                imprimeLinha(item1->linha);
            }
            item2 = item2->proximo;
        }
        item2 = aux2;
        item1 = item1->proximo;
    }
}

void DefineAlfabeto(short *Alfabeto) {
    char Simbolos[MAXALFABETO + 1];
    int i, CompSimbolos;
    char *TEMP;
    for (i = 0; i <= MAXALFABETO; i++)
        Alfabeto[i] = FALSE;
    fgets(Simbolos, MAXALFABETO + 1, ArqAlf);
    TEMP = strchr(Simbolos, '\n');
    if (TEMP != NULL) *TEMP = 0;
    CompSimbolos = strlen(Simbolos);
    for (i = 0; i < CompSimbolos; i++)
        Alfabeto[Simbolos[i] + 127] = TRUE;
    Alfabeto[0] = FALSE; /* caractere de codigo zero: separador */
}

int main(int argc, char *argv[]) {
    ArqTxt = fopen("Texto.txt", "r");
    ArqAlf = fopen("Alfabeto.txt", "r");
    ArqPalavras = fopen("Palavras_Chave.txt", "r");
    ArqTeste = fopen("saida.txt", "w"); //O TRABALHO TEM Q ATUALIZAR O INDICE, MAS PARA N TER Q VOLTAR A CADA TESTE....
    DefineAlfabeto(Alfabeto);
    int hashOuArv;
    scanf("%d", &hashOuArv);
    if (hashOuArv == 1) {
        indiceArvore();
    }
    if (hashOuArv == 2) {
        indiceHash();
    }
    if (hashOuArv == 3) {
        buscaArvore();
    }
    if (hashOuArv == 4) {
        buscaHash();
    }
    return 0;
}
/* End. */