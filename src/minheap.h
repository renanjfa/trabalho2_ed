#ifndef MINHEAP_H
#define MINHEAP_H

#include <stdbool.h>

typedef void *MinHeap;

MinHeap createMinHeap(int capacidade);

void insertMinHeapAux(MinHeap h, int index);

void insertMinHeap(MinHeap h, int v, double dist);

void minHeapify(MinHeap h, int index);

int extractMinV(MinHeap h);

double extractMinDist(MinHeap h);

bool isMinHeapEmpty(MinHeap h);

void atualizaMinHeap(MinHeap h, int v, double novaDist);

bool estaNaHeap(MinHeap h, int v);



#endif