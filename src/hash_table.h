#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef void *HashNode;
typedef void *HashTable;
typedef void *ConteudoHashNode;

HashTable createHashTable(int tamanho);

void insertHashTable(HashTable tabela, char *key, ConteudoHashNode valor);

ConteudoHashNode buscaHashTable(HashTable tabela, char *key);

void destroiHashTable(HashTable tabela, void (*liberaValor)(ConteudoHashNode));

int getOrCreateNode(HashTable tabela, char *key, int *proxId);

#endif