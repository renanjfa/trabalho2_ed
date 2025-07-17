#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

typedef struct stHN {
    char* key;
    ConteudoHashNode value;
    struct stHN* proximo;
} stHN;

typedef stHN *stHashNode;

typedef struct stHashTable {
    int tamanho;
    stHashNode *buckets;
} stHashTable;



unsigned int hash(const char *str, int modulo) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return (unsigned int)(hash % modulo);
}

HashTable createHashTable(int tamanho) {
    stHashTable *ht = malloc(sizeof(stHashTable));

    ht->tamanho = tamanho;
    ht->buckets = calloc(tamanho, sizeof(stHashNode));

    return (HashTable)ht;
}

void insertHashTable(HashTable tabela, char *key, ConteudoHashNode valor) {
    stHashTable *ht = (stHashTable*)tabela;

    int idx = hash(key, ht->tamanho);

    stHashNode novo = malloc(sizeof(stHN));
    novo->key = strdup(key);
    novo->value = valor;
    novo->proximo = ht->buckets[idx];
    ht->buckets[idx] = novo;
}

ConteudoHashNode buscaHashTable(HashTable tabela, char *key) {
    stHashTable *ht = (stHashTable *)tabela;

    int idx = hash(key, ht->tamanho);

    stHashNode atual = ht->buckets[idx];
    while (atual) {
        if (strcmp(atual->key, key) == 0)
            return atual->value;
        atual = atual->proximo;
    }
    return NULL;
}

void destroiHashTable(HashTable tabela, void (*liberaValor)(ConteudoHashNode)) {
    stHashTable *ht = (stHashTable *)tabela;

    for (int i = 0; i < ht->tamanho; i++) {
        stHashNode atual = ht->buckets[i];
        while (atual) {
            stHashNode prox = atual->proximo;
            free(atual->key);
            if (liberaValor)
                liberaValor(atual->value);
            free(atual);
            atual = prox;
        }
    }
    free(ht->buckets);
    free(ht);
}


int getOrCreateNode(HashTable tabela, char *key, int *proxId) {
    ConteudoHashNode resultado = buscaHashTable(tabela, key);

    if (resultado != NULL)
        return (int)(long)resultado;

    int novo = (*proxId)++;
    insertHashTable(tabela, key, (void *)(long)novo);
    return novo;
}

void percorrerHashTable(HashTable ht, Callback c, void *extra) {
    for (int i = 0; i < ((stHashTable*)ht)->tamanho; i++) {
        HashNode* node = ((stHashTable*)ht)->buckets[i];
        while (node != NULL) {
            c(((stHN*)node)->key, ((stHN*)node)->value, extra);
            node = ((stHN*)node)->proximo;
        }
    }
}


// int main() {
//     // Criar tabela com tamanho inicial adequado
//     HashTable tabelaEnderecos = criaHashTable(20);

//     int proxId = 0; // contador de Node (índices)

//     // Endereços de exemplo
//     const char *enderecos[] = {
//         "Rua A, 100",
//         "Rua B, 200",
//         "Av. Central, 300",
//         "Rua A, 100",          // duplicado proposital
//         "Rua C, 400",
//         "Av. Central, 300"     // duplicado proposital
//     };

//     int total = sizeof(enderecos) / sizeof(enderecos[0]);

//     // Inserção segura
//     for (int i = 0; i < total; i++) {
//         Node id = getOrCreateNode(tabelaEnderecos, (char *)enderecos[i], &proxId);
//         printf("Endereço: %-20s → Node (índice): %d\n", enderecos[i], id);
//     }

//     // Liberação da hash table
//     destroiHash(tabelaEnderecos, NULL); // valores são inteiros simples, não precisam de free

//     return 0;
// }


// int *valor = malloc(sizeof(int));
// *valor = node;
// insertHashTable(tabela, nome, valor);

// // Recuperar:
// int *ptr = (int *)buscaHash(tabela, nome);
// Node node = *ptr;
