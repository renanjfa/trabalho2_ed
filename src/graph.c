#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "graph.h"
#include "hash_table.h"


typedef struct stVertex {
    char *nome;
    Info dados; // Quadra: nome, cep, ancx, ancy
    bool adicionado;

    Lista adjacentes; // Lista de Edges
} stVertex;

typedef stVertex* Vertex;

typedef struct stGraph {
    char *nome;
    int maxNodes;
    int totalNodes;
    int totalEdges;
    bool directed;

    Vertex *vertices; // vetor de vertices[]
    Lista edges;
    Graph *subgrafos;   // vetor de subgrafos[]

    HashTable nomesToNodes;
    HashTable nomesToSubgraphs;

} stGraph;

typedef struct stEdge {
    Node from;
    Node to;
    Info dados; // Informacao Rua: nome, velocidade, comp, ldir, lesq
    bool habilitado;

} stEdge;


Graph createGraph(int nVert, bool directed, char *nome) {
    stGraph *g = malloc(sizeof(stGraph));

    g->nome = (char*)malloc(strlen(nome)+1);
    if(g->nome == NULL) {
        printf("Erro na alocacao do nome do grafo.\n");
        exit(1);
    }
    strcpy(g->nome, nome);

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
    }

    // revisar 
    g->subgrafos = NULL;
    

    g->nomesToNodes = createHashTable(nVert);
    g->nomesToSubgraphs = createHashTable(100);
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

bool isHabilitadaEdge(Graph g, Edge e) {
    return ((stEdge*)e)->habilitado;
}

void setHabilitadaEdge(Graph g, Edge e, bool new_state) {
    ((stEdge*)e)->habilitado = new_state;
}



void setEdgeInfo(Graph g, Edge e, Info info) {
    ((stEdge*)e)->dados = info;
}

// fazer verificacao se o vertice from ou to existem
Edge addEdge(Graph g, Node from, Node to, Info info) {
    if(!g || !info) return NULL;

    
    stEdge *new_edge = malloc(sizeof(stEdge));

    new_edge->from = from;
    new_edge->to = to;
    new_edge->dados = info;
    new_edge->habilitado = true;

    // fazer verificacao se o node esta adicionado ou nao para adicionar edge
    insereLista(((stGraph*)g)->vertices[from]->adjacentes, new_edge);
    insereLista(((stGraph*)g)->edges, new_edge);
    ((stGraph*)g)->totalEdges++;


    if(!((stGraph*)g)->directed) {
       stEdge *reverse_edge = malloc(sizeof(stEdge));
       reverse_edge->from = to;
       reverse_edge->to = from;
       reverse_edge->dados = info; 
       reverse_edge->habilitado = true;

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

        //insereLista(nosAdjacentes, to_atual);
          
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



void getEdgesAux(Graph g, Lista arestas, Lista adj) {
    if(!g || !arestas) return;

    for(Celula p = getInicioLista(adj); p != NULL; p = getProxCelula(p)) {
        Edge atual = getConteudoCelula(p);

        insereLista(arestas, atual);
    }
}


void getEdges(Graph g, Lista arestas) {
    if(!g || !arestas) return;

    int tamanho = ((stGraph*)g)->maxNodes;
    for(int i = 0; i<tamanho; i++) {
        if(((stGraph*)g)->vertices[i]->adicionado) {
            getEdgesAux(g, arestas, ((stGraph*)g)->vertices[i]->adjacentes);
        }
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
    if(!g || !nome) return -1;

    Node idx = (Node)buscaHashTable(((stGraph*)g)->nomesToNodes, nome);

    return idx;
}

Node addNode(Graph g, char *nome, Info info) {
    if(!g || !nome || !info) return -1;

    int proxID = 0;
    Node idx = getOrCreateNode( ((stGraph*)g)->nomesToNodes, nome, &proxID);

    ((stGraph*)g)->vertices[idx]->adicionado = true;

    ((stGraph*)g)->vertices[idx]->nome = (char*)malloc(strlen(nome)+1);
    if(((stGraph*)g)->vertices[idx]->nome == NULL) {
        printf("Erro na alocacao do nome do grafo.\n");
        exit(1);
    }
    strcpy(((stGraph*)g)->vertices[idx]->nome, nome);

    setNodeInfo(g, idx, info);

    ((stGraph*)g)->totalNodes++;
}



// double* dijkstraA(Graph g, Node inicio, Node destino, int **predecessores, FuncCusto calcularCusto) {
//     int n = getMaxNodes(g);

//     double* dist = malloc(n * sizeof(double));
//     bool* visitado = calloc(n, sizeof(bool));
//     *predecessores = malloc(n * sizeof(int));

//     for (int i = 0; i < n; i++) {
//         dist[i] = DBL_MAX;
//         (*predecessores)[i] = -1;
//     }

//     dist[inicio] = 0.0;

//     while (true) {
//         // menor não visitado
//         double menor = DBL_MAX;
//         Node u = -1;
//         for (int i = 0; i < n; i++) {
//             if (!visitado[i] && dist[i] < menor) {
//                 menor = dist[i];
//                 u = i;
//             }
//         }

//         if (u == -1 || u == destino) break;

//         visitado[u] = true;

//         Lista adj = criaLista();
//         adjacentEdges(g, u, adj);

//         for (Celula c = getInicioLista(adj); c != NULL; c = getProxCelula(c)) {
//             Edge e = getConteudoCelula(c);
//             Node v = getToNode(g, e);

//             double peso = calcularCusto(getEdgeInfo(g, e));
//             if (!visitado[v] && dist[u] + peso < dist[v]) {
//                 dist[v] = dist[u] + peso;
//                 (*predecessores)[v] = u;
//             }
//         }

//         liberaLista(adj);
//     }

//     free(visitado);
//     return dist;
// }
