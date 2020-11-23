#define NOME_ARQUIVO_ENTRADA "entrada.dat"

#include <stdlib.h>

#include "cliente.h"
#include "lista_clientes.h"
#include "nomes.h"
#include "geracao_particoes.h"

Nomes *nomes = NULL;

ListaClientes *entrada, *oraculo, *saida;
Nomes *p;

void teste01(){
    //Classificacao Interna. Arquivo com 2 registros ja ordenados.
    ListaClientes *entrada, *saida;
    Nomes *p;
    entrada = cria_clientes(2,
                            cliente(1, "Joao"),
                            cliente(5, "Maria"));
    salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
    libera_clientes(entrada);
    nomes = cria_nomes(cria_str("p1.dat"), NULL);

    classificacao_interna(NOME_ARQUIVO_ENTRADA, nomes, 6);

    p = nomes;

    saida = le_clientes(p->nome);
    imprime_clientes(saida); //imprime a partição p1

    libera_clientes(saida);
    p = p->prox;
}

void teste02(){
    //Classificacao Interna. Arquivo com 2 registros desordenados.
    ListaClientes *entrada, *saida;
    Nomes *p;
    entrada = cria_clientes(2,
                            cliente(5, "Maria"),
                            cliente(1, "Joao"));
    salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
    libera_clientes(entrada);
    nomes = cria_nomes(cria_str("p1.dat"), NULL);

    classificacao_interna(NOME_ARQUIVO_ENTRADA, nomes, 6);

    p = nomes;
    saida = le_clientes(p->nome);
    imprime_clientes(saida); //imprime a partição p1

    libera_clientes(saida);
    p = p->prox;
}

void teste03(){
    //Classificacao Interna. Arquivo com 6 registros desordenados.
    ListaClientes *entrada, *saida;
    Nomes *p;
    entrada = cria_clientes(6,
                            cliente(5, "Maria"),
                            cliente(1, "Joao"),
                            cliente(10, "Belle"),
                            cliente(8, "Vanessa"),
                            cliente(7, "Raphael"),
                            cliente(2, "Marcos"));
    salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
    libera_clientes(entrada);
    nomes = cria_nomes(cria_str("p1.dat"), NULL);

    classificacao_interna(NOME_ARQUIVO_ENTRADA, nomes, 6);

    p = nomes;
    saida = le_clientes(p->nome);
    imprime_clientes(saida); //imprime a partição p1

    libera_clientes(saida);
    p = p->prox;
}

void teste04(){
    //Classificacao Interna. Arquivo com 9 registros desordenados.
    ListaClientes *entrada, *saida;
    Nomes *p;
    entrada = cria_clientes(9,
                            cliente(5, "Maria"),
                            cliente(1, "Joao"),
                            cliente(10, "Belle"),
                            cliente(20, "Mariana"),
                            cliente(3, "Raphael"),
                            cliente(87, "Jonas"),
                            cliente(8, "Vanessa"),
                            cliente(7, "Liz"),
                            cliente(2, "Marcos"));
    salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
    libera_clientes(entrada);
    nomes = cria_nomes(cria_str("p1.dat"), cria_nomes(cria_str("p2.dat"), NULL));

    classificacao_interna(NOME_ARQUIVO_ENTRADA, nomes, 6);

    p = nomes;
    saida = le_clientes(p->nome);
    imprime_clientes(saida); //imprime a partição p1

    libera_clientes(saida);
    p = p->prox;

    saida = le_clientes(p->nome);
    imprime_clientes(saida); //imprime a partição p2

    libera_clientes(saida);
    p = p->prox;
}

