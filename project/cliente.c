#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "cliente.h"


void imprime_cliente(TCliente *cliente)
{
    printf("%d, %s\n", cliente->cod_cliente, cliente->nome);
}

TCliente *cliente(int cod, char *nome)
{
    TCliente *cliente = (TCliente *) malloc(sizeof(TCliente));
    if (cliente) memset(cliente, 0, sizeof(TCliente));
    cliente->cod_cliente = cod;
    strcpy(cliente->nome, nome);
    return cliente;
}

void salva_cliente(TCliente *cliente, FILE *out)
{
    fwrite(&cliente->cod_cliente, sizeof(int), 1, out);
    fwrite(cliente->nome, sizeof(char), sizeof(cliente->nome), out);
}

TCliente *le_cliente(FILE *in)
{
    TCliente *cliente = (TCliente *) malloc(sizeof(TCliente));
    if (0 >= fread(&cliente->cod_cliente, sizeof(int), 1, in)) {
        free(cliente);
        return NULL;
    }
    fread(cliente->nome, sizeof(char), sizeof(cliente->nome), in);
    return cliente;
}

int cmp_cliente(TCliente *c1, TCliente *c2)
{
    if (c1 == NULL) {
        return (c2 == NULL);
    }
    if (c1->cod_cliente != c2->cod_cliente) {
        return 0;
    }
    if (strcmp(c1->nome, c2->nome) != 0) {
        return 0;
    }
    return 1;
}

int tamanho_cliente()
{
    return sizeof(int) + // cod_cliente
           sizeof(char) * TAM_NOME; // nome
}
