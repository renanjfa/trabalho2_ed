#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"
#include "hash_table.h"
#include "graph.h"
#include "smutreap.h"
#include "svg.h"

#define MAX_SIZE 10000



bool leituraLinha(FILE* arq, char *linha, int max_size) {
    if (fgets(linha, max_size, arq) != NULL) {
        return true;
    } else {
        return false;
    }
}

void LeituraCompletaQry(FILE* arqQry, FILE **txt, FILE **svgs2, Graph g, SmuTreap smuVertices, HashTable quadras, HashTable enderecos, HashTable percursos, Lista *arestasN) {
    int num, n;
    double x, y, w, h;
    char comando[30], reg[300], cep[300], face, nome[300], np[300], reg1[300], reg2[300], np1[300], np2[300], cmc[300], cmr[300];

    char linha[MAX_SIZE];
    char aux[MAX_SIZE];

    while(leituraLinha(arqQry, linha, 1000)) {
        aux[0] = '\0';
        strcpy(aux, linha);
        sscanf(aux, "%s", comando);

        if(strcmp(comando, "@o?") == 0) {
            sscanf(aux, "%s %s %s %c %d", comando, reg, cep, &face, &num);
            // registrarEndereco(reg, cep, face, num);
        }

        else if(strcmp(comando, "alag") == 0) {
            sscanf(aux, "%s %d %lf %lf %lf %lf", comando, &n, &x, &y, &w, &h);
            // alag(n, x, y, w, h);
        }

        else if(strcmp(comando, "dren") == 0) {
            sscanf(aux, "%s %d", comando, &n);
            // dren(n);
        }

        else if(strcmp(comando, "sg") == 0) {
            sscanf(aux, "%s %s %lf %lf %lf %lf", comando, nome, &x, &y, &w, &h);
            // sg(nome, x, y, w, h);
        }

        else if(strcmp(comando, "p?") == 0) {
            sscanf(aux, "%s %s %s %s %s", comando, np, nome, reg1, reg2);
            // registrarPercurso(np, nome, reg1, reg2);
        }

        else if(strcmp(comando, "join") == 0) {
            sscanf(aux, "%s %s %s %s", comando, np, np1, np2);
            // join(np, np1, np2);
        }

        else if(strcmp(comando, "shw") == 0) {
            sscanf(aux, "%s %s %s %s", comando, np, cmc, cmr);
            // shw(np, cmc, cmr);
        }
    }
}

void ProcessaQry(const char *pathqry, const char *dirSaida, const char *nomearqsaida, const char *nomeqry, Graph g, SmuTreap smuVertices, HashTable quadras, HashTable enderecos, HashTable percursos, Lista *arestasN) {
    char *pathqry2 = (char*)malloc(sizeof(char)*(strlen(pathqry)+6+strlen(nomeqry)));
    pathqry2[0] = '\0';
    strcpy(pathqry2, pathqry);
    strcat(pathqry2, nomeqry);
    printf("Diretório do arquivo qry: %s\n", pathqry2);

    FILE* arqqry = fopen(pathqry2, "r");
    if(arqqry == NULL) {
        fprintf(stderr, "Erro na abertura do arquivo QRY: %s\n", pathqry2);
        fclose(arqqry);
        exit(1);
    }
    printf("Diretorio de saida: %s\n", dirSaida);

    char svg2[512];
    svg2[0]='\0';
    strcat(svg2, dirSaida);
    strcat(svg2, nomearqsaida);
    strcat(svg2, ".svg");
    printf("Diretório do arquivo svg2: %s\n", svg2);

    char saidatxt[512];
    saidatxt[0]='\0';
    strcat(saidatxt, dirSaida);
    strcat(saidatxt, nomearqsaida);
    strcat(saidatxt, ".txt");
    printf("nDiretório do arquivo txt: %s\n", saidatxt);

    FILE* ssvg2 = fopen(svg2, "w");
    if (ssvg2==NULL) {
        fprintf(stderr, "Erro na criação do arquivo SVG: %s\n", svg2);
        fclose(arqqry);
        fclose(ssvg2);
        exit(1);
    }

    printSVGCabecalho(ssvg2);

    FILE* stxt = fopen(saidatxt, "w");
    if(stxt == NULL) {
        fprintf(stderr, "Erro na criacao do arquivo TXT: %s\n", saidatxt);
        fclose(arqqry);
        fclose(ssvg2);
        fclose(stxt);
        exit(1);
    }

    LeituraCompletaQry(arqqry, &stxt, &ssvg2, g, smuVertices, quadras, enderecos, percursos, arestasN);

    fecharSVG(ssvg2);
    fclose(arqqry);
    fclose(stxt);
}


