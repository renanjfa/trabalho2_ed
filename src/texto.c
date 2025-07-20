#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "texto.h"
#include <string.h>

typedef struct stEstilo {
    char *family;
    char *weight;
    char *size;
} stEstilo;

typedef struct stTexto {
    int i;
    double x, y;
    char *corb, *corp;
    char a;
    char *texto;
    double sw;  
    Estilo ts;
} stTexto;

Texto criarTexto(int i, double x, double y, char *corb, char *corp, char a, char *texto, Estilo ts) {
    stTexto *t = malloc(sizeof(stTexto));

    t->i = i; 
    t->x = x; t->y = y;
    t->sw = 0.1;

    t->corb = (char *)malloc(strlen(corb)+1);
    if (t->corb == NULL) {
        printf("Erro na alocação de memória da cor de borda");
        exit(1);
    }
    strcpy(t->corb, corb);

    t->corp = (char *)malloc(strlen(corp)+1);
    if (t->corp == NULL) {
        printf("Erro na alocação de memória da cor de preenchimento");
        exit(1);
    }
    strcpy(t->corp, corp);

    t->a = a;

    t->texto = (char *)malloc(strlen(texto)+1);
    if (t->texto == NULL) {
        printf("Erro na alocação de memória no texto");
        exit(1);
    }
    strcpy(t->texto, texto);

    t->ts = ts;

    return ((stTexto*)t);
}

Estilo criarEstilo(char *family, char *weight, char *size) {
    stEstilo *ts = malloc(sizeof(stEstilo));

    ts->family = (char *)malloc(strlen(family)+1);
    if (ts->family == NULL) {
        printf("Erro na alocação de memória da familia");
        exit(1);
    }
    strcpy(ts->family, family);

    ts->weight = (char *)malloc(strlen(weight)+1);
    if (ts->weight == NULL) {
        printf("Erro na alocação de memória do weight");
        exit(1);
    }
    strcpy(ts->weight, weight);

    ts->size = (char *)malloc(strlen(size)+1);
    if (ts->size == NULL) {
        printf("Erro na alocação de memória do size");
        exit(1);
    }
    strcpy(ts->size, size);

    return ((stEstilo*)ts);
}

int getITexto(Texto t) {
    return ((stTexto*)t)->i;
}

double getXTexto(Texto t) {
    return ((stTexto*)t)->x;
}

double getYTexto(Texto t) {
    return ((stTexto*)t)->y;
}

char* getCorbTexto(Texto t) {
    return ((stTexto*)t)->corb;
}

char* getCorpTexto(Texto t) {
    return ((stTexto*)t)->corp;
}

char getATexto(Texto t) {
    return ((stTexto*)t)->a;
}

char* getTextTexto(Texto t) {
    return ((stTexto*)t)->texto;
}

double calculaAreaT(Texto t) {
    return 12*strlen(((stTexto*)t)->texto);
}

void setITexto(Texto t, int i) {
    ((stTexto*)t)->i = i;
}

void setXTexto(Texto t, double x) {
    ((stTexto*)t)->x = x;
}

void setYTexto(Texto t, double y) {
    ((stTexto*)t)->y = y;
}

void setCorbTexto(Texto t, char *corb) {
    ((stTexto*)t)->corb = corb;
}

void setCorpTexto(Texto t, char *corp) {
    ((stTexto*)t)->corp = corp;
}

void setATexto(Texto t, char a) {
    ((stTexto*)t)->a = a;
}

void setTextTexto(Texto t, char *texto) {
    ((stTexto*)t)->texto = texto;
}

char* getSize(Estilo ts) {
    return ((stEstilo*)ts)->size;
}


char* getWeight(Estilo ts) {
    return ((stEstilo*)ts)->weight;
}

char* getFamily(Estilo ts) {
    return ((stEstilo*)ts)->family;
}

void setFamily(Estilo ts, char *family) {
    strcpy(((stEstilo*)ts)->family, family);
}

void setWeight(Estilo ts, char *weight) {
    strcpy(((stEstilo*)ts)->weight, weight);

}

void setSize(Estilo ts, char *size) {
    strcpy(((stEstilo*)ts)->size, size);
}

Estilo getStyle(Texto t) {
    return ((stTexto*)t)->ts;
}

double getSWTexto(Texto t) {
    return ((stTexto*)t)->sw;
}

void setSWTexto(Texto t, double sw) {
    ((stTexto*)t)->sw = sw;
}


