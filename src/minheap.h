#ifndef MINHEAP_H
#define MINHEAP_H

#include <stdbool.h>
#include <math.h>


typedef void *MinHeap;
/*
    MINHEAP.H
    Módulo responsável por gerenciar uma estrutura de dados de FILA DE PRIORIDADE MÍNIMA.
    Inclui operações básicas para operação com a estrutura.
*/


/// @brief Cria e retorna uma Heap mínima com capacidade fornecida.
/// @param capacidade Capacidade de armazenamento da Heap.
/// @return Retorna a estrutura MinHeap.
MinHeap createMinHeap(int capacidade);

/// @brief Insere um novo elemento na Heap mínima.
/// @param h Ponteiro para a Heap mínima.
/// @param v Índice do vértice a ser inserido.
/// @param dist Distância associada ao vértice.
void insertMinHeap(MinHeap h, int v, double dist);

/// @brief Restaura a propriedade de Heap mínima a partir de um índice.
/// @param h Ponteiro para a Heap mínima.
/// @param index Índice a partir do qual a ordenação será ajustada.
void minHeapify(MinHeap h, int index);

/// @brief Remove e retorna o vértice com a menor distância da Heap.
/// @param h Ponteiro para a Heap mínima.
/// @return Índice do vértice com a menor distância.
int extractMinV(MinHeap h);

/// @brief Remove e retorna a menor distância da Heap.
/// @param h Ponteiro para a Heap mínima.
/// @return Valor da menor distância presente na Heap.
double extractMinDist(MinHeap h);

/// @brief Verifica se a Heap mínima está vazia.
/// @param h Ponteiro para a Heap mínima.
/// @return Retorna true se estiver vazia, false caso contrário.
bool isMinHeapEmpty(MinHeap h);

/// @brief Atualiza a distância de um vértice na Heap mínima.
/// @param h Ponteiro para a Heap mínima.
/// @param v Índice do vértice a ser atualizado.
/// @param novaDist Novo valor de distância.
void atualizaMinHeap(MinHeap h, int v, double novaDist);

/// @brief Verifica se um vértice está presente na Heap mínima.
/// @param h Ponteiro para a Heap mínima.
/// @param v Índice do vértice a ser verificado.
/// @return Retorna true se o vértice estiver na Heap, false caso contrário.
bool estaNaHeap(MinHeap h, int v);



#endif