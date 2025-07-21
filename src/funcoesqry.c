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

    fprintf(txt, "Coordenada do endereco: (%.3lf, %.3lf)\n\n", x, y);

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

    bool inalcancavel = false;

    Lista path_cmc = getPathCMCPercurso(p);
    if(getTamanhoLista(path_cmc) == 1) {
        printf("SEM DESTINO\n");
        Endereco origem_cmc = getOrigemPercurso(p);
        Endereco destino_cmc = getDestinoPercurso(p);

        Linha l_inalcancavel_cmc = criarLinha(27, getXEndereco(origem_cmc), getYEndereco(origem_cmc), getXEndereco(destino_cmc), getYEndereco(destino_cmc), "red", true);
        setSWLinha(l_inalcancavel_cmc, 10);
        insertLineSVG(svg, l_inalcancavel_cmc);

        Circulo c1 = criarCirculo(27, getXEndereco(destino_cmc), getYEndereco(destino_cmc), 30, "black", "black");
        Estilo ts = criarEstilo("sans", "b", "30px");
        Texto t = criarTexto(27, getXEndereco(destino_cmc)+50, getYEndereco(destino_cmc), "black", "black", 'i', "DESTINO", ts);
        insertCircleSVG(svg, c1); insertTextSVG(svg, t);

        inalcancavel = true;
    }
    else {

        for(Celula p = getInicioLista(path_cmc); getProxCelula(p) != NULL && p != NULL; p = getProxCelula(p)) {
            Coordenadas inicio = getConteudoCelula(p);
            Coordenadas fim = getConteudoCelula(getProxCelula(p));
            printf("TAMANHO LISTA CMC: %d\n", getTamanhoLista(path_cmc));
    
            
            Linha l1 = criarLinha(27, getXCoord(inicio)+3, getYCoord(inicio)+3, getXCoord(fim)+3, getYCoord(fim)+3, cmc, false);
            setSWLinha(l1, 6);
            insertLineSVG(svg, l1);
        }
    }
    
    
    Lista path_cmr = getPathCMRPercurso(p);
    if(!(getTamanhoLista(path_cmr) == 1)) {
        
        for(Celula p = getInicioLista(path_cmr); getProxCelula(p) != NULL && p != NULL; p = getProxCelula(p)) {
            Coordenadas inicio = getConteudoCelula(p);
            Coordenadas fim = getConteudoCelula(getProxCelula(p));
    
            Linha l2 = criarLinha(27, getXCoord(inicio), getYCoord(inicio), getXCoord(fim), getYCoord(fim), cmr, false);
            setSWLinha(l2, 6);
            insertLineSVG(svg, l2);
        }
    }
    

    
    
    if(!inalcancavel) {

        char *path_name_cmc = malloc((strlen(np)+5) * sizeof(char));
        char *path_name_cmr = malloc((strlen(np)+5) * sizeof(char));
    
        strcpy(path_name_cmc, np);
        strcpy(path_name_cmr, np);
    
        strcat(path_name_cmc, "cmc");
        strcat(path_name_cmr, "cmr");
    
        printPathCMCSVG(svg, p, path_name_cmc);
        printPathCMRSVG(svg, p, path_name_cmr);
    
        printAnimationSVG(svg, path_name_cmc);
        printAnimationSVG(svg, path_name_cmr);
    }


    printf("saida shw\n");
}



void desabilitarArestasAlagadas(Graph g, Lista arestas, FILE* svg, FILE* txt) {
    if(!g || !arestas) return;
    double x1, y1, x2, y2;

    for(Celula p = getInicioLista(arestas); p!=NULL; p = getProxCelula(p)) {

        Edge e = getConteudoCelula(p);

        Node idx_from = getFromNode(g, e);
        Node idx_to = getToNode(g, e);
        
        Esquina eq_from = getNodeInfo(g, idx_from);
        Esquina eq_to = getNodeInfo(g, idx_to);

        x1 = getXEsquina(eq_from); y1 = getYEsquina(eq_from);
        x2 = getXEsquina(eq_to); y2 = getYEsquina(eq_to);
 

        Linha l = criarLinha(27, x1, y1, x2, y2, "black", false);
        insertLineSVG(svg, l);

        setHabilitadaEdge(g, e, false);

        Rua r = getEdgeInfo(g, e);

        fprintf(txt, "Aresta Desabilitada:\n");
        fprintf(txt, "%s -> %s Lados: %s(DIR) %s(ESQ) Comp: %.2lf VelocM: %.2lf NomeRua: %s\n", getNomeEsquina(eq_from), getNomeEsquina(eq_to), getLDIRRua(r), getLESQRua(r), getComprimentoRua(r), getVelocidadeRua(r), getNomeRUa(r));
    }
    fprintf(txt, "\n");
}

