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


/// @brief Abre o arquivo svg fornecido com print do cabeçalho.
/// @param svg Arquivo svg.
void printSVGCabecalho(FILE *svg);

/// @brief Fecha o arquivo svg fornecido.
/// @param svg Arquivo svg.
void fecharSVG(FILE *svg);

/// @brief Insere um quadra ao svg.
/// @param svg Arquivo svg.
/// @param q Quadra q.
void insertQuadraSVG(FILE *svg, Quadra q);

/// @brief Insere um circulo ao svg.
/// @param svg Arquivo svg.
/// @param c Circulo c.
void insertCircleSVG(FILE *svg, Circulo c);

/// @brief Insere um retangulo ao svg.
/// @param svg Arquivo svg.
/// @param r Retangulo r.
void insertRectSVG(FILE *svg, Retangulo r);

/// @brief Insere uma linha ao svg.
/// @param svg Arquivo svg.
/// @param l Linha l.
void insertLineSVG(FILE *svg, Linha l);

/// @brief Insere um texto ao svg.
/// @param svg Arquivo svg.
/// @param t Texto t.
void insertTextSVG(FILE *svg, Texto t);

/// @brief Printa o path relacionado ao caminho mais curto do percurso p.
/// @param svg Arquivo svg.
/// @param p Percurso p.
/// @param nomepath Nome a ser dado ao id do path.
void printPathCMCSVG(FILE *svg, Percurso p, char *nomepath);

/// @brief Printa o path relacionado ao caminho mais rápido do percurso p.
/// @param svg Arquivo svg.
/// @param p Percurso p.
/// @param nomepath Nome a ser dado ao id do path.
void printPathCMRSVG(FILE *svg, Percurso p, char *nomepath);

/// @brief Printa a animação do escudo do Clube de Regatas do Flamengo descrita pelo path de idpath.
/// @param svg Arquivo svg.
/// @param idpath Nome do path a ser descrito e mostrado.
/// @param animationTime Tempo da animação.
void printAnimationSVG(FILE *svg, char *idpath, double animationTime);


#endif