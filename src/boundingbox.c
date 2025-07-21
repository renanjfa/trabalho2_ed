#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "boundingbox.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "smutreap.h"

#define TPC 0  // definicao CIRCULO
#define TPL 1  // definicao LINHA
#define TPR 2  // definicao RETANGULO
#define TPT 3  // definicao TEXTO

typedef struct stBB {
    double x, y; 
    double w, h;
} stBB;



BoundingBox criarBB(double x, double y, double w, double h) {
    stBB *bb = malloc(sizeof(stBB));
    bb->x = x;
    bb->y = y;
    bb->w = w;
    bb->h = h;
    return ((stBB*)bb);
}


void calculaParametroBBRetangulo(Retangulo r, double *x, double *y, double *w, double *h) {
    *x = getXRetangulo(r);
    *y = getYRetangulo(r);
    *w = getWRetangulo(r);
    *h = getHRetangulo(r); 
}

void calculaParametroBBCirculo(Circulo c, double *x, double *y, double *w, double *h) {
    *x = fabs(getXCirculo(c) - getRCirculo(c));
    *y = fabs(getYCirculo(c) - getRCirculo(c));
    *w = 2*getRCirculo(c);
    *h = 2*getRCirculo(c);
}

void calculaParametroBBLinha(Linha l, double *x, double *y, double *w, double *h) {
    double x1, y1, x2, y2;
    x1 = getX1Linha(l); y1 = getY1Linha(l);
    x2 = getX2Linha(l); y2 = getY2Linha(l);

    if (fabs(x1 - x2) < 0.0001 || x1 < x2)
        *x = x1;
    else
        *x = x2;

    if (fabs(y1 - y2) < 0.0001 || y1 < y2)
        *y = y1;
    else
        *y = y2;

    *w = fabs(x1 - x2);
    *h = fabs(y1 - y2);
}

void calculaParametroBBTexto(Texto t, double *x, double *y, double *w, double *h) {
    *x = getXTexto(t);
    *y = getYTexto(t);
    *w = 0;
    *h = 0;
}

void uniaoBBAmbosFilhos(BoundingBox bbmain, BoundingBox bbinfo, BoundingBox bbesq, BoundingBox bbdir) {
    double minX = fmin(((stBB*)bbinfo)->x, fmin(((stBB*)bbesq)->x, ((stBB*)bbdir)->x));
    double minY = fmin(((stBB*)bbinfo)->y, fmin(((stBB*)bbesq)->y, ((stBB*)bbdir)->y));
    double maxXW = fmax(((stBB*)bbinfo)->x + ((stBB*)bbinfo)->w, 
                       fmax(((stBB*)bbesq)->x + ((stBB*)bbesq)->w, 
                           ((stBB*)bbdir)->x + ((stBB*)bbdir)->w));
    double maxYH = fmax(((stBB*)bbinfo)->y + ((stBB*)bbinfo)->h, 
                       fmax(((stBB*)bbesq)->y + ((stBB*)bbesq)->h, 
                           ((stBB*)bbdir)->y + ((stBB*)bbdir)->h));
    
    ((stBB*)bbmain)->x = minX;
    ((stBB*)bbmain)->y = minY;
    ((stBB*)bbmain)->w = maxXW - minX;
    ((stBB*)bbmain)->h = maxYH - minY;
}

void uniaoBBSemFilhos(BoundingBox bbmain, BoundingBox bbinfo) {
    ((stBB*)bbmain)->x = ((stBB*)bbinfo)->x;
    ((stBB*)bbmain)->y = ((stBB*)bbinfo)->y;
    ((stBB*)bbmain)->w = ((stBB*)bbinfo)->w;
    ((stBB*)bbmain)->h = ((stBB*)bbinfo)->h;
}


void uniaoBBEsquerda(BoundingBox bbmain, BoundingBox bbesq) {
    // Calcula os limites do bounding box existente (bbmain)
    double main_x1 = ((stBB*)bbmain)->x;
    double main_y1 = ((stBB*)bbmain)->y;
    double main_x2 = main_x1 + ((stBB*)bbmain)->w;
    double main_y2 = main_y1 + ((stBB*)bbmain)->h;
    
    // Calcula os limites do bounding box esquerdo (bbesq)
    double esq_x1 = ((stBB*)bbesq)->x;
    double esq_y1 = ((stBB*)bbesq)->y;
    double esq_x2 = esq_x1 + ((stBB*)bbesq)->w;
    double esq_y2 = esq_y1 + ((stBB*)bbesq)->h;
    
    // Calcula o novo bounding box que engloba ambos
    double new_x1 = fmin(main_x1, esq_x1);
    double new_y1 = fmin(main_y1, esq_y1);
    double new_x2 = fmax(main_x2, esq_x2);
    double new_y2 = fmax(main_y2, esq_y2);
    
    // Atualiza o bounding box principal
    ((stBB*)bbmain)->x = new_x1;
    ((stBB*)bbmain)->y = new_y1;
    ((stBB*)bbmain)->w = new_x2 - new_x1;
    ((stBB*)bbmain)->h = new_y2 - new_y1;
}