void teste05(){
    //selecao_com_substituicao. Arquivo com 20 registros desordenados.
    ListaClientes *entrada, *saida;
    Nomes *p;
    entrada = cria_clientes(20,
                            cliente(5, "Maria"),
                            cliente(1, "Joao"),
                            cliente(10, "Belle"),
                            cliente(20, "Mariana"),
                            cliente(3, "Matheus"),
                            cliente(87, "Jonas"),

                            cliente(8, "Vanessa"),
                            cliente(7, "Bruna"),
                            cliente(2, "Raphael"),
                            cliente(0, "Julia"),
                            cliente(9, "Liz"),
                            cliente(81, "Bianca"),

                            cliente(60, "Hugo"),
                            cliente(47, "Martim"),
                            cliente(23, "Clarissa"),
                            cliente(22, "Lucila"),
                            cliente(35, "Marceu"),
                            cliente(48, "Tatiana"),

                            cliente(90, "Melissa"),
                            cliente(85, "Paul"));
    salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
    libera_clientes(entrada);
    nomes = cria_nomes(cria_str("p1.dat"),
                       cria_nomes(cria_str("p2.dat"),
                                  cria_nomes(cria_str("p3.dat"),
                                             cria_nomes(cria_str("p4.dat"), NULL))));

    selecao_com_substituicao(NOME_ARQUIVO_ENTRADA, nomes, 6);

    p = nomes;
    saida = le_clientes(p->nome);
    imprime_clientes(saida); //imprime a partição p1

    libera_clientes(saida);
    p = p->prox;

    saida = le_clientes(p->nome);
    imprime_clientes(saida); //imprime a partição p2

    libera_clientes(saida);
    p = p->prox;

    saida = le_clientes(p->nome);
    imprime_clientes(saida); //imprime a partição p3

    libera_clientes(saida);
    p = p->prox;

    saida = le_clientes(p->nome);
    imprime_clientes(saida); //imprime a partição p4

    libera_clientes(saida);
    p = p->prox;
}
void teste06(){
    //Seleção Natural. Arquivo com 20 registros desordenados.
    ListaClientes *entrada, *saida;
    Nomes *p;
    entrada = cria_clientes(20,
                            cliente(5, "Maria"),
                            cliente(1, "Joao"),
                            cliente(10, "Belle"),
                            cliente(20, "Mariana"),
                            cliente(3, "Matheus"),
                            cliente(87, "Jonas"),

                            cliente(8, "Vanessa"),
                            cliente(7, "Bruna"),
                            cliente(2, "Raphael"),
                            cliente(0, "Julia"),
                            cliente(9, "Liz"),
                            cliente(81, "Bianca"),

                            cliente(60, "Hugo"),
                            cliente(47, "Martim"),
                            cliente(23, "Clarissa"),
                            cliente(22, "Lucila"),
                            cliente(35, "Marceu"),
                            cliente(48, "Tatiana"),

                            cliente(90, "Melissa"),
                            cliente(85, "Paul"));
    salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
    libera_clientes(entrada);
    nomes = cria_nomes(cria_str("p1.dat"),
                       cria_nomes(cria_str("p2.dat"),
                                  cria_nomes(cria_str("p3.dat"),
                                             cria_nomes(cria_str("p4.dat"), NULL))));

    selecao_natural(NOME_ARQUIVO_ENTRADA, nomes, 6,6);

    p = nomes;
    printf("\n=========== P1 \n");
    saida = le_clientes(p->nome);
    imprime_clientes(saida); //imprime a partição p1

    libera_clientes(saida);
    p = p->prox;

    printf("\n=========== P2 \n");
    saida = le_clientes(p->nome);
    imprime_clientes(saida); //imprime a partição p2

    libera_clientes(saida);
    p = p->prox;

    saida = le_clientes(p->nome);
    imprime_clientes(saida); //imprime a partição p3

    libera_clientes(saida);
    p = p->prox;

    saida = le_clientes(p->nome);
    imprime_clientes(saida); //imprime a partição p4

    libera_clientes(saida);
    p = p->prox;
}

