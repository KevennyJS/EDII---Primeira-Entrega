cmake_minimum_required(VERSION 3.17)
project(project C)

set(CMAKE_C_STANDARD 11)

add_executable(project main.c cliente.c cliente.h geracao_particoes.c geracao_particoes.h lista_clientes.c lista_clientes.h nomes.c nomes.h)