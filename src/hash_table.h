#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>

typedef void *HashNode;
typedef void *HashTable;
typedef void *ConteudoHashNode;
/*
    HASH_TABLE.H
    Módulo responsável por gerenciar uma estrutura de dados de uma TABELA HASH abstrata, podendo ser armazenado qualquer tipo de informação.
    Inclui operações básicas para operações com a estrutura.
*/

typedef void (*Callback)(char* key, void* value, void* extra);

void percorrerHashTable(HashTable ht, Callback c, void *extra);

HashTable createHashTable(int tamanho);

void insertHashTable(HashTable tabela, char *key, ConteudoHashNode valor);

ConteudoHashNode buscaHashTable(HashTable tabela, char *key);

int getOrCreateNode(HashTable tabela, char *key, int *proxId);

void destroiHashTable(HashTable tabela);


#endif