#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "leitura_via.h"
#include "graph.h"
#include "enderecos.h"
#include "svg.h"
#include "tratar_strings.h"

#define MAX_SIZE 10000

Graph LeituraCompletaVia(FILE *arqvia, SmuTreap t) {
    double x, y, comp, veloc;
    char i[300], j[300], ldir[300], lesq[300], nome[300], id[300];
    char comando[10];

    // leitura nv no inicio do arquvio.via e criar graph com nVert
    int nVert;
    fscanf(arqvia, "%d", &nVert);
    Graph g = createGraph(nVert, true, "-");

    char linha[MAX_SIZE];
    char aux[MAX_SIZE];

    while(leituraLinha(arqvia, linha, MAX_SIZE)) {

        aux[0] = '\0';
        comando[0] = '\0';
        strcpy(aux, linha);
        sscanf(aux, "%s", comando);

        if(strcmp("v", comando) == 0) {
            sscanf(aux, "%s %s %lf %lf", comando, id, &x, &y);

            Esquina eq = createEsquina(id, x, y);

            addNode(g, id, x, y, eq);

            insertSmuT(t, x, y, eq, 5, calculaBoundingBoxEsquina);
        }
        
        else if(strcmp("e", comando) == 0) {
            sscanf(aux, "%s %s %s %s %s %lf %lf %s", comando, i, j, ldir, lesq, &comp, &veloc, nome);

            Rua rua = createRua(nome, lesq, ldir, comp, veloc);

            addEdge(g, getNode(g, i), getNode(g, j), rua);

        }
    }

    return g;
}

Graph ProcessaVia(const char *pathvia, SmuTreap t) {
    FILE *arqvia = fopen(pathvia, "r");
    printf("Diretorio do arquivo via: %s\n", pathvia);
    if (arqvia == NULL) {
        fprintf(stderr, "Erro na abertura do arquivo Via (Via): %s\n", pathvia);
        exit(1);
    }

    Graph g = LeituraCompletaVia(arqvia, t);
    return g;
}