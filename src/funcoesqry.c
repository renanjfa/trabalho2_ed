#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoesqry.h"
#include "hash_table.h"
#include "enderecos.h"
#include "registradores.h"
#include "boundingbox.h"
#include "svg.h"


void registrarEndereco(FILE* svg, FILE* txt, HashTable enderecos, HashTable quadras, char *nomereg, char *nomeQuadra, char face, int num) {

    Endereco e = createEndereco(nomeQuadra, face, num, quadras);
    insertHashTable(enderecos, nomereg, e);

    double x, y;
    x = getXEndereco(e);
    y = getYEndereco(e);

    fprintf(txt, "Coordenada do endereco: (%.3lf, %.3lf)\n", x, y);

    Linha l1 = criarLinha(27, 30, y, x, y, "red", true);
    Linha l2 = criarLinha(27, x, 30, x, y, "red", true);

    insertLineSVG(svg, l1);
    insertLineSVG(svg, l2);

    Estilo ts = criarEstilo("sans", "b", "5px");
    Texto t1 = criarTexto(27, 30, y-3, "black", "black", 'i', nomereg, ts);
    Texto t2 = criarTexto(27, x+3, 30, "black", "black", 'i', nomereg, ts);

    insertTextSVG(svg, t1);
    insertTextSVG(svg, t2);

    Circulo c = criarCirculo(27, x, y, 3, "black", "orange");

    insertCircleSVG(svg, c);
}


void shw(FILE* svg, char *np, char *cmc, char *cmr, HashTable percursos) {

    Percurso p = buscaHashTable(percursos, np);

    Lista path_cmc = getPathCMCPercurso(p);

    for(Celula p = getInicioLista(path_cmc); getProxCelula(p) != NULL && p != NULL; p = getProxCelula(p)) {
        Coordenadas inicio = getConteudoCelula(p);
        Coordenadas fim = getConteudoCelula(getProxCelula(p));

        Linha l1 = criarLinha(27, getXCoord(inicio), getYCoord(inicio), getXCoord(fim), getYCoord(fim), cmc, false);
    }


    Lista path_cmr = getPathCMRPercurso(p);

    for(Celula p = getInicioLista(path_cmr); getProxCelula(p) != NULL && p != NULL; p = getProxCelula(p)) {
        Coordenadas inicio = getConteudoCelula(p);
        Coordenadas fim = getConteudoCelula(getProxCelula(p));

        Linha l1 = criarLinha(27, getXCoord(inicio), getYCoord(inicio), getXCoord(fim), getYCoord(fim), cmr, false);
    }

    printAnimationSVG(svg, getNomePercurso(p));
}



void desabilitarArestasAlagadas(Graph g, Lista arestas) {
    if(!g || !arestas) return;

    for(Celula p = getInicioLista(arestas); p!=NULL; p = getProxCelula(p)) {

        Edge e = getConteudoCelula(p);
        setHabilitadaEdge(g, e, false);

    }
}

// reportar svg e txt
void alag(FILE* svg, FILE* txt, Graph g, SmuTreap t, int n, double x, double y, double w, double h, Lista *arestasN) {
    Lista esquinas_alagadas = criaLista(); // esquinas alagadas

    if(getInfosDentroRegiaoSmuT(t, x, y, w, h, BBinternoRegiao, esquinas_alagadas)) {
        for(Celula p = getInicioLista(esquinas_alagadas); p != NULL; p = getProxCelula(p)) {

            SmuNode atual = getConteudoCelula(p);
            Esquina eq = getInfoSmuT(t, atual);

            Node from = getNode(g, getNomeEsquina(eq));
            
            adjacentEdges(g, from, arestasN[n]);
        }
    }

    desabilitarArestasAlagadas(g, arestasN[n]);
}

// reportar svg e txt
void dren(FILE *txt, Graph g, int n, Lista *arestasN) {

    for(Celula p = getInicioLista(arestasN[n]); p != NULL; p = getProxCelula(p)) {

        Edge e = getConteudoCelula(p);
        setHabilitadaEdge(g, e, true);

    }
}