void uniaoBBDireita(BoundingBox bbmain, BoundingBox bbdir) {
    // Calcula os limites do bounding box existente (bbmain)
    double main_x1 = ((stBB*)bbmain)->x;
    double main_y1 = ((stBB*)bbmain)->y;
    double main_x2 = main_x1 + ((stBB*)bbmain)->w;
    double main_y2 = main_y1 + ((stBB*)bbmain)->h;
    
    // Calcula os limites do bounding box direito (bbdir)
    double dir_x1 = ((stBB*)bbdir)->x;
    double dir_y1 = ((stBB*)bbdir)->y;
    double dir_x2 = dir_x1 + ((stBB*)bbdir)->w;
    double dir_y2 = dir_y1 + ((stBB*)bbdir)->h;
    
    // Calcula o novo bounding box que engloba ambos
    double new_x1 = fmin(main_x1, dir_x1);
    double new_y1 = fmin(main_y1, dir_y1);
    double new_x2 = fmax(main_x2, dir_x2);
    double new_y2 = fmax(main_y2, dir_y2);
    
    // Atualiza o bounding box principal
    ((stBB*)bbmain)->x = new_x1;
    ((stBB*)bbmain)->y = new_y1;
    ((stBB*)bbmain)->w = new_x2 - new_x1;
    ((stBB*)bbmain)->h = new_y2 - new_y1;
}

double getXBoundingBox(BoundingBox bb) {
    return ((stBB*)bb)->x;
}

double getYBoundingBox(BoundingBox bb) {
    return ((stBB*)bb)->y;
}

double getWBoundingBox(BoundingBox bb) {
    return ((stBB*)bb)->w;
}

double getHBoundingBox(BoundingBox bb) {
    return ((stBB*)bb)->h;
}

typedef struct ponto {
    double x, y;
} Ponto;

bool BBinternoRegiao(SmuNode r, BoundingBox bbinfo, double x1, double y1, double x2, double y2) {
    (void)r;
    Ponto p1, p4;
    p1.x = ((stBB*)bbinfo)->x; 
    p1.y = ((stBB*)bbinfo)->y;
    p4.x = ((stBB*)bbinfo)->x + ((stBB*)bbinfo)->w;
    p4.y = ((stBB*)bbinfo)->y + ((stBB*)bbinfo)->h;

    double epsilon = 0.0001;

    if ((x1 - epsilon <= p1.x && p1.x <= x2 + epsilon) &&
    (y1 - epsilon <= p1.y && p1.y <= y2 + epsilon) &&
    (x1 - epsilon <= p4.x && p4.x <= x2 + epsilon) &&
    (y1 - epsilon <= p4.y && p4.y <= y2 + epsilon))

        return true;
    else 
        return false;
}


bool aproximadamenteIgualEpsilon(double a, double b, double epsilon) {
    return fabs(a - b) <= epsilon;
}

bool pontoInternoLinha(double x, double y, double x1, double y1, double x2, double y2, double epsilon) {
    double determinante = (x - x1) * (y2 - y1) - (y - y1) * (x2 - x1);
    if (!aproximadamenteIgualEpsilon(determinante, 0.0, epsilon)) {
        return false; // não tá na mesma linha
    }

    if ((x >= fmin(x1, x2) - epsilon && x <= fmax(x1, x2) + epsilon) &&
        (y >= fmin(y1, y2) - epsilon && y <= fmax(y1, y2) + epsilon)) {
        return true;
    }

    return false;
}


bool PontoInternoFormas(SmuNode r, Info i, double x, double y) {
    double x1, y1, raio, w, h, x2, y2;
    double epsilon = 0.0001;
    int descritor = getTypeInfoSrbT(0, r);

    switch(descritor) {
        case TPC:
            x1 = getXCirculo(i); y1 = getYCirculo(i);
            raio = getRCirculo(i);
            if( (sqrt(pow(x1 - x, 2) + pow(y1 - y, 2)) <= raio + epsilon))
                return true;
            break;
        case TPL:
            x1 = getX1Linha(i); y1 = getY1Linha(i);
            x2 = getX2Linha(i); y2 = getY2Linha(i);
            if(pontoInternoLinha(x, y, x1, y1, x2, y2, epsilon))
                return true;
            break;
        case TPR:   
            x1 = getXRetangulo(i); y1 = getYRetangulo(i);
            w = getWRetangulo(i); h = getHRetangulo(i);
            if((x >= x1 - epsilon && x <= x1 + w + epsilon) && (y >= y1 - epsilon && y <= y1 + h + epsilon))
                return true;
            break;
        case TPT:
            x1 = getXTexto(i); y1 = getYTexto(i);
            if(fabs(x - x1) <= epsilon && fabs(y - y1) <= epsilon ) 
                return true;
            break;
    }
    return false;
}








