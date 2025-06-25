#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "retangulo.h"
#include "stdbool.h"

typedef struct stRetangulo {
    int i;
    double x, y;
    double w, h;
    char *corb, *corp;
    double sw;
} stRetangulo;

Retangulo criarRetangulo(int i, double x, double y, double w, double h, char *corb, char *corp) {
    stRetangulo *r = malloc(sizeof(stRetangulo));
    r->x = x; r->y = y; 
    r->w = w; r->h = h;
    r->i = i; 
    r->sw = 1;

    r->corb = (char *)malloc(strlen(corb)+1);
    if (r->corb == NULL) {
        printf("Erro na alocação de memória para corb");
        free(r);
        exit(1);
    }
    strcpy(r->corb, corb);

    r->corp = (char *)malloc(strlen(corp)+1);
    if (r->corp == NULL) {
        printf("Erro na alocação de memória");
        free(r);
        exit(1);
    }
    strcpy(r->corp, corp);

    return ((stRetangulo*)r);    
}

int getIRetangulo(Retangulo r) {
    return ((stRetangulo*)r)->i; 
}

double getXRetangulo(Retangulo r) {
    return ((stRetangulo*)r)->x;
}

double getYRetangulo(Retangulo r) {
    return ((stRetangulo*)r)->y;
}

double getWRetangulo(Retangulo r) {
    return ((stRetangulo*)r)->w;
}

double getHRetangulo(Retangulo r) {
    return ((stRetangulo*)r)->h;
}

char* getCorbRetangulo(Retangulo r) {
    return ((stRetangulo*)r)->corb;
}

char* getCorpRetangulo(Retangulo r) {
    return ((stRetangulo*)r)->corp;
}

double calculaAreaR(Retangulo r) {
    return ((stRetangulo*)r)->w * ((stRetangulo*)r)->h;
} 

void setIRetangulo(Retangulo r, int i) {
    ((stRetangulo*)r)->i = i;
}

void setXRetangulo(Retangulo r, double x) {
    ((stRetangulo*)r)->x = x;
}

void setYRetangulo(Retangulo r, double y) {
    ((stRetangulo*)r)->y = y;
}

void setWRetangulo(Retangulo r, double w) {
    ((stRetangulo*)r)->w = w;
}

void setHRetangulo(Retangulo r, double h) {
    ((stRetangulo*)r)->h = h;
}

void setCorbRetangulo(Retangulo r, char* corb) {
    strcpy(((stRetangulo*)r)->corb, corb);
}

void setCorpRetangulo(Retangulo r, char* corp) {
    strcpy(((stRetangulo*)r)->corp, corp);
}

double getSWRetangulo(Retangulo r) {
    return ((stRetangulo*)r)->sw;
}

void setSWRetangulo(Retangulo r, double sw) {
    ((stRetangulo*)r)->sw = sw;
}


