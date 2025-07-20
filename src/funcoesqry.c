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

    Estilo ts = criarEstilo("sans", "b", "15px");
    Texto t1 = criarTexto(27, 30, y-3, "black", "black", 'i', nomereg, ts);
    Texto t2 = criarTexto(27, x+3, 30, "black", "black", 'i', nomereg, ts);

    insertTextSVG(svg, t1);
    insertTextSVG(svg, t2);

    Circulo c = criarCirculo(27, x, y, 3, "black", "orange");

    insertCircleSVG(svg, c);
    free(c); free(ts); free(t1); free(t2); free(l1); free(l2);
}


void shw(FILE* svg, char *np, char *cmc, char *cmr, HashTable percursos) {

    printf("entrada shw\n");
    Percurso p = buscaHashTable(percursos, np);
    printf("saiu buscahash\n");
    if(!p) {
        printf("percurso null\n");
    }

    Lista path_cmc = getPathCMCPercurso(p);
    printf("lista cmc\n");

    for(Celula p = getInicioLista(path_cmc); getProxCelula(p) != NULL && p != NULL; p = getProxCelula(p)) {
        Coordenadas inicio = getConteudoCelula(p);
        Coordenadas fim = getConteudoCelula(getProxCelula(p));

        Linha l1 = criarLinha(27, getXCoord(inicio)+3, getYCoord(inicio)+3, getXCoord(fim)+3, getYCoord(fim)+3, cmc, false);
        setSWLinha(l1, 6);
        insertLineSVG(svg, l1);
    }
    printf("saiu loop print linhas path cmc\n");


    Lista path_cmr = getPathCMRPercurso(p);

    for(Celula p = getInicioLista(path_cmr); getProxCelula(p) != NULL && p != NULL; p = getProxCelula(p)) {
        Coordenadas inicio = getConteudoCelula(p);
        Coordenadas fim = getConteudoCelula(getProxCelula(p));

        Linha l2 = criarLinha(27, getXCoord(inicio), getYCoord(inicio), getXCoord(fim), getYCoord(fim), cmr, false);
        setSWLinha(l2, 6);
        insertLineSVG(svg, l2);
    }

    printf("saiu loop print linhas path cmc\n");


    char *path_name_cmc = malloc((strlen(np)+5) * sizeof(char));
    char *path_name_cmr = malloc((strlen(np)+5) * sizeof(char));

    strcat(path_name_cmc, "cmc");
    strcat(path_name_cmr, "cmr");

    printPathCMCSVG(svg, p, path_name_cmc);
    printPathCMRSVG(svg, p, path_name_cmr);

    printAnimationSVG(svg, path_name_cmc);
    printAnimationSVG(svg, path_name_cmr);

    printf("saida shw\n");
}



void desabilitarArestasAlagadas(Graph g, Lista arestas, FILE* svg) {
    if(!g || !arestas) return;
    double x1, y1, x2, y2;

    for(Celula p = getInicioLista(arestas); p!=NULL; p = getProxCelula(p)) {

        Edge e = getConteudoCelula(p);

        Node idx_from = getFromNode(g, e);
        Node idx_to = getToNode(g, e);
        //printf("idx_from = %d\tidx_to = %d\n");
        
        Esquina eq_from = getNodeInfo(g, idx_from);
        Esquina eq_to = getNodeInfo(g, idx_to);

        x1 = getXEsquina(eq_from); y1 = getYEsquina(eq_from);
        x2 = getXEsquina(eq_to); y2 = getYEsquina(eq_to);

        //printf("LinhaEdge => %s -> %s \nx1: %.2lf\ty1: %.2lf\tx2: %.2lf\ty2: %.2lf\n", getNomeEsquina(eq_from), getNomeEsquina(eq_to), x1, y1, x2, y2);

        Linha l = criarLinha(27, x1, y1, x2, y2, "green", false);
        insertLineSVG(svg, l);

        setHabilitadaEdge(g, e, false);

    }
}

// reportar svg e txt
void alag(FILE* svg, FILE* txt, Graph g, SmuTreap t, int n, double x, double y, double w, double h, Lista *arestasN) {
    Lista esquinas_alagadas = criaLista(); // esquinas alagadas

    Retangulo r = criarRetangulo(27, x, y, w, h, "red", "red");
    insertRectSVG(svg, r);

    if(getInfosDentroRegiaoSmuT(t, x, y, w, h, BBinternoRegiao, esquinas_alagadas)) {
        for(Celula p = getInicioLista(esquinas_alagadas); p != NULL; p = getProxCelula(p)) {

            SmuNode atual = getConteudoCelula(p);
            Esquina eq = getInfoSmuT(t, atual);

            Node from = getNode(g, getNomeEsquina(eq));
            
            adjacentEdges(g, from, arestasN[n]);
        }
    }

    desabilitarArestasAlagadas(g, arestasN[n], svg);
}

// reportar svg e txt
void dren(FILE *txt, Graph g, int n, Lista *arestasN) {

    for(Celula p = getInicioLista(arestasN[n]); p != NULL; p = getProxCelula(p)) {

        Edge e = getConteudoCelula(p);
        setHabilitadaEdge(g, e, true);

    }
}


double extraiComprimento(Rua r) {
    return getComprimentoRua(r);
}

double extraiVelocidade(Rua r) {
    return getComprimentoRua(r)/getVelocidadeRua(r);
}

void registrarPercurso(FILE* svg, Graph g, SmuTreap t, HashTable enderecos, HashTable percursos, char *np, char *nome, char *reg1, char *reg2) {
    
    printf("entrada p?\n");
    Endereco origem = buscaHashTable(enderecos, reg1);
    Endereco destino = buscaHashTable(enderecos, reg2);

    Esquina e1 = getInfoMaisProximoRaioSmuT(t, getXEndereco(origem), getYEndereco(origem), 50, BBinternoRegiao);
    Esquina e2 = getInfoMaisProximoRaioSmuT(t, getXEndereco(destino), getYEndereco(destino), 50, BBinternoRegiao);

    Percurso p = createPercurso(np, getNomeEsquina(e1), getNomeEsquina(e2));
    insertHashTable(percursos, np, p);


    int *cmc = malloc(getTotalNodes(g) * sizeof(int));
    int *cmr = malloc(getTotalNodes(g) * sizeof(int));
    int tam_cmc;
    int tam_cmr;

    printGraph(g, extraiComprimento);

    dijkstra(g, getNomeEsquina(e1), getNomeEsquina(e2), cmc, &tam_cmc, extraiComprimento);
    dijkstra(g, getNomeEsquina(e1), getNomeEsquina(e2), cmr, &tam_cmr, extraiVelocidade);

    for(int i = 0; i<tam_cmc; i++) {

        printf("%d ", cmc[i]);
        Esquina e = getNodeInfo(g, cmc[i]);

        Coordenadas c = createCoordenadas(getXEsquina(e), getYEsquina(e));
        insertPathCMCPercurso(p, c);
    }
    printf("\n");

    for(int i = 0; i<tam_cmr; i++) {

        printf("%d ", cmr[i]);
        Esquina e = getNodeInfo(g, cmr[i]);

        Coordenadas c = createCoordenadas(getXEsquina(e), getYEsquina(e));
        insertPathCMRPercurso(p, c);
    }
    printf("\n");

    printPathCMCSVG(svg, p, np);



    printf("saida p?\n");
}


// void join(FILE* svg, Graph g, SmuTreap t, HashTable percursos, HashTable enderecos, char *np, char *np1, char *np2) {

    


// }


