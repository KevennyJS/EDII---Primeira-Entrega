#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include "geracao_particoes.h"
#include "nomes.h"
#include "cliente.h"


int getMinIndex(int M, TCliente* *memory, char *frozen);
void initFronzenArray(char *array, int M);
int fullXFrozenArray(char *array, int m);

void classificacao_interna(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M) {

    int fim = 0; //variável de controle para saber se arquivo de entrada terminou
    FILE *arq; //declara ponteiro para arquivo

    //abre arquivo para leitura
    if ((arq = fopen(nome_arquivo_entrada, "rb")) == NULL) {
        printf("Erro ao abrir arquivo de entrada\n");
    } else {

        //le primeiro cliente
        TCliente *cin = le_cliente(arq);

        while (!(fim)) {
            //le o arquivo e coloca no vetor
            TCliente *v[M];

            int i = 0;
            while (!feof(arq) && i < M) {
                v[i] = cin;
                cin = le_cliente(arq);
                i++;
            }

            //ajusta tamanho M caso arquivo de entrada tenha terminado antes do vetor
            if (i != M) {
                M = i;
            }

            //faz ordenacao
            for (int j = 1; j < M; j++) {
                TCliente *c = v[j];
                i = j - 1;
                while ((i >= 0) && (v[i]->cod_cliente > c->cod_cliente)) {
                    v[i + 1] = v[i];
                    i = i - 1;
                }
                v[i + 1] = c;
            }

            //cria arquivo de particao e faz gravacao
            char *nome_particao = nome_arquivos_saida->nome;
            nome_arquivos_saida = nome_arquivos_saida->prox;

            FILE *p;
            if ((p = fopen(nome_particao, "wb")) == NULL) {
                printf("Erro criar arquivo de saida\n");
            } else {
                for (int i = 0; i < M; i++) {
                    salva_cliente(v[i], p);
                }
                fclose(p);
            }
            if (feof(arq)) {
                fim = 1;
            }
        }
    }
}

void selecao_com_substituicao(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M) {

    int fim = 0; //variável de controle para saber se arquivo de entrada terminou
    FILE *arq; //declara ponteiro para arquivo de entrada

    //abre arquivo para leitura
    if ((arq = fopen(nome_arquivo_entrada, "rb")) == NULL) {
        printf("Erro ao abrir arquivo de entrada\n");
        exit(1);
    }

    FILE *p; // arquivo de partições

    TCliente *memory[M]; // array em memoria
    char frozen[M]; // array que representa os congelados
    initFronzenArray(frozen,M);

    // le os M primeiros registros
    int z = 0;
    while (!feof(arq) && z < M) {
        memory[z] = le_cliente(arq);
        z++;
    }

    while (fim != 1) { //enquanto não for o fim do arquivo de entrada e fim do algoritimo

        // abre arquivo de partição
        char *nome_particao = nome_arquivos_saida->nome; // pega o nome da primeira partição
        if ((p = fopen(nome_particao, "wb")) == NULL) {
            printf("Erro criar arquivo de saida\n");
            exit(1);
        }

        while(fullXFrozenArray(frozen,M) != 1 || !feof(arq)){ //  enquanto não tiver todoo o array congelado ou for o fim do arquivo
            // pega o index do menor codigo dentro da memory
            int minIndex = getMinIndex(M, memory,frozen);

            //salva na partição
            printf("%i:%s",memory[minIndex]->cod_cliente,memory[minIndex]->nome);
            TCliente *minCliente = memory[minIndex];
            salva_cliente(minCliente, p);

            // pega o proximo R
            memory[minIndex] = le_cliente(arq);

            if(memory[minIndex]->cod_cliente < minCliente->cod_cliente){
                frozen[minIndex] = 'X';
            }
        }

        fclose(p); // fecha partição
        initFronzenArray(frozen,M);// descongela

        if (feof(arq)) {
            fim = 1;
            break;
        }

        nome_arquivos_saida = nome_arquivos_saida->prox; // pega o proximo nome de partição e coloca como atual
    }

}

void initFronzenArray(char *array, int M){
    for(int i = 0; i< M; i++){
        array[i] = '0';
    }
}

int fullXFrozenArray(char *array, int m){
    int isfull = 1;
    for(int cont = 0 ; cont < m ; cont++){
        if(array[cont] == 'X') isfull = 0;
    }
    return isfull;
}

int getMinIndex(int M, TCliente* *memory, char *frozen) {
    int minValue, minIndex ;

    for(int k=0,j=1; k < M-1;){
        if (frozen[k] == 'X'){
            k++;j++;
            continue;
        }
        if(memory[k]->cod_cliente < memory[minIndex]->cod_cliente){
            minIndex = k;
            minValue = memory[k]->cod_cliente;
        }
        k++;j++;
    }
    return minIndex;
}

void selecao_natural(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M, int n) {
    //TODO: Inserir aqui o codigo do algoritmo de geracao de particoes
}

