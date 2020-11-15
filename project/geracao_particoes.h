#ifndef PROJECT_GERACAO_PARTICOES_H
#define PROJECT_GERACAO_PARTICOES_H

#include "nomes.h"

// Executa o algoritmo de geracao de particoes por Classificacao Interna
// nome_arquivo_entrada: nome do arquivo de entrada
// nome_arquivo_saida: lista encadeada com nomes de arquivos de saida
// M: tamanho do array em memoria para manipulacao dos registros
void classificacao_interna(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M);

// Executa o algoritmo de geracao de particoes por Selecao com Substituicao
// nome_arquivo_entrada: nome do arquivo de entrada
// nome_arquivo_saida: lista encadeada com nomes de arquivos de saida
// M: tamanho do array em memoria para manipulacao dos registros
_Noreturn void selecao_com_substituicao(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M);

// Executa o algoritmo de geracao de particoes por Selecao Natural
// nome_arquivo_entrada: nome do arquivo de entrada
// nome_arquivo_saida: lista encadeada com nomes de arquivos de saida
// M: tamanho do array em memoria para manipulacao dos registros
// n: tamanho do reservatorio
void selecao_natural(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M, int n);

#endif //PROJECT_GERACAO_PARTICOES_H