void alag(FILE* svg, FILE* txt, Graph g, SmuTreap t, int n, double x, double y, double w, double h, Lista *arestasN) {
    Lista esquinas_alagadas = criaLista(); // esquinas alagadas

    Retangulo r = criarRetangulo(27, x, y, w, h, "#AA0044", "#AB37C8");
    insertRectSVG(svg, r);

    if(getInfosDentroRegiaoSmuT(t, x, y, w, h, BBinternoRegiao, esquinas_alagadas)) {
        for(Celula p = getInicioLista(esquinas_alagadas); p != NULL; p = getProxCelula(p)) {

            SmuNode atual = getConteudoCelula(p);
            Esquina eq = getInfoSmuT(t, atual);

            Node from = getNode(g, getNomeEsquina(eq));
            
            adjacentEdges(g, from, arestasN[n]);
        }
    }

    desabilitarArestasAlagadas(g, arestasN[n], svg, txt);
}

void dren(FILE *txt, Graph g, int n, Lista *arestasN) {

    for(Celula p = getInicioLista(arestasN[n]); p != NULL; p = getProxCelula(p)) {

        Edge e = getConteudoCelula(p);
        setHabilitadaEdge(g, e, true);

        Node idx_from = getFromNode(g, e);
        Node idx_to = getToNode(g, e);
        
        Esquina eq_from = getNodeInfo(g, idx_from);
        Esquina eq_to = getNodeInfo(g, idx_to);

        Rua r = getEdgeInfo(g, e);

        fprintf(txt, "Aresta Reabilitada:\n");
        fprintf(txt, "%s -> %s Lados: %s(DIR) %s(ESQ) Comp: %.2lf VelocM: %.2lf NomeRua: %s\n", getNomeEsquina(eq_from), getNomeEsquina(eq_to), getLDIRRua(r), getLESQRua(r), getComprimentoRua(r), getVelocidadeRua(r), getNomeRUa(r));
    }
    fprintf(txt, "\n");
}


double extraiComprimento(Rua r) {
    return getComprimentoRua(r);
}

double extraiVelocidade(Rua r) {
    return getComprimentoRua(r)/getVelocidadeRua(r);
}


void inserirPathsPercursos(FILE* txt, Graph g, int *cmc, int *cmr, int tam_cmc, int tam_cmr, Percurso p) {
    fprintf(txt, "Caminho Mais Curto (CMC): ");
    for(int i = 0; i<tam_cmc; i++) {

        printf("%d ", cmc[i]);
        Esquina e = getNodeInfo(g, cmc[i]);

        Coordenadas c = createCoordenadas(getXEsquina(e), getYEsquina(e));
        fprintf(txt, "(%.2lf, %.2lf) ", getXEsquina(e), getYEsquina(e));
        insertPathCMCPercurso(p, c);
    }
    fprintf(txt, "\n");
    printf("\n");

    fprintf(txt, "Caminho Mais Rapido (CMR): ");
    for(int i = 0; i<tam_cmr; i++) {

        Esquina e = getNodeInfo(g, cmr[i]);
        printf("%d (%.2lf, %.2lf)", cmr[i], getXEsquina(e), getYEsquina(e));

        Coordenadas c = createCoordenadas(getXEsquina(e), getYEsquina(e));
        fprintf(txt, "(%.2lf, %.2lf) ", getXEsquina(e), getYEsquina(e));
        insertPathCMRPercurso(p, c);
    }
    printf("\n");
    fprintf(txt, "\n\n");
}


void registrarPercurso(FILE* txt, Graph g, SmuTreap t, HashTable enderecos, HashTable percursos, char *np, char *nome, char *reg1, char *reg2) {
    
    printf("entrada p?\n");
    fprintf(txt, "Percurso %s:\n", np);
    Endereco origem = buscaHashTable(enderecos, reg1);
    Endereco destino = buscaHashTable(enderecos, reg2);

    Esquina e1 = getInfoMaisProximoRaioSmuT(t, getXEndereco(origem), getYEndereco(origem), 50, BBinternoRegiao);
    Esquina e2 = getInfoMaisProximoRaioSmuT(t, getXEndereco(destino), getYEndereco(destino), 50, BBinternoRegiao);

    Percurso p = createPercurso(np, origem, destino);
    insertHashTable(percursos, np, p);


    //printGraph(g, extraiComprimento);

    if(strcmp(nome, "-") == 0) {
        int *cmc = malloc(getTotalNodes(g) * sizeof(int));
        int *cmr = malloc(getTotalNodes(g) * sizeof(int));
        int tam_cmc;
        int tam_cmr; 

        dijkstra(g, getNomeEsquina(e2), getNomeEsquina(e1), cmc, &tam_cmc, extraiComprimento);
        dijkstra(g, getNomeEsquina(e2), getNomeEsquina(e1), cmr, &tam_cmr, extraiVelocidade);

        inserirPathsPercursos(txt, g, cmc, cmr, tam_cmc, tam_cmr, p);
    } 
    else {
        Graph sub = produceGraph(g, nome);

        int *cmc_sub = malloc(getTotalNodes(sub) * sizeof(int));
        int *cmr_sub = malloc(getTotalNodes(sub) * sizeof(int));
        int tam_cmc_sub;
        int tam_cmr_sub;

        dijkstra(sub, getNomeEsquina(e2), getNomeEsquina(e1), cmc_sub, &tam_cmc_sub, extraiComprimento);
        dijkstra(sub, getNomeEsquina(e2), getNomeEsquina(e1), cmr_sub, &tam_cmr_sub, extraiVelocidade);

        inserirPathsPercursos(txt, sub, cmc_sub, cmr_sub, tam_cmc_sub, tam_cmr_sub, p);
    }



    printf("saida p?\n");
}


