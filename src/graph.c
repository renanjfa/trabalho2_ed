#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "hash_table.h"


typedef struct stVertex {
    char *nome;
    Info dados; // Quadra: nome, cep, ancx, ancy
    double x, y;
    bool adicionado;

    Lista adjacentes; // Lista de Edges
} stVertex;

typedef stVertex* Vertex;

typedef struct stGraph {
    int maxNodes;
    int totalNodes;
    int totalEdges;
    bool directed;

    Vertex *vertices; // vetor de vertices
    Lista edges;
    
    // hash table: nomes -> indice subgrafos

} stGraph;

typedef struct stEdge {

    Node from;
    Node to;
    Info dados; // Informacao Rua: nome, velocidade, comp, ldir, lesq

} stEdge;


Graph createGraph(int nVert, bool directed) {
    stGraph *g = malloc(sizeof(stGraph));
    
    g->directed = directed;
    g->maxNodes = nVert;
    g->totalEdges = 0;
    g->totalNodes = 0;

    g->vertices = malloc(nVert * sizeof(Vertex));
    for(int i = 0; i < nVert; i++) {
        g->vertices[i] = malloc(sizeof(stVertex));
        g->vertices[i]->adjacentes = criaLista();
        g->vertices[i]->adicionado = false;
        g->vertices[i]->nome = NULL;
        g->vertices[i]->dados = NULL;
        g->vertices[i]->x = g->vertices[i]->y = 0.0;
    }

    g->edges = criaLista();

    return ((stGraph*)g);
}


int getMaxNodes(Graph g) {
    return ((stGraph*)g)->maxNodes;
}

int getTotalNodes(Graph g) {
    return ((stGraph*)g)->totalNodes;
}

int getTotalEdges(Graph g) {
    return ((stGraph*)g)->totalEdges;
}

bool getDirected(Graph g) {
    return ((stGraph*)g)->directed;
}





Node getFromNode(Graph g, Edge e) {
    return ((stEdge*)e)->from;
}


Node getToNode(Graph g, Edge e) {
    return ((stEdge*)e)->to;
}


Edge getEdge(Graph g, Node from, Node to) {
    if(!g) return NULL;

    Celula inicio = getInicioLista(((stGraph*)g)->vertices[from]->adjacentes);

    for(Celula p = inicio; p != NULL; p = getProxCelula(p)) {
        Edge e = getConteudoCelula(p);

        Node atual = getToNode(g, e);
        if(atual == to)
            return ((stEdge*)e);
    }
    return NULL;
}


Info getEdgeInfo(Graph g, Edge e) {
    return ((stEdge*)e)->dados; 
}


void setEdgeInfo(Graph g, Edge e, Info info) {
    ((stEdge*)e)->dados = info;
}


Edge addEdge(Graph g, Node from, Node to, Info info) {
    if(!g || !info) return NULL;

    
    stEdge *new_edge = malloc(sizeof(stEdge));

    new_edge->from = from;
    new_edge->to = to;
    new_edge->dados = info;

    // fazer verificacao se o node esta adicionado ou nao para adicionar edge
    insereLista(((stGraph*)g)->vertices[from]->adjacentes, new_edge);
    insereLista(((stGraph*)g)->edges, new_edge);
    ((stGraph*)g)->totalEdges++;


    if(!((stGraph*)g)->directed) {
       stEdge *reverse_edge = malloc(sizeof(stEdge));
       reverse_edge->from = to;
       reverse_edge->to = from;
       reverse_edge->dados = info; 

       // fazer verificacao se o node esta adicionado ou nao para adicionar edge
        insereLista(((stGraph*)g)->vertices[to]->adjacentes, reverse_edge);
        insereLista(((stGraph*)g)->edges, reverse_edge);
        ((stGraph*)g)->totalEdges++;

    }

    return new_edge;
}

void removeEdge(Graph g, Edge e) {
    if(!g || !e) return;

    Node from = getFromNode(g, e);

    Celula anterior = NULL;
    Celula inicio = getInicioLista(((stGraph*)g)->vertices[from]->adjacentes);
    for(Celula p = inicio; p != NULL; p = getProxCelula(p)) {

        Node to_p = getToNode(g, getConteudoCelula(p));
        if(to_p == getToNode(g, e)) {
            removeCelula(((stGraph*)g)->vertices[from]->adjacentes, p, anterior);
            return;
        }

        anterior = p;
    }
}


bool isAdjacent(Graph g, Node from, Node to) {
    if(!g) return false;

    Celula inicio = getInicioLista(((stGraph*)g)->vertices[from]->adjacentes);

    for(Celula p = inicio; p != NULL; p = getProxCelula(p)) {
        Edge atual = getConteudoCelula(p);
        Node to_atual = getToNode(g, atual);

        if(to_atual == to) 
            return true;
    }

    return false;
}

void adjacentNodes(Graph g, Node node, Lista nosAdjacentes) {
    if(!g || !nosAdjacentes) return;

    Celula inicio = getInicioLista(((stGraph*)g)->vertices[node]->adjacentes);

    for(Celula p = inicio; p != NULL; p = getProxCelula(p)) {
        Edge atual = getConteudoCelula(p);
        Node to_atual = getToNode(g, atual);

        insereLista(nosAdjacentes, to_atual);
          
    }
}


void adjacentEdges(Graph g, Node node, Lista arestasAdjacentes) {
    if(!g || !arestasAdjacentes) return;

    Celula inicio = getInicioLista(((stGraph*)g)->vertices[node]->adjacentes);

    for(Celula p = inicio; p != NULL; p = getProxCelula(p)) {
        Edge atual = getConteudoCelula(p);

        insereLista(arestasAdjacentes, atual);
    }

}

void getEdges(Graph g, Lista arestas) {
    if(!g || !arestas) return;

    Celula inicio = getInicioLista(((stGraph*)g)->edges);
    for(Celula p = inicio; p != NULL; p = getProxCelula(p)) {
        Edge atual = getConteudoCelula(p);

        insereLista(arestas, atual);
    }
}


Info getNodeInfo(Graph g, Node node) {
    return ((stGraph*)g)->vertices[node]->dados;
}

char* getNodeName(Graph g, Node node) {
    return ((stGraph*)g)->vertices[node]->nome;
}

void setNodeInfo(Graph g, Node node, Info info) {
    ((stGraph*)g)->vertices[node]->dados = info;
}


void  getNodeNames(Graph g, Lista nomesNodes) {
    if(!g || !nomesNodes) return;

    for(int i = 0; i < getMaxNodes(g); i++) {
        Vertex aux = ((stGraph*)g)->vertices[i];

        insereLista(nomesNodes, aux->nome);
    }
    
}

Node getNode(Graph g, char *nome) {
    if(!g || !nome) return;

    int nVert = getMaxNodes(g); 

    return hash(nome, nVert);
}

Node addNode(Graph g, char *nome, Info info) {
    if(!g || !nome || !info) return;

    Node indice = hash(nome, getMaxNodes(g));

    ((stGraph*)g)->vertices[indice]->adicionado = true;

    strcpy(((stGraph*)g)->vertices[indice]->nome, nome);
    setNodeInfo(g, indice, info);
    // coordenadas 

    return indice;
}






    








