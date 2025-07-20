#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"
#include "hash_table.h"
#include "graph.h"
#include "smutreap.h"
#include "svg.h"
#include "funcoesqry.h"
#include "tratar_strings.h"

#define MAX_SIZE 10000


void inserirQuadrasSVG2(char *key, Quadra q, FILE* svg) {
    if(!q) return;
    Estilo ts = criarEstilo("sans", "b", "12px");

    insertQuadraSVG(svg, q);
    insertTextSVG(svg, criarTexto(27, getXQuadra(q)+7, getYQuadra(q)+12, "black", "black", 'i', getNomeQuadra(q), ts));
    free(ts);
}

void printEsquinasSVG(SmuNode n, Info i, double x, double y, FILE* svg) {
    if(!n || !svg || !i) return;

    Circulo c = criarCirculo(27, x, y, 2, "orange", "orange");
    insertCircleSVG(svg, c);
    free(c);
}



void LeituraCompletaQry(FILE* arqQry, FILE **txt, FILE **svg2, Graph g, SmuTreap smuVertices, HashTable quadras, HashTable enderecos, HashTable percursos, Lista *arestasN) {
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
            fprintf(*txt, "[*] @o? %s %s %c %d\n", reg, cep, face, num);
            registrarEndereco(*svg2, *txt, enderecos, quadras, reg, cep, face, num);
        }

        else if(strcmp(comando, "alag") == 0) {
            sscanf(aux, "%s %d %lf %lf %lf %lf", comando, &n, &x, &y, &w, &h);
            fprintf(*txt, "[*] alag %d %.3lf %.3lf %.3lf %.3lf\n", n, x, y, w, h);
            alag(*svg2, *txt, g, smuVertices, n, x, y, w, h, arestasN);
        }

        else if(strcmp(comando, "dren") == 0) {
            sscanf(aux, "%s %d", comando, &n);
            fprintf(*txt, "[*] dren %d\n", n);
            dren(*txt, g, n, arestasN);
        }

        else if(strcmp(comando, "sg") == 0) {
            sscanf(aux, "%s %s %lf %lf %lf %lf", comando, nome, &x, &y, &w, &h);
            // sg(nome, x, y, w, h);
        }

        else if(strcmp(comando, "p?") == 0) {
            sscanf(aux, "%s %s %s %s %s", comando, np, nome, reg1, reg2);
            registrarPercurso(*svg2, g, smuVertices, enderecos, percursos, np, nome, reg1, reg2);
        }

        else if(strcmp(comando, "join") == 0) {
            sscanf(aux, "%s %s %s %s", comando, np, np1, np2);
            join(*svg2, g, smuVertices, percursos, enderecos, np, np1, np2);
        }

        else if(strcmp(comando, "shw") == 0) {
            sscanf(aux, "%s %s %s %s", comando, np, cmc, cmr);
            shw(*svg2, np, cmc, cmr, percursos);
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

    percorrerHashTable(quadras, inserirQuadrasSVG2, ssvg2);
    //printf("saiu percorrer hashtable\n");
    visitaProfundidadeSmuT(smuVertices, printEsquinasSVG, ssvg2);
    //printf("saiu visitaProfundidade\n");

    LeituraCompletaQry(arqqry, &stxt, &ssvg2, g, smuVertices, quadras, enderecos, percursos, arestasN);

    fecharSVG(ssvg2);
    fclose(arqqry);
    fclose(stxt);
}