void join(FILE* txt, Graph g, SmuTreap t, HashTable percursos, char *np, char *np1, char *np2) {

    printf("\nentrou join\n");
    fprintf(txt, "Percurso %s (%s e %s):\n", np, np1, np2);

    Percurso p1 = buscaHashTable(percursos, np1);
    Percurso p2 = buscaHashTable(percursos, np2);

    Endereco end_destino_np1 = getDestinoPercurso(p1);
    Endereco end_origem_np2 = getOrigemPercurso(p2);

    Esquina eq1 = getInfoMaisProximoRaioSmuT(t, getXEndereco(end_destino_np1), getYEndereco(end_destino_np1), 50, BBinternoRegiao);
    Esquina eq2 = getInfoMaisProximoRaioSmuT(t, getXEndereco(end_origem_np2), getYEndereco(end_origem_np2), 50, BBinternoRegiao);

    Percurso p = createPercurso(np, getDestinoPercurso(p1), getOrigemPercurso(p2));
    insertHashTable(percursos, np, p);

    int *cmc = malloc(getTotalNodes(g) * sizeof(int));
    int *cmr = malloc(getTotalNodes(g) * sizeof(int));
    int tam_cmc;
    int tam_cmr;

    dijkstra(g, getNomeEsquina(eq2), getNomeEsquina(eq1), cmc, &tam_cmc, extraiComprimento);
    dijkstra(g, getNomeEsquina(eq2), getNomeEsquina(eq1), cmr, &tam_cmr, extraiVelocidade);

    fprintf(txt, "Caminho Mais Curto (CMC): ");
    for(int i = 0; i<tam_cmc; i++) {

        printf("%d ", cmc[i]);
        Esquina e = getNodeInfo(g, cmc[i]);

        Coordenadas c = createCoordenadas(getXEsquina(e), getYEsquina(e));
        fprintf(txt, "(%.2lf, %.2lf) ", getXEsquina(e), getYEsquina(e));
        insertPathCMCPercurso(p, c);
    }
    printf("\n");
    fprintf(txt, "\n");

    fprintf(txt, "Caminho Mais Curto (CMC): ");
    for(int i = 0; i<tam_cmr; i++) {

        printf("%d ", cmr[i]);
        Esquina e = getNodeInfo(g, cmr[i]);

        Coordenadas c = createCoordenadas(getXEsquina(e), getYEsquina(e));
        fprintf(txt, "(%.2lf, %.2lf) ", getXEsquina(e), getYEsquina(e));
        insertPathCMRPercurso(p, c);
    }
    printf("\n");
    fprintf(txt, "\n\n");
}



void sg(FILE* svg, Graph g, SmuTreap t, char *nome, double x, double y, double w, double h) {
    if(!g || !nome) return;

    Lista internos = criaLista();
    getInfosDentroRegiaoSmuT(t, x, y, w, h, BBinternoRegiao, internos);

    int nVert = getTamanhoLista(internos);
    char **nomesVerts = malloc(nVert * sizeof(char*));
    for(int i = 0; i<nVert; i++) {
        nomesVerts[i] = malloc(100*sizeof(char));
    }

    int i = 0;
    for(Celula p = getInicioLista(internos); p!=NULL; p = getProxCelula(p)) {

        SmuNode smu = getConteudoCelula(p);
        Esquina e = getInfoSmuT(t, smu);

        strcpy(nomesVerts[i], getNomeEsquina(e));

        i++;
    }

    createSubgraphDG(g, nome, nomesVerts, nVert, getDirected(g));
    Linha l1 = criarLinha(27, x, y, x+w, y, "red", true);
    Linha l2 = criarLinha(27, x, y, x, y+h, "red", true);
    Linha l3 = criarLinha(27, x+w, y, x+w, y+h, "red", true);
    Linha l4 = criarLinha(27, x, y+h, x+w, y+h, "red", true);
    setSWLinha(l1, 5); setSWLinha(l2, 5); setSWLinha(l3, 5); setSWLinha(l4, 5);
    insertLineSVG(svg, l1);
    insertLineSVG(svg, l2);
    insertLineSVG(svg, l3);
    insertLineSVG(svg, l4);
}

