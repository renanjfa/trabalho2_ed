#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "leitura_cidade.h"
#include "enderecos.h"
#include "svg.h"

#define MAX_SIZE 10000


bool leituraLinha(FILE* arq, char *linha, int max_size) {
    if (fgets(linha, max_size, arq) != NULL) {
        return true;
    } else {
        return false;
    }
}

int quantidadeQuadras(FILE *arqcidade) {

    char comando[10];
    char linha[MAX_SIZE];
    char aux[MAX_SIZE];

    int qntQuadras = 0;

    while(leituraLinha(arqcidade, linha, 1000)) {

        aux[0] = '\0';
        comando[0] = '\0';
        strcpy(aux, linha);
        sscanf(aux, "%s", comando);

        if(strcmp(comando, "q") == 0)
            qntQuadras++;
    }

    return qntQuadras;
}


HashTable LeituraCompletaCidade(FILE **svg1, FILE *arqcidade) {
    double ancx, ancy, w, h;
    char corp[300], corb[300], nome[300], sw[300], comando[10];

    int qntQuadras = quantidadeQuadras(arqcidade);
    rewind(arqcidade);
    HashTable ht = createHashTable(qntQuadras);

    char linha[MAX_SIZE];
    char aux[MAX_SIZE];

    while(leituraLinha(arqcidade, linha, 1000)) {

        aux[0] = '\0';
        comando[0] = '\0';
        strcpy(aux, linha);
        sscanf(aux, "%s", comando);

        if(strcmp(comando, "cq") == 0) {
            sscanf(aux, "%s %s %s %s", comando, sw, corp, corb);
        }

        else if(strcmp(comando, "q") == 0) {
            sscanf(aux, "%s %s %lf %lf %lf %lf", comando, nome, &ancx, &ancy, &w, &h);
            
            Quadra q = createQuadra(nome, ancx, ancy, w, h, corb, corp, sw);

            insertHashTable(ht, nome, q);

            insertQuadraSVG(svg1, q);
            // inserir text no svg (nome da quadra);
        }
    }

    return ht;
}

void ProcessaCidade(const char *pathcidade, const char *dirsaida, const char *nomecidade) {
    FILE *arqcidade = fopen(pathcidade, "r");
    printf("Diretorio do arquivo geo: %s\n", pathcidade);
    if (arqcidade == NULL) {
        fprintf(stderr, "Erro na abertura do arquivo GEO (Cidade): %s\n", pathcidade);
        exit(1);
    }

    char saidasvg1[512];
    saidasvg1[0] = '\0';
    strcat(saidasvg1, dirsaida);
    strcat(saidasvg1, nomecidade);
    strcat(saidasvg1, ".svg");
    printf("Diretorio do arquivo svg1: %s\n", saidasvg1);

    FILE *svg1 = fopen(saidasvg1, "w");
    if (svg1 == NULL) {
        fprintf(stderr, "Erro na criação do arquivo SVG: %s\n", saidasvg1);
        exit(1);
    }

    printSVGCabecalho(svg1);

    LeituraCompletaCidade(&svg1, arqcidade);

    fecharSVG(svg1);

    fclose(arqcidade);
}

