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
char Indice[1000][256];
char Linha[1250];
int i;
short aux;

void pegaIndice(FILE* ArqPalavras) {
    int j=0;
    while (fgets(Linha, 256, ArqPalavras) != NULL) {
        for (i = 0; i < strlen(Linha) - 1; i++) {
            Indice[j][i] = Linha[i];
        }
        j++;
    }
    j++;
}

void ordenaIndice(){
    int j=0;
    char aux[256];
    while(Indice[i+1][0] != 0){
        if (strcmp(Indice[i],Indice[i+1])>0){
            strcpy(aux,Indice[i]);
            strcpy(Indice[i],Indice[i+1]);
            strcpy(Indice[i+1],aux);
            if(i>0)
                i-=2;
            else
                i-=1;
        }
        i++;
    }
//    for (i=0;i<1000;i++){
//        if (Indice[i][0]!=0)
//            puts(Indice[i]);
//    }
}

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
    teste = 1;
    imprimeArv(arvore, ArqTeste);
    if (aux) {
        puts(Palavra);
        *Palavra = '\0';
    }
    fclose(ArqTxt);
    fclose(ArqAlf);
}

void indiceHash() {
    TipoDicionario hash;
    InicializaHash(hash);
    for(i=0;i<1000;i++){
        if(Indice[i][0]!=0)
            InsereHash(Indice[i],hash);
    }
    ordenaIndice();
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
    int apontador;
    for (i=0;i<1000;i++){
        if(Indice[i][0]!=0){
            apontador=Pesquisa(Indice[i], hash);
            imprimeHash(apontador, hash, ArqTeste);
        }
    }
//    imprimeHash(hash, ArqTeste);
//    ImprimeHash(hash, ArqTeste);
    if (aux) {
        puts(Palavra);
        *Palavra = '\0';
    }
    fclose(ArqTxt);
    fclose(ArqAlf);
}

void imprimeLinha(int nLinha) {
    int aux = 0;
    rewind(ArqTxt);
    while (fgets(Linha, 1250, ArqTxt) != NULL) { //ENQUANTO PEGAR LINHA DO LISTA
        aux++;
        if (aux == nLinha) {
            puts(Linha);
        }
    }
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

void buscaArvore() {
    char palavras[50][50];
    int i = 0, j = 0;
    getchar();
    while (palavras[i][j - 1] != 10) {
        palavras[i][j] = getchar();
        if (palavras[i][j] == 32) {
            palavras[i][j] = 0;
            i++;
            j = 0;
        } else {
            j++;
        }
    }
    palavras[i][j - 1] = 0;
    palavras[i + 1][0] = 0;
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
    TipoRegistro* reg = pesquisaArv(arvore, palavras[0]);
    TipoRepeticao* aux = reg->repeticao;
    int linha;
    if (strlen(palavras[1]) != 0) {
        while (reg != NULL) {
            linha = 0;
            i = 1;
            while (strlen(palavras[i]) != 0) {
                linha = procuraLinhaArv(aux->linha, palavras[i], arvore);
                i++;
            }
            if (linha == 1) {
                imprimeLinha(aux->linha);
            }
            reg = aux->proximo;
        }
    } else {
        while (aux != NULL) {
            imprimeLinha(aux->linha);
            aux = aux->proximo;
        }
    }
    fclose(ArqTxt);
    fclose(ArqAlf);
}

void imprimeLinhasHash(TipoRepeticaoHash* aux1, TipoRepeticaoHash* aux2) {
    TipoRepeticaoHash* item1 = aux1;
    TipoRepeticaoHash* item2 = aux2;
    while (item1 != NULL) {
        while (item2 != NULL) {
            if (item1->linha == item2->linha) {
                rewind(ArqTxt);
                imprimeLinha(item1->linha);
            }
            item2 = item2->proximo;
        }
        item2 = aux2;
        item1 = item1->proximo;
    }
}

void buscaHash() {
    char palavras[50][50];
    int i = 0, j = 0;
    getchar();
    while (palavras[i][j - 1] != 10) {
        palavras[i][j] = getchar();
        if (palavras[i][j] == 32) {
            palavras[i][j] = 0;
            i++;
            j = 0;
        } else {
            j++;
        }
    }
    palavras[i][j - 1] = 0;
    palavras[i + 1][0] = 0;
    TipoDicionario hash;
    InicializaHash(hash);
    for(i=0;i<1000;i++){
        if(Indice[i][0]!=0)
            InsereHash(Indice[i],hash);
    }
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
    int pos = Pesquisa(palavras[0], hash);
    int linha;
    TipoRepeticaoHash* aux = hash[pos]->repeticao;
    if (strlen(palavras[1]) != 0) {
        while (aux != NULL) {
            linha = 0;
            i = 1;
            while (strlen(palavras[i]) != 0) {
                linha = procuraLinhaHash(aux->linha, palavras[i], hash);
                i++;
            }
            if (linha == 1) {
                imprimeLinha(aux->linha);
            }
            aux = aux->proximo;
        }
    } else {
        while (aux != NULL) {
            imprimeLinha(aux->linha);
            aux = aux->proximo;
        }
    }
    fclose(ArqTxt);
    fclose(ArqAlf);
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
    pegaIndice(ArqPalavras);
    ordenaIndice();
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