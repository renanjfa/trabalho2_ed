#ifndef SVG_H
#define SVG_H

#include <stdio.h>
#include <stdlib.h>

#include "enderecos.h"
#include "circulo.h"
#include "linha.h"
#include "retangulo.h"
#include "texto.h"
#include "lista.h"
#include "registradores.h"

/*
    SVG.H
    Módulo responsável por realizar operações de inserção de formas e paths em um svg dado.
*/


void printSVGCabecalho(FILE *svg);

void fecharSVG(FILE *svg);

void insertQuadraSVG(FILE *svg, Quadra q);

void insertCircleSVG(FILE *svg, Circulo c);

void insertRectSVG(FILE *svg, Retangulo r);

void insertLineSVG(FILE *svg, Linha l);

void insertTextSVG(FILE *svg, Texto t);

void printPathCMCSVG(FILE *svg, Percurso p, char *nomepath);

void printPathCMRSVG(FILE *svg, Percurso p, char *nomepath);

void printAnimationSVG(FILE *svg, char *idpath, double animationTime);


#endif