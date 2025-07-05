#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"

typedef struct stHN {
    char* key;
    struct HashNode* next;
} stHN;

typedef stHN *stHashNode;

typedef struct stHashTable {
    int tamanho;
    stHashNode *buckets;
} stHashTable;


HashTable ht_create(int tamanho) {
    stHashTable *ht = malloc(sizeof(stHashTable));

    ht->tamanho = tamanho;
    ht->buckets = calloc(tamanho, sizeof(stHN));

    return ((stHashTable*)ht);
}


unsigned int hash(char *string, int modulo) {
    unsigned long hash = 5381;
    int c;

    for(int i = 0; string[i] != '\0'; i++) {
        c = string[i];
        hash = ((hash << 5) + hash) + c;  
    }

    return (unsigned int)(hash % modulo);
}
