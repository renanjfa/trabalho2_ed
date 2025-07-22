#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "graph.h"
#include "hash_table.h"
#include "minheap.h"


typedef struct stVertex {
    char *nome;
    double x, y;
    Info dados; 
    bool adicionado;

    Lista adjacentes; // Lista de Edges
} stVertex;

typedef stVertex* Vertex;

typedef struct stGraph {
    char *nome;
    int maxNodes;
    int totalNodes;
    int totalEdges;
    int proxID;
    bool directed;

    Vertex *vertices; // vetor de vertices[]
    
    HashTable subgrafos;   
    HashTable nomesToNodes;

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
    g->proxID = 0;

    int capacidadeAlocada = nVert;
    g->vertices = calloc(capacidadeAlocada, sizeof(Vertex));
    if (!g->vertices) {
        fprintf(stderr, "Erro ao alocar vetor de vértices.\n");
        exit(1);
    }

    // Inicializa cada vértice
    for (int i = 0; i < nVert; i++) {
        g->vertices[i] = calloc(1, sizeof(stVertex));
        if (!g->vertices[i]) {
            fprintf(stderr, "Erro ao alocar vértice %d.\n", i);
            exit(1);
        }

        g->vertices[i]->adjacentes = criaLista();  // lista de adjacência
        g->vertices[i]->adicionado = false;
        g->vertices[i]->nome = NULL;
        g->vertices[i]->dados = NULL;
        g->vertices[i]->x = g->vertices[i]->y = -1.0;
    }

    
    g->subgrafos = createHashTable(100);
    g->nomesToNodes = createHashTable(nVert);

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



void getNodeCoordinates(Graph g, Node node, double *x, double *y) {
    *x = ((stGraph*)g)->vertices[node]->x;
    *y = ((stGraph*)g)->vertices[node]->y;
}




Node getFromNode(Graph g, Edge e) {
    (void)g;
    return ((stEdge*)e)->from;
}


Node getToNode(Graph g, Edge e) {
    (void)g;
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
    (void)g;
    return ((stEdge*)e)->dados; 
}

bool isHabilitadaEdge(Graph g, Edge e) {
    (void)g;
    return ((stEdge*)e)->habilitado;
}

void setHabilitadaEdge(Graph g, Edge e, bool new_state) {
    (void)g;
    ((stEdge*)e)->habilitado = new_state;
}



void setEdgeInfo(Graph g, Edge e, Info info) {
    (void)g;
    ((stEdge*)e)->dados = info;
}

// fazer verificacao se o vertice from ou to existem
Edge addEdge(Graph g, Node from, Node to, Info info) {
    if (!g || !info) return NULL;

    stGraph* graph = (stGraph*)g;
    int total = graph->totalNodes;

    if (from < 0 || from >= total || to < 0 || to >= total) {
        fprintf(stderr, "addEdge: Índice de nó inválido: from=%d, to=%d\n", from, to);
        return NULL;
    }

    if (!graph->vertices[from] || !graph->vertices[to]) {
        fprintf(stderr, "addEdge: Vértices from ou to não existem no grafo.\n");
        return NULL;
    }

    stEdge *new_edge = malloc(sizeof(stEdge));
    new_edge->from = from;
    new_edge->to = to;
    new_edge->dados = info;
    new_edge->habilitado = true;

    insereLista(graph->vertices[from]->adjacentes, new_edge);
    graph->totalEdges++;

    if (!graph->directed) {
        stEdge *reverse_edge = malloc(sizeof(stEdge));
        reverse_edge->from = to;
        reverse_edge->to = from;
        reverse_edge->dados = info; // ou duplicar com copiaInfo(info)
        reverse_edge->habilitado = true;

        insereLista(graph->vertices[to]->adjacentes, reverse_edge);
        graph->totalEdges++;
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

Node addNode(Graph g, char *nome, double x, double y, Info info) {
    if (!g || !nome || !info) return -1;

    // Garante que nome válido
    Node idx = getOrCreateNode(((stGraph*)g)->nomesToNodes, nome, &((stGraph*)g)->proxID);

    // Verifica se o índice está dentro do limite
    if (idx < 0 || idx >= ((stGraph*)g)->maxNodes) {
        fprintf(stderr, "Erro: índice %d fora do limite da capacidade (%d).\n", idx, ((stGraph*)g)->maxNodes);
        exit(1);
    }

    // Aloca vértice se necessário
    if (((stGraph*)g)->vertices[idx] == NULL) {
        ((stGraph*)g)->vertices[idx] = calloc(1, sizeof(struct stVertex));
        if (!((stGraph*)g)->vertices[idx]) {
            fprintf(stderr, "Erro ao alocar struct stVertex.\n");
            exit(1);
        }
    }

    // Marca como adicionado
    ((stGraph*)g)->vertices[idx]->adicionado = true;

    // Copia nome
    ((stGraph*)g)->vertices[idx]->nome = malloc(strlen(nome) + 1);
    if (!((stGraph*)g)->vertices[idx]->nome) {
        fprintf(stderr, "Erro ao alocar nome do vértice.\n");
        exit(1);
    }
    strcpy(((stGraph*)g)->vertices[idx]->nome, nome);

    // Atribui info
    ((stGraph*)g)->vertices[idx]->x = x;
    ((stGraph*)g)->vertices[idx]->y = y;

    setNodeInfo(g, idx, info);

    // Atualiza total
    ((stGraph*)g)->totalNodes++;

    return idx;
}


void dijkstra(Graph g, char *nomeOrigem, char *nomeDestino, int* caminho, int* tamCaminho, FuncCusto extraiPeso) {
    if(!g || !caminho) return;

    int n = getTotalNodes(g);
    int MAX = getMaxNodes(g);
    printf("N: %d\nMAX: %d\n", n, MAX);
    if(n<=0) return;
    double* dist = malloc(n * sizeof(double));
    double* distHeuristica = malloc(n * sizeof(double)); // Distância + Distância Euclidiana
    int* anterior = malloc(n * sizeof(int));

    // Obter coordenadas do destino para cálculo da distância euclidiana
    Node destino = getNode(g, nomeDestino);
    double xDest = 0, yDest = 0;
    getNodeCoordinates(g, destino, &xDest, &yDest);

    printf("DIJK passagem coords\n");

    for (int i = 0; i < n; i++) {
        dist[i] = DBL_MAX;
        distHeuristica[i] = DBL_MAX;
        anterior[i] = -1;
    }

    Node origem = getNode(g, nomeOrigem);

    // Calcular distancia euclidiana para o nó de origem
    double xOrig, yOrig;
    getNodeCoordinates(g, origem, &xOrig, &yOrig);
    double heuristicaOrig = sqrt(pow(xOrig - xDest, 2) + pow(yOrig - yDest, 2));

    MinHeap heap = createMinHeap(n);
    dist[origem] = 0.0;
    distHeuristica[origem] = heuristicaOrig; // dist euclidiana para priorização
    insertMinHeap(heap, origem, distHeuristica[origem]);
    
    printf("antes do loop\n");

    if(!heap) printf("HEAP NULA\n");

    while (!isMinHeapEmpty(heap)) {
        int u = extractMinV(heap);
        
        // se chegar no destino, encerrar mais cedo
        if (u == destino) {
            break;
        }

        for (Celula p = getInicioLista( ((stGraph*)g)->vertices[u]->adjacentes ); p != NULL; p = getProxCelula(p)) {
            Edge e = getConteudoCelula(p);
            if(isHabilitadaEdge(g, e)) {
                Node v = getToNode(g, e);
                double peso = extraiPeso(getEdgeInfo(g, e)); 
                
                if (dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso;
                    anterior[v] = u;
                    
                    // Calcular Dist Euclidiana para o nó adjacente
                    double xV, yV;
                    getNodeCoordinates(g, v, &xV, &yV);
                    double heuristicaV = sqrt(pow(xV - xDest, 2) + pow(yV - yDest, 2));
                    
                    // Distância euclidiana = distância real + dist euclidiana
                    distHeuristica[v] = dist[v] + heuristicaV;
                    
                    if (estaNaHeap(heap, v)) {
                        atualizaMinHeap(heap, v, distHeuristica[v]);
                    } else {
                        insertMinHeap(heap, v, distHeuristica[v]);
                    }
                }
            }
        }
    }

    // Reconstruir caminho
    int atual = destino;
    int stack[n];
    int topo = 0;

    while (atual != -1) {
        stack[topo++] = atual;
        atual = anterior[atual];
    }

    // Inverter para colocar na ordem correta
    *tamCaminho = topo;
    for (int i = 0; i < topo; i++)
        caminho[i] = stack[topo - i - 1];

    free(dist);
    free(distHeuristica);
    free(anterior);
    free(heap);
}

/*
 **********************
    SUB-GRAFOS
 **********************
*/

void createSubgraphDG(Graph g, char *nomeSubgrafo, char *nomesVerts[], int nVert, bool comArestas) {
    if(!g || !nomeSubgrafo || !nomesVerts || nVert <= 0) return;
    printf("nVerts: %d\n", nVert);

    Graph sub = createGraph(nVert, true, nomeSubgrafo);
    if(!sub) return; 
    
    insertHashTable(((stGraph*)g)->subgrafos, nomeSubgrafo, sub);

    HashTable presentes = createHashTable(nVert+100);
    if(!presentes) {
        printf("Erro na criacao HashTable presentes!!\n");
        return;
    }

    // verifica se todos os vértices existem no grafo original
    for (int i = 0; i < nVert; i++) {
        Node node = getNode(g, nomesVerts[i]);
        if(node == -1) {
            destroiHashTable(presentes);
            return;
        }
    }

    // Adiciona vértices ao subgrafo
    for (int i = 0; i < nVert; i++) {
        Node node = getNode(g, nomesVerts[i]);
        if(node == -1)
            printf("ERRO: vértice '%s' não encontrado no grafo original!\n", nomesVerts[i]);
        Info info = getNodeInfo(g, node);
        if (!info) printf("Info do Node isolado '%s' é NULL!\n", nomesVerts[i]);

        double x = -1.0;
        double y = -1.0;
        getNodeCoordinates(g, node, &x, &y);

        addNode(sub, nomesVerts[i], x, y, info);
        insertHashTable(presentes, nomesVerts[i], node);
    }

    printf("TOTAL NODES CREATESUB: %d\n", getTotalNodes(sub));

    if(comArestas) { 
        for (int i = 0; i < nVert; i++) {
            Node origem = getNode(g, nomesVerts[i]);
            if(!origem) continue;

            Lista adj = criaLista();

            adjacentEdges(g, origem, adj);

            for (Celula c = getInicioLista(adj); c != NULL; c = getProxCelula(c)) {
                Edge e = getConteudoCelula(c);
                Node destino = getToNode(g, e);
                char* nomeDestino = getNodeName(g, destino);

                // verifica apenas se o destino está no subgrafo
                if (buscaHashTable(presentes, nomeDestino)) {
                    Node from = getNode(sub, nomesVerts[i]);
                    Node to = getNode(sub, nomeDestino);

                    if(from && to) {
                        addEdge(sub, from, to, getEdgeInfo(g, e));
                    }
                }
            }
            liberaLista(adj); 
        }
    }

    destroiHashTable(presentes);
}



// Edge includeEdgeSDG(Graph g, char *nomeSubgrafo, Edge e) {
//     if(!g || !nomeSubgrafo || !e) return;

//     int idx_subgraph = (int)buscaHashTable(((stGraph*)g)->nomesToSubgraphs, nomeSubgrafo);

//     Graph sub = ((stGraph*)g)->subgrafos[idx_subgraph];

//     Node from = getFromNode(g, e);
//     Node to = getToNode(g, e);
//     Info info = getEdgeInfo(g, e);

//     Edge new_edge = addEdge(g, from, to, info);
//     return new_edge;
// }

// void excludeEdgeSDG(Graph g, char *nomeSubgrafo, Edge e) {
//     if(!g || !nomeSubgrafo || !e) return;

//     int idx_subgraph = (int)buscaHashTable(((stGraph*)g)->nomesToSubgraphs, nomeSubgrafo);

//     Graph sub = ((stGraph*)g)->subgrafos[idx_subgraph];

//     Node from = getFromNode(g, e);

//     Celula anterior = NULL;
//     Celula inicio = getInicioLista(((stGraph*)sub)->vertices[from]->adjacentes);
//     for(Celula p = inicio; p != NULL; p = getProxCelula(p)) {

//         Node to_p = getToNode(g, getConteudoCelula(p));
//         if(to_p == getToNode(g, e)) {
//             removeCelula(((stGraph*)g)->vertices[from]->adjacentes, p, anterior);
//             return;
//         }

//         anterior = p;
//     }
// }

Graph produceGraph(Graph g, char *nomeSubgrafo) {
    if(!g || !nomeSubgrafo) return NULL;

    return buscaHashTable(((stGraph*)g)->subgrafos, nomeSubgrafo);
}


