#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <stdio.h>
#include <stdlib.h>


#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "texto.h"
#include "smutreap.h"

typedef void *BoundingBox;
/*
    Arquivo .h relacionado ao bounding box (forma de um retangulo que engloba o retangulo maximo de cada forma padrao
    texto, linha, circulo, retangulo), responsavel por todas as operacoes relacionadas aos bounding boxes de todas 
    as formas como uniao de bbs das subarvores, verificacao de forma interior a outra e etc.
*/


/// @brief faz a união dos bounding box do node pai e de ambos os seus filhos, e atualiza este novo bounding box ao pai
/// @param bbmain bounding box da subarvore do pai que será alterado com o novo bounding box
/// @param bbinfo bounding box da informacao armazenada em um node da SmuTreap
/// @param bbesq bounding box da subarvore do filho esquerdo
/// @param bbdir bounding box da subarvre do filho direito
void uniaoBBAmbosFilhos(BoundingBox bbmain, BoundingBox bbinfo, BoundingBox bbesq, BoundingBox bbdir);


/// @brief faz a uniao do bounding box do node pai que não apresenta filhos, a atualiza este novo bounding box ao pai
/// @param bbmain bounding box da subarvore do pai que será alterado com o novo bounding box
/// @param bbinfo bounding box da informacao relacionada ao pai armazenada em um node da SmuTreap
void uniaoBBSemFilhos(BoundingBox bbmain, BoundingBox bbinfo);


/// @brief faz a união dos bounding box do node pai e de seu filho esquerdo, e atualiza este novo bounding box ao pai
/// @param bbmain bounding box da subarvore do pai que será alterado com o novo bounding box
/// @param bbesq bounding box da subarvore do filho esquerdo
void uniaoBBEsquerda(BoundingBox bbmain, BoundingBox bbesq);


/// @brief faz a união dos bounding box do node pai e de seu filho direito, e atualiza este novo bounding box ao pai
/// @param bbmain bounding box da subarvore do pai que será alterado com o novo bounding box
/// @param bbdir bounding box da subarvore do filho direito
void uniaoBBDireita(BoundingBox bbmain, BoundingBox bbdir);


/// @brief cria a forma denotada de bounding box, retangulo minimo que engloba as formas (texto, linha, circulo, retangulo)
/// @param x ancora x do bounding box
/// @param y ancora y do bounding box
/// @param w largura do bounding box
/// @param h altura do bounding box
/// @return retorna a forma bounding box
BoundingBox criarBB(double x, double y, double w, double h);


/// @brief calculo dos elementos compositores de um bounding box de um retangulo. Os valores sao passados e alterados por referencia. 
/// @param r retangulo r como forma
/// @param x ancora x do futuro bounding box
/// @param y ancora y do futuro bounding box
/// @param w largura do futuro bounding box
/// @param h altura do futuro bounding box
void calculaParametroBBRetangulo(Retangulo r, double *x, double *y, double *w, double *h);


/// @brief calculo dos elementos compositores de um bounding box de um circulo. Os valores sao passados e alterados por referencia. 
/// @param c circulo c como forma
/// @param x ancora x do futuro bounding box
/// @param y ancora y do futuro bounding box
/// @param w largura do futuro bounding box
/// @param h altura do futuro bounding box
void calculaParametroBBCirculo(Circulo c, double *x, double *y, double *w, double *h);


/// @brief calculo dos elementos compositores de um bounding box de uma linha. Os valores sao passados e alterados por referencia. 
/// @param l linha l como forma
/// @param x ancora x do futuro bounding box
/// @param y ancora y do futuro bounding box
/// @param w largura do futuro bounding box
/// @param h altura do futuro bounding box
void calculaParametroBBLinha(Linha l, double *x, double *y, double *w, double *h);


/// @brief calculo dos elementos compositores de um bounding box de um texto. Os valores sao passados e alterados por referencia.
/// @param t texto t como forma
/// @param x ancora x do futuro bounding box
/// @param y ancora y do futuro bounding box
/// @param w largura do futuro bounding box
/// @param h altura do futuro bounding box
void calculaParametroBBTexto(Texto t, double *x, double *y, double *w, double *h);


/// @brief funcao get da ancora x do bounding box
/// @param bb bounding box bb como forma
/// @return retorna a ancora x do bounding box
double getXBoundingBox(BoundingBox bb);


/// @brief funcao get da ancora y do bounding box
/// @param bb bounding box bb como forma
/// @return retorna a ancora y do bounding box
double getYBoundingBox(BoundingBox bb);


/// @brief funcao get da largura do bounding box
/// @param bb bounding box bb como forma
/// @return retorna a largura w do bounding box
double getWBoundingBox(BoundingBox bb);


/// @brief funcao get da altura do bounding box 
/// @param bb bounding box bb como forma
/// @return retorna a altura h do bounding box 
double getHBoundingBox(BoundingBox bb);


/// @brief verifica se um bounding box (retangulo) é interior a uma regiao/bounding box delimitada por x1, y1, x2, y2
/// @param n node n da SmuTreap 
/// @param i bounding box i como forma
/// @param x1 ancora x do primeiro ponto extremo
/// @param y1 ancora y do primeiro ponto extremo
/// @param x2 ancora x do segundo ponto extremo 
/// @param y2 ancora y do segundo ponto extremo
/// @return retorna true se a forma é interna a região, retorna falso se não.
bool BBinternoRegiao(SmuNode n, BoundingBox i, double x1, double y1, double x2, double y2);


/// @brief vericica se um ponto (x, y) é interno a uma forma (texto, linha, circulo, retangulo)
/// @param n node n da SmuTreap
/// @param forma forma (linha, texto, circulo, retangulo)
/// @param x ancora x do ponto 
/// @param y ancora y do ponto
/// @return retorna true se o ponto é interno a forma passada como parametro, retorna false se não.
bool PontoInternoFormas(SmuNode n, Info forma, double x, double y);

#endif