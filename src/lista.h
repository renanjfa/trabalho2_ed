#ifndef LISTA_H
#define LISTA_H
#include <stdbool.h>

typedef void *Lista;
typedef void *Celula;
typedef void *Conteudo; 
/*
    LISTA.H
    Módulo responsável pela aplicação abstrata de uma lista, pode ser utilizada de forma genérica em qualquer contexto.
    Inclui operações básicas para operações com a lista.
*/


/// @brief cria uma lista vazia e a retorna
/// @return retorna a lista vazia
Lista criaLista();

/// @brief reazliza a inserção de um elemento na lista
/// @param l Lista l
/// @param n Conteudo n
void insereLista(Lista l, Conteudo n);

/// @brief remove a celula do inicio da lista
/// @param l Lista l
void removeInicioLista(Lista l);

/// @brief retorna o conteudo da celula inicio da lista
/// @param l Lista l
/// @return retorna o conteudo do inicio 
Conteudo getConteudoInicioLista(Lista l);

/// @brief retorna a celula de inicio da lista 
/// @param l Lista l
/// @return celula do inicio da lista 
Celula getInicioLista(Lista l);

/// @brief retorna o tamanho da lista 
/// @param l Lista l
/// @return retorna o tamanho da lista l
int getTamanhoLista(Lista l);

/// @brief copia uma lista fonte para outra 
/// @param copia Lista a ser copiada para
/// @param fonte Lista fonte 
void copiaListas(Lista copia, Lista fonte);

/// @brief liberar memória da lista 
/// @param lista Lista
void liberaLista(Lista lista);

/// @brief retorna o proximo elemento da celula p
/// @param p Celula p
/// @return retorna a proxima celula em relacao e p
Celula getProxCelula(Celula p);

/// @brief retorna o conteudo da celula p 
/// @param p Celula p
/// @return retorna o conteudo da celula p
Conteudo getConteudoCelula(Celula p);


/// @brief percorre a lista e remove o primeiro elemento que e identificado pela sua chave 
/// @param lista Lista 
/// @param chave Conteudo chave
/// @return retorna true se ele foi removido, e false se nao for encontrado 
bool searchAndRemoveLista(Lista lista, Conteudo chave);

/// @brief remove uma celula especifica da lista
/// @param lista Lista
/// @param alvo Celula a ser removida
/// @param anterior Celula anterior a ela
void removeCelula(Lista lista, Celula alvo, Celula anterior);

#endif