#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "string.h"
#include "linha.h"

typedef struct stLinha {
    int i;
    double x1, y1, x2, y2;
    char *cor;
    double sw;
} stLinha;

Linha criarLinha(int i, double x1, double y1, double x2, double y2, char *cor) {
    stLinha *l = malloc(sizeof(stLinha));
    l->i = i; 
    l->x1 = x1; l->y1 = y1;
    l->x2 = x2; l->y2 = y2;
    l->sw = 1;

    l->cor = (char *)malloc(strlen(cor)+1);
    if (l->cor == NULL) {
        printf("Erro na alocação de memória na cor do texto");
        exit(1);
    }
    strcpy(l->cor, cor);

    return ((stLinha*)l);
}

int getILinha(Linha l) {
    return ((stLinha*)l)->i;
}

double getX1Linha(Linha l){
    return ((stLinha*)l)->x1;
}

double getY1Linha(Linha l) {
    return ((stLinha*)l)->y1;
}

double getX2Linha(Linha l) {
    return ((stLinha*)l)->x2;
}

double getY2Linha(Linha l){
    return ((stLinha*)l)->y2;
} 
    
char* getCorLinha(Linha l) {
    return ((stLinha*)l)->cor;
}

double calculaAreaL(Linha l) {
    return 10*sqrt(pow( ((stLinha*)l)->x1 - ((stLinha*)l)->x2, 2) + pow( ((stLinha*)l)->y1 - ((stLinha*)l)->y2, 2)); 
}

void setILinha(Linha l, int i) {
    ((stLinha*)l)->i = i;
}

void setX1Linha(Linha l, double x1) {
    ((stLinha*)l)->x1 = x1;
}

void setY1Linha(Linha l, double y1) {
    ((stLinha*)l)->y1 = y1;
}

void setX2Linha(Linha l, double x2) {
    ((stLinha*)l)->x2 = x2;
}

void setY2Linha(Linha l, double y2) {
    ((stLinha*)l)->y2 = y2;
}

void setCorLinha(Linha l, char* cor) {
    ((stLinha*)l)->cor = cor;
}

double getSWLinha(Linha l) {
    return ((stLinha*)l)->sw;
}

void setSWLinha(Linha l, double sw) {
    ((stLinha*)l)->sw = sw;
}