void teste07(){
    //Seleção Natural. Arquivo com 20 registros desordenados.
    ListaClientes *entrada, *saida;
    Nomes *p;
    entrada = cria_clientes(54,
                            cliente(29, "Maria"),
                            cliente(14, "Joao"),
                            cliente(76, "Belle"),
                            cliente(75, "Mariana"),
                            cliente(59, "Matheus"),
                            cliente(6, "Jonas"),
                            cliente(7, "Vanessa"),
                            cliente(74, "Bruna"),
                            cliente(48, "Raphael"),
                            cliente(46, "Julia"),
                            cliente(10, "Liz"),
                            cliente(18, "Bianca"),
                            cliente(56, "Hugo"),
                            cliente(20, "Martim"),
                            cliente(26, "Clarissa"),
                            cliente(4, "Lucila"),
                            cliente(21, "Marceu"),
                            cliente(65, "Tatiana"),
                            cliente(22, "Melissa"),
                            cliente(49, "Tatiana"),
                            cliente(11, "Lucila"),
                            cliente(16, "Melissa"),
                            cliente(8, "Liz"),
                            cliente(15, "Joao"),
                            cliente(5, "Melissa"),
                            cliente(19, "Liz"),
                            cliente(50, "Matheus"),
                            cliente(55, "Joao"),
                            cliente(25, "Melissa"),
                            cliente(66, "Liz"),
                            cliente(57, "Melissa"),
                            cliente(77, "Melissa"),
                            cliente(12, "Liz"),
                            cliente(30, "Melissa"),
                            cliente(17, "Liz"),
                            cliente(9, "Melissa"),
                            cliente(54, "Melissa"),
                            cliente(78, "Matheus"),
                            cliente(43, "Liz"),
                            cliente(38, "Melissa"),
                            cliente(51, "Joao"),
                            cliente(32, "Melissa"),
                            cliente(58, "Melissa"),
                            cliente(13, "Liz"),
                            cliente(73, "Melissa"),
                            cliente(79, "Joao"),
                            cliente(27, "Melissa"),
                            cliente(1, "Matheus"),
                            cliente(3, "Melissa"),
                            cliente(60, "Melissa"),
                            cliente(36, "Joao"),
                            cliente(47, "Marcos"),
                            cliente(31, "Matheus"),
                            cliente(80, "Paul"));
    salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
    libera_clientes(entrada);
    nomes = cria_nomes(cria_str("p1.dat"),
                       cria_nomes(cria_str("p2.dat"),
                                  cria_nomes(cria_str("p3.dat"),
                                             cria_nomes(cria_str("p4.dat"),
                                                        cria_nomes(cria_str("p5.dat"), NULL)))));

    selecao_natural(NOME_ARQUIVO_ENTRADA, nomes, 6,6);

    p = nomes;
    printf("\n=========== P1 \n");
    saida = le_clientes(p->nome);
    imprime_clientes(saida); //imprime a partição p1

    libera_clientes(saida);
    p = p->prox;

    printf("\n=========== P2 \n");
    saida = le_clientes(p->nome);
    imprime_clientes(saida); //imprime a partição p2

    libera_clientes(saida);
    p = p->prox;

    printf("\n=========== P3 \n");
    saida = le_clientes(p->nome);
    imprime_clientes(saida); //imprime a partição p3

    libera_clientes(saida);
    p = p->prox;

    printf("\n=========== P4 \n");
    saida = le_clientes(p->nome);
    imprime_clientes(saida); //imprime a partição p4

    libera_clientes(saida);
    p = p->prox;

    printf("\n=========== P5 \n");
    saida = le_clientes(p->nome);
    imprime_clientes(saida); //imprime a partição p5

    libera_clientes(saida);
    p = p->prox;
}

int main(void) {
    //Classificacao Interna. Arquivo com 2 registros ja ordenados.
    printf("=======================\n");
    printf("Execução do teste 01 \n");
    printf("=======================\n");
    //teste01();
    printf("\n");

    //Classificacao Interna. Arquivo com 2 registros desordenados.
    printf("=======================\n");
    printf("Execução do teste 02 \n");
    printf("=======================\n");
    //teste02();
    printf("\n");

    //Classificacao Interna. Arquivo com 6 registros desordenados.
    printf("=======================\n");
    printf("Execução do teste 03 \n");
    printf("=======================\n");
    //teste03();
    printf("\n");

    //Classificacao Interna. Arquivo com 9 registros desordenados.
    printf("=======================\n");
    printf("Execução do teste 04 \n");
    printf("=======================\n");
    //teste04();
    printf("\n");

    //Por substituição. Arquivo com 20 registros desordenados.
    printf("=======================\n");
    printf("Execução do teste 05 \n");
    printf("=======================\n");
    //teste05();
    printf("\n");

    //Seleção Natural. Arquivo com 20 registros desordenados.
    printf("=======================\n");
    printf("Execução do teste 06 \n");
    printf("=======================\n");
    teste06();
    printf("\n");

    //Seleção Natural. Arquivo com 54 registros desordenados.
    printf("=======================\n");
    printf("Execução do teste 07 \n");
    printf("=======================\n");
    teste07();
    printf("\n");

    return 0;
}
