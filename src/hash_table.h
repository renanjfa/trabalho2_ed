#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef void *HashNode;
typedef void *HashTable;
typedef void *ConteudoHashNode;

HashTable createHashTable(int tamanho);

unsigned int hash(char *string, int modulo);

void insertHashTable(HashTable ht, char* key, ConteudoHashNode content);


#endif