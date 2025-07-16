#include "stdio.h"
#include "stdlib.h"
#include "lista.h"

typedef struct stCelula {
    Conteudo chave;
    struct stCelula *prox;
} stCelula;  

typedef struct stLista {
    int tam;
    stCelula *inicio;
} stLista;

Lista criaLista() {
    stLista *l = malloc(sizeof(stLista));
    l->inicio = NULL;
    l->tam = 0;
    return ((stLista*)l);
}

void insereLista(Lista l, Conteudo chave) {
    stCelula *new = malloc(sizeof(stCelula));

    if(((stLista*)l)->inicio == NULL) {
        new->chave = chave;
        ((stLista*)l)->inicio = new;
        new->prox = NULL;
    } else {
        new->chave = chave;
        new->prox = ((stLista*)l)->inicio;
        ((stLista*)l)->inicio = new;        
    }

    ((stLista*)l)->tam++;
}

Conteudo getConteudoInicioLista(Lista l) {
    return ((stLista*)l)->inicio->chave;
}

Celula getInicioLista(Lista l) {
    return ((stLista*)l)->inicio;
}

void removeInicioLista(Lista l) {
    if(l == NULL || ((stLista*)l)->inicio == NULL) return;

    Celula aux = ((stLista*)l)->inicio;
    ((stLista*)l)->inicio = ((stLista*)l)->inicio->prox;
    free(aux);
    ((stLista*)l)->tam--;
}

int getTamanhoLista(Lista l) {
    return ((stLista*)l)->tam;
}

void copiaListas(Lista copia, Lista fonte) {
    Celula aux = ((stLista*)fonte)->inicio;
    while(aux != NULL) {
        insereLista(copia, ((stCelula*)aux)->chave);
        aux = ((stCelula*)aux)->prox;
    }
}

void liberaLista(Lista l) {
    if (l == NULL) return;
    
    Celula atual = ((stLista*)l)->inicio;  // Assumindo que Lista tem um campo 'inicio'
    while (atual != NULL) {
        Celula proximo = ((stCelula*)atual)->prox;
        free(atual);  // Libera o próprio nó
        atual = proximo;
    }
    
    free(l);  // Libera a estrutura da lista
}

Celula getProxCelula(Celula p) {
    Celula aux = ((stCelula*)p)->prox;
    if(aux != NULL) return aux;
    else return NULL;
}

Conteudo getConteudoCelula(Celula p) {
    return ((stCelula*)p)->chave;
}

bool searchAndRemoveLista(Lista lista, Conteudo chave) {
    if (lista == NULL || ((stLista*)lista)->inicio == NULL) return false;

    Celula anterior = NULL;
    Celula atual = ((stLista*)lista)->inicio;

    while (atual != NULL) {
        if (((stCelula*)atual)->chave == chave) {
            if (anterior == NULL) {
                // removendo do início
                ((stLista*)lista)->inicio = ((stCelula*)atual)->prox;
            } else {
                ((stCelula*)anterior)->prox = ((stCelula*)atual)->prox;
            }

            // libera a chave e a célula
            free(((stCelula*)atual)->chave);
            free(atual);
            return true;  // remove apenas a primeira ocorrência
        }

        anterior = atual;
        atual = ((stCelula*)atual)->prox;
    }
    return false;
}

void removeCelula(Lista lista, Celula alvo, Celula anterior) {
    if (alvo == NULL) return;

    if (anterior == NULL) {
        // Remover o primeiro elemento da lista
        ((stLista*)lista)->inicio = ((stCelula*)alvo)->prox;
    } else {
        ((stCelula*)anterior)->prox = ((stCelula*)alvo)->prox;
    }

}




