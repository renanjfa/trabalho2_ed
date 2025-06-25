#include "circulo.h"
#include "string.h"
#include "stdbool.h"

#define PI 3.14159265

typedef struct stCirculo {
    int i;
    double x, y;
    double r;
    char *corb, *corp;
    double sw;
} stCirculo;


Circulo criarCirculo(int i, double x, double y, double raio, char *corb, char *corp) {
    stCirculo *c = malloc(sizeof(stCirculo));
    c->x = x; c->y = y; 
    c->r = raio;
    c->i = i;
    c->sw = 1;

    c->corb = (char*)malloc(strlen(corb)+1);
    if(c->corb == NULL) {
        printf("Erro na alocação de memória para a cor de borda.");
        exit(1);
    }
    strcpy(c->corb, corb);

    c->corp = (char*)malloc(strlen(corp)+1);
    if(c->corp == NULL) {
        printf("Erro na alocação de memória para a cor de preenchimento.");
        exit(1);
    }
    strcpy(c->corp, corp);

    return ((stCirculo*)c);    
} 


int getICirculo(Circulo c) {
    return ((stCirculo*)c)->i;
}

double getXCirculo(Circulo c) {
    return ((stCirculo*)c)->x;
}

double getYCirculo(Circulo c) {
    return ((stCirculo*)c)->y;
}

double getRCirculo(Circulo c) {
    return ((stCirculo*)c)->r;
}

char* getCorbCirculo(Circulo c) {
    return ((stCirculo*)c)->corb;
}

char* getCorpCirculo(Circulo c) {
    return ((stCirculo*)c)->corp;
}

void setICirculo(Circulo c, int i) {
    ((stCirculo*)c)->i = i;
}

void setXCirculo(Circulo c, double x) {
    ((stCirculo*)c)->x = x;
}

void setYCirculo(Circulo c, double y) {
    ((stCirculo*)c)->y = y;
}

void setRCirculo(Circulo c, double r) {
    ((stCirculo*)c)->r = r;
}

void setCorbCirculo(Circulo c, char* corb) {
    strcpy(((stCirculo*)c)->corb, corb);
}

void setCorpCirculo(Circulo c, char* corp) {
    strcpy(((stCirculo*)c)->corp, corp);
}


double calculaAreaC (Circulo c) {
    return PI * ((stCirculo*)c)->r * ((stCirculo*)c)->r;
}

double getSWCirculo(Circulo c) {
    return ((stCirculo*)c)->sw;
}

void setSWCirculo(Circulo c, double sw) {
    ((stCirculo*)c)->sw = sw;
}




