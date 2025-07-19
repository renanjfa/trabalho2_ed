#include <stdio.h>
#include <stdlib.h>

#include "minheap.h"

typedef struct ItemHeap {
    int v;
    double dist;
} ItemHeap;

typedef struct stHeap {
    ItemHeap *arr;
    int size;
    int capacidade;
    int *pos;
} stHeap;


MinHeap createMinHeap(int capacidade) {
    stHeap *h = malloc(sizeof(stHeap));
    if(!h) return NULL;

    h->size = 0;
    h->capacidade = capacidade;

    h->arr = malloc(capacidade * sizeof(ItemHeap));
    h->pos = malloc(capacidade * sizeof(int));

    for (int i = 0; i < capacidade; i++)
        h->pos[i] = -1;

    return ((stHeap*)h);
}


void swapHeap(ItemHeap *a, ItemHeap *b) {
    ItemHeap temp = *a;
    *a = *b;
    *b = temp;
}


void insertMinHeapAux(MinHeap h, int index) {
    int pai = (index - 1) / 2;

    if(index > 0 && ((stHeap*)h)->arr[pai].dist > ((stHeap*)h)->arr[index].dist) {

        ((stHeap*)h)->pos[((stHeap*)h)->arr[pai].v] = index;
        ((stHeap*)h)->pos[((stHeap*)h)->arr[index].v] = pai;

        swapHeap(&((stHeap*)h)->arr[pai], &((stHeap*)h)->arr[index]);

        insertMinHeapAux(h, pai);
    }
}

void insertMinHeap(MinHeap h, int v, double dist) {
    if(((stHeap*)h)->size < ((stHeap*)h)->capacidade) {

        ((stHeap*)h)->arr[ ((stHeap*)h)->size ].v = v;
        ((stHeap*)h)->arr[ ((stHeap*)h)->size ].dist = dist;
        ((stHeap*)h)->pos[v] = ((stHeap*)h)->size;

        ((stHeap*)h)->size++;
        insertMinHeapAux(h, ((stHeap*)h)->size);
    }
}


void minHeapify(MinHeap h, int index) {

    int esq = index * 2 + 1;
    int dir = index * 2 + 2;
    int min = index;

    if(esq < ((stHeap*)h)->size && ((stHeap*)h)->arr[esq].dist < ((stHeap*)h)->arr[index].dist)
        min = esq;
    if(dir < ((stHeap*)h)->size && ((stHeap*)h)->arr[dir].dist < ((stHeap*)h)->arr[index].dist)
        min = dir;

    if(min != index) {

        ((stHeap*)h)->pos[((stHeap*)h)->arr[min].v] = index;
        ((stHeap*)h)->pos[((stHeap*)h)->arr[index].v] = min;

        swapHeap(&((stHeap*)h)->arr[index], &((stHeap*)h)->arr[min]);

        minHeapify(h, min);
    }
}


int extractMinV(MinHeap h) {

    if(((stHeap*)h)->size == 0) {
        printf("Heap id empty.\n");
        return;
    }

    ItemHeap root = ((stHeap*)h)->arr[0];
    ItemHeap last = ((stHeap*)h)->arr[((stHeap*)h)->size - 1];

    ((stHeap*)h)->arr[0] = last;
    ((stHeap*)h)->pos[last.v] = 0;
    ((stHeap*)h)->pos[root.v] = -1;

    ((stHeap*)h)->size--;
    minHeapify(h, 0);

    return root.v;
}

double extractMinDist(MinHeap h) {

    if(((stHeap*)h)->size == 0) {
        printf("Heap id empty.\n");
        return;
    }

    ItemHeap root = ((stHeap*)h)->arr[0];
    ItemHeap last = ((stHeap*)h)->arr[((stHeap*)h)->size - 1];

    ((stHeap*)h)->arr[0] = last;
    ((stHeap*)h)->pos[last.v] = 0;
    ((stHeap*)h)->pos[root.v] = -1;

    ((stHeap*)h)->size--;

    minHeapify(h, 0);
    return root.dist;
}

bool isMinHeapEmpty(MinHeap h) {
    if(((stHeap*)h)->size <= 0)
        return true;
    else    
        return false;
}

void atualizaMinHeap(MinHeap h, int v, double novaDist) {
    stHeap *heap = (stHeap*)h;
    int i = heap->pos[v];

    if (i < 0 || i >= heap->size) return;

    heap->arr[i].dist = novaDist;

    // Sobe o elemento se necessário
    while (i > 0 && heap->arr[i].dist < heap->arr[(i - 1) / 2].dist) {
        int pai = (i - 1) / 2;

        // atualiza pos[]
        heap->pos[heap->arr[i].v] = pai;
        heap->pos[heap->arr[pai].v] = i;

        swapHeap(&heap->arr[i], &heap->arr[pai]);
        i = pai;
    }
}


bool estaNaHeap(MinHeap h, int v) {
    stHeap *heap = (stHeap*) h;
    return heap->pos[v] >= 0 && heap->pos[v] < heap->size;
}