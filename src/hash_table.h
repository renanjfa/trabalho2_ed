#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef void *HashNode;
typedef void *HashTable;
typedef void *ConteudoHashNode;

typedef void (*Callback)(char* key, void* value, void* extra);

void percorrerHashTable(HashTable ht, Callback c, void *extra);

HashTable createHashTable(int tamanho);

void insertHashTable(HashTable tabela, char *key, ConteudoHashNode valor);

ConteudoHashNode buscaHashTable(HashTable tabela, char *key);

int getOrCreateNode(HashTable tabela, char *key, int *proxId);




void destroiHashTable(HashTable tabela);


#endif