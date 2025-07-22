#ifndef LEITURA_CIDADE_H
#define LEITURA_CIDADE_H

#include <stdlib.h>
#include <stdio.h>

#include "hash_table.h"

/*
    LEITURA_CIDADE.H
    Módulo responsável pela leitura de um arquivo .geo que descreve o comportamento das quadras de uma cidade.
*/

/*
    Realiza a leitura completa do arquivo .geo responsável por descrever as quadras de uma cidade.
    Retorna uma Tabela Hash associando os nomes das quadras com suas informações.
*/
HashTable LeituraCompletaCidade(FILE **svg1, FILE *arqcidade, HashTable ht);


/*
    Processa o arquivo .geo por seu path, preparando-o para sua leitura.
    Retorna uma Tabela Hash associando os nomes das quadras com suas informações.
*/
HashTable ProcessaCidade(const char *pathcidade, const char *dirsaida, const char *nomecidade);


#endif
