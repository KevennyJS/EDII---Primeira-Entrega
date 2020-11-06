#ifndef PROJECT_CLIENTE_H
#define PROJECT_CLIENTE_H

#include <stdio.h>

#define TAM_NOME 100

typedef struct Cliente {
    int cod_cliente;
    char nome[TAM_NOME];
} TCliente;

// Imprime cliente
void imprime_cliente(TCliente *cliente);

// Cria cliente. Lembrar de usar free(cliente)
TCliente *cliente(int cod, char *nome);

// Salva cliente no arquivo out, na posicao atual do cursor
void salva_cliente(TCliente *cliente, FILE *out);

// Le um cliente do arquivo in na posicao atual do cursor
// Retorna um ponteiro para cliente lido do arquivo
TCliente *le_cliente(FILE *in);

// Compara dois clientes
// Retorna 1 se os valores dos atributos de ambos forem iguais
// e 0 caso contrario
int cmp_cliente(TCliente *c1, TCliente *c2);

// Retorna tamanho do cliente em bytes
int tamanho_cliente();

#endif //PROJECT_CLIENTE_H
