#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "geracao_particoes.h"
#include "nomes.h"
#include "cliente.h"
#include "string.h"


int getMinIndexWithFrozen(int M, TCliente* *memory, char *frozen);
int getMinIndex(int M, TCliente* *memory);
void initFronzenArray(char *array, int M);
int fullXFrozenArray(char *array, int m);
int estaVazio(TCliente **vetor, int n);
int reservatorioTransferToMemory(FILE *reservatorio,TCliente **memory,int indexReservatorio, int M);
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
    }else{
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

        while (fim == 0) { //enquanto não for o fim do arquivo de entrada e fim do algoritimo
            // abre arquivo de partição
            char *nome_particao = nome_arquivos_saida->nome; // pega o nome da primeira partição
            if ((p = fopen(nome_particao, "wb")) == NULL) {
                printf("Erro criar arquivo de saida2\n");
            }else{
                while((fullXFrozenArray(frozen,M) != 1) ){ //  enquanto não tiver todoo o array congelado ou for o fim do arquivo
                    // pega o index do menor codigo dentro da memory
                    int minIndex = getMinIndexWithFrozen(M, memory, frozen);

                    //salva na partição
                    TCliente *minCliente = memory[minIndex];  //minCliente fica como ultimo cliente salvo na partição
                    salva_cliente(minCliente, p);

                    // pega o proximo R
                    if(fim == 0){// verifica se está no final do arquivo de entrada se tiver ele não deixa ficar carregando novos clientes
                        TCliente *minClienteAux = le_cliente(arq);
                        if(minClienteAux != NULL){
                            memory[minIndex] = minClienteAux;
                        }else{// quando o cliente carregado for NULL é pq ja esta no final do arquivo entao ele gela a posição
                            fim = 1;
                            frozen[minIndex] = 'X';
                        }
                    }else{
                        frozen[minIndex] = 'X';
                    }

                    if (frozen[minIndex] != 'X'){ // aqui serve para não deixar quebra quando  na memory ja tiver clientes com NULL
                        if(memory[minIndex]->cod_cliente < minCliente->cod_cliente){
                            frozen[minIndex] = 'X';
                        }
                    }
                }

                fclose(p); // fecha partição
                initFronzenArray(frozen,M);// descongela

                nome_arquivos_saida = nome_arquivos_saida->prox; // pega o proximo nome de partição e coloca como atual
            }
        }

    }

}

void initFronzenArray(char *array, int M){
    for(int i = 0; i< M; i++){
        array[i] = '0';
    }
}

int fullXFrozenArray(char *array, int m){
    int countX = 0;
    for(int i = 0 ; i < m ; i++){
        if(array[i]=='X') {countX++;}
    }
    return countX == m ? 1:0;
}

int getMinIndexWithFrozen(int M, TCliente* *memory, char *frozen) {
    int minIndex , first=0;

    for(int k=0; k < M;){
        if (frozen[k] == 'X'){
            k++;
            continue;
        }
        if(first==0){
            minIndex=k;
            first++;
        }

        if(memory[k]->cod_cliente < memory[minIndex]->cod_cliente){
            minIndex = k;
        }
        k++;
    }
    return minIndex;
}

void selecao_natural(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M, int n) {

    int fim = 0,fimBuscaR=0,indexReservatorio=0; //variável de controle para saber se arquivo de entrada terminou //fim buscaR é a variavel que determina que os proximos R serao NULOS
    FILE *arq; //declara ponteiro para arquivo de entrada
    FILE *reservatorio; //declara ponteiro para arquivo do reservatorio

    //abre arquivo para leitura
    arq = fopen(nome_arquivo_entrada, "rb");
    reservatorio = fopen("reservatorio.dat", "wb+");
    if ( (arq == NULL) || (reservatorio == NULL)) {
        printf("Erro ao abrir arquivo de entrada ou criar arquivo do reservatorio\n");
    }else{
        FILE *p; // arquivo de partições

        TCliente *memory[M]; // array em memoria

        // le os M primeiros registros
        int z = 0;
        while (!feof(arq) && z < M) {
            memory[z] = le_cliente(arq);
            z++;
        }

        while (fimBuscaR < 2) { //enquanto não for o fim do arquivo de entrada e fim do algoritimo
            if(fimBuscaR == 1){
                fimBuscaR++;
            }
            // abre arquivo de partição
            char *nome_particao = nome_arquivos_saida->nome; // pega o nome da primeira partição
            if ((p = fopen(nome_particao, "wb")) == NULL) {
                printf("Erro criar arquivo de saida2\n");
            }else{
                //printf("\n== P>%s==\n", nome_particao);
                int fimParticao=0;
                while((indexReservatorio < n) && (fimParticao == 0)){ //  enquanto não tiver todoo o array congelado ou for o fim do arquivo
                    if(estaVazio(memory,M) == 1){
                        fimParticao = 1;
                        break;
                    }
                    // pega o index do menor codigo dentro da memory
                    int minIndex = getMinIndex(M, memory);

                    //salva na partição
                    //printf("%i:%s\n",memory[minIndex]->cod_cliente,memory[minIndex]->nome);
                    //printf("\n>>>>>%i::%i", minIndex, countVerifyNullMemory);
                    TCliente *minCliente = memory[minIndex];  //minCliente fica como ultimo cliente salvo na partição
                    salva_cliente(minCliente, p);

                    if(fimBuscaR != 0){
                        memory[minIndex] = NULL;
                    }

                    // pega o proximo R
                    if(fimBuscaR==0){
                        TCliente *minClienteNewR;
                        do {
                            minClienteNewR = le_cliente(arq);
                            if (minClienteNewR != NULL) {
                                if (minClienteNewR->cod_cliente < minCliente->cod_cliente) {
                                    salva_cliente(minClienteNewR, reservatorio);
                                    indexReservatorio++; // indica quantos elementos tem no reservatorio
                                } else {
                                    memory[minIndex] = minClienteNewR;
                                }
                            }else {
                                fimBuscaR = 1;
                                memory[minIndex] = NULL;
                                break;
                            }
                        } while (minClienteNewR->cod_cliente < minCliente->cod_cliente);
                    }

                }

                //organizarArray(memory,M,NULL);
                //todo: por os registros do reservatorio na memoria
                indexReservatorio = reservatorioTransferToMemory(reservatorio,memory,indexReservatorio,M);
                fclose(p); // fecha partição
                nome_arquivos_saida = nome_arquivos_saida->prox; // pega o proximo nome de partição e coloca como atual
            }
        }

    }

}
int estaVazio(TCliente **vetor, int n) {
    for (int i = 0; i < n; i++) {
        if(vetor[i] != NULL) return 0;
    }
    return 1;
}

int reservatorioTransferToMemory(FILE *reservatorio,TCliente **memory,int indexReservatorio, int M){
    rewind(reservatorio);
    TCliente *aux = NULL;
    int i = 0;
    while ((aux = le_cliente(reservatorio)) != NULL && i<M){
        memory[i] = aux;
        indexReservatorio--;
        i++;
    }
    rewind(reservatorio);
    return indexReservatorio;
}

int getMinIndex(int M, TCliente* *memory){
    int minIndex , first=0;

    for(int k=0; k < M;){
        if (memory[k] == NULL){
            k++;
            continue;
        }
        if(first==0){
            minIndex=k;
            first++;
        }

        if(memory[k]->cod_cliente < memory[minIndex]->cod_cliente){
            minIndex = k;
        }
        k++;
    }
    return minIndex;
}


