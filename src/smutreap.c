#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "smutreap.h"
#include "boundingbox.h"
#include "lista.h"
#include "svg.h"

typedef struct ancora {
    double x, y;
} Ancora;

typedef struct stNode {
    Ancora anc;
    int priori;
    int promotionCount;
    Info info;
    DescritorTipoInfo d;
    Info bbinfo;
    Info bbsub;
    struct stNode *esq; 
    struct stNode *dir;
    struct stNode *pai;
} stNode;

typedef struct stSmuTreap { 
    int hitCount;
    double promotionRate;
    double epsilon;
    int prioMax;
    Node *raiz; 
} stSmuTreap;

SmuTreap newSmuTreap(int hitCount, double promotionRate, double epsilon, int prioMax) {
    stSmuTreap *smu = malloc(sizeof(stSmuTreap));
    smu->hitCount = hitCount;
    smu->promotionRate = promotionRate;
    smu->epsilon = epsilon;
    smu->raiz = NULL;
    smu->prioMax = prioMax;
    return ((stSmuTreap*)smu);
}

Node criarNode(double x, double y, Info info, DescritorTipoInfo d, FCalculaBoundingBox calcBB, Node pai, int priori) {

    stNode *new = malloc(sizeof(stNode));

    new->anc.x = x; new->anc.y = y; // ancoras
    new->priori = priori;    // prioridade aleatoria
    new->promotionCount = 0;   // promotionCount
    new->info = info;   // forma(info)
    new->d = d;   // descritor
    new->esq = NULL; new->dir = NULL;  // ponteiros filhos NULL
    new->pai = pai;    // pai passado por insertSmuTreapAux

    double xbb, ybb, wbb, hbb;
    calcBB(info, &xbb, &ybb, &wbb, &hbb);
    new->bbinfo = criarBB(xbb, ybb, wbb, hbb);
    new->bbsub = criarBB(xbb, ybb, wbb, hbb);

    return ((stNode*)new);
}

void uniaoGeralBoundingBox(Node r) {
    if(((stNode*)r)->esq == NULL && ((stNode*)r)->dir == NULL) 
        uniaoBBSemFilhos(((stNode*)r)->bbsub, ((stNode*)r)->bbinfo);
    else if(((stNode*)r)->esq == NULL && ((stNode*)r)->dir != NULL)
        uniaoBBDireita(((stNode*)r)->bbsub, ((stNode*)r)->dir->bbsub);
    else if(((stNode*)r)->esq != NULL && ((stNode*)r)->dir == NULL)
        uniaoBBEsquerda(((stNode*)r)->bbsub, ((stNode*)r)->esq->bbsub);
    else    
        uniaoBBAmbosFilhos(((stNode*)r)->bbsub, ((stNode*)r)->bbinfo, ((stNode*)r)->esq->bbsub, ((stNode*)r)->dir->bbsub);
} 

Node rotacionaDireita(Node r) {
    Node v = ((stNode*)r)->esq;
    if (!v) return r;  
    
    Node acertobb = ((stNode*)v)->dir;
    bool acerto = false;
    
    if(((stNode*)v)->esq != NULL && ((stNode*)v)->dir != NULL) 
        acerto = true;

    // ação de rotação
    ((stNode*)r)->esq = ((stNode*)v)->dir;
    if (((stNode*)v)->dir) ((stNode*)v)->dir->pai = r;
    
    ((stNode*)v)->dir = r;
    
    // atualização pai
    ((stNode*)v)->pai = ((stNode*)r)->pai;
    ((stNode*)r)->pai = v;

    // atualização do ponteiro do pai do antigo nó u
    if (((stNode*)v)->pai) {
        if (((stNode*)v)->pai->esq == r) 
            ((stNode*)v)->pai->esq = v;
        else if (((stNode*)v)->pai->dir == r) 
            ((stNode*)v)->pai->dir = v;
    }
    
    uniaoGeralBoundingBox(r);
    if(acerto) uniaoGeralBoundingBox(acertobb);
    return v; 
}

Node rotacionaEsquerda(Node r) {
    Node v = ((stNode*)r)->dir;
    if(!v) return r;
    
    Node acertobb = ((stNode*)v)->esq;
    bool acerto = false;

    if(((stNode*)v)->esq != NULL && ((stNode*)v)->dir != NULL) 
        acerto = true;

    // ação de rotação
    ((stNode*)r)->dir = ((stNode*)v)->esq;
    if (((stNode*)v)->esq) ((stNode*)v)->esq->pai = r;

    ((stNode*)v)->esq = r;

    // atualização pai
    ((stNode*)v)->pai = ((stNode*)r)->pai;
    ((stNode*)r)->pai = v;

    // atualização do ponteiro do pai do antigo nó u
    if (((stNode*)v)->pai) {
        if (((stNode*)v)->pai->esq == r) 
            ((stNode*)v)->pai->esq = v;
        else if (((stNode*)v)->pai->dir == r) 
            ((stNode*)v)->pai->dir = v;
    }

    uniaoGeralBoundingBox(r);
    if(acerto) uniaoGeralBoundingBox(acertobb);
    return v;
}



Node insertSmuTAux(SmuTreap t, Node r, double x, double y, Info i, DescritorTipoInfo d, FCalculaBoundingBox f, Node pai, int priori) {
    Node paidef = pai;
    if(r == NULL) {
        return criarNode(x, y, i, d, f, paidef, priori);
    }

    if(x < ((stNode*)r)->anc.x) {
        ((stNode*)r)->esq = insertSmuTAux(t, ((stNode*)r)->esq, x, y, i, d, f, r, priori);
        if( ((stNode*)r)->priori < ((stNode*)r)->esq->priori  &&  ((stNode*)r)->esq != NULL) {
            r = rotacionaDireita(r);
        }
    } 
    else {
        ((stNode*)r)->dir = insertSmuTAux(t, ((stNode*)r)->dir, x, y, i, d, f, r, priori);
        if( ((stNode*)r)->priori < ((stNode*)r)->dir->priori  &&  ((stNode*)r)->dir != NULL) {
            r = rotacionaEsquerda(r);
        }
    }

    uniaoGeralBoundingBox(r);
        
    return r;
}

int prioriAleatoria(int prioMax) {
    static int initialized = 0;
    if (!initialized) {
        srand(time(NULL));
        initialized = 1;
    }
    return rand() % prioMax;
}

Node insertSmuT(SmuTreap t, double x, double y, Info i, DescritorTipoInfo d, FCalculaBoundingBox f) {
    if(t == NULL) return NULL;
    Node pai = NULL;
    int priori = prioriAleatoria(((stSmuTreap*)t)->prioMax);
    ((stSmuTreap*)t)->raiz = insertSmuTAux(t, ((stSmuTreap*)t)->raiz, x, y, i, d, f, pai, priori);
    return ((stSmuTreap*)t)->raiz;
}

Node rebalanceiaSmuTreap(Node root) {
    if (!root) return NULL;

    if ( ((stNode*)root)->esq && ((stNode*)root)->esq->priori > ((stNode*)root)->priori) {
        root = rotacionaDireita(root);
        ((stNode*)root)->dir = rebalanceiaSmuTreap(((stNode*)root)->dir);  // continua caso tenha mais promoções pendentes
    }
    else if ( ((stNode*)root)->dir && ((stNode*)root)->dir->priori > ((stNode*)root)->priori) {
        root = rotacionaEsquerda(root);
        ((stNode*)root)->esq = rebalanceiaSmuTreap(((stNode*)root)->esq);  // continua caso tenha mais promoções pendentes
    }

    return root;
}

Node RebalanceFromRoot(Node r) {
    if(r==NULL) return NULL;
    
    ((stNode*)r)->esq = RebalanceFromRoot(((stNode*)r)->esq);
    ((stNode*)r)->dir = RebalanceFromRoot(((stNode*)r)->dir);
    r = rebalanceiaSmuTreap(r);
    uniaoGeralBoundingBox(r);
    return r;
}


void removeNoSmuT(SmuTreap t, Node no) {
    if (no == NULL) return;

    // Caso do no ser uma folha
    if (((stNode*)no)->esq == NULL && ((stNode*)no)->dir == NULL) {
        Node pai = ((stNode*)no)->pai;

        if (pai != NULL) {
            if (((stNode*)pai)->dir == no) {
                ((stNode*)pai)->dir = NULL;
            } else if (((stNode*)pai)->esq == no) {
                ((stNode*)pai)->esq = NULL;
            }
        } else {
            // O nó é a raiz da árvore
            ((stSmuTreap*)t)->raiz = NULL;
        }

        free(no);
    }


    // Caso de um filho
    else if (((stNode*)no)->esq == NULL || ((stNode*)no)->dir == NULL) {
        Node pai = ((stNode*)no)->pai;
        Node filho = (((stNode*)no)->esq != NULL) ? ((stNode*)no)->esq : ((stNode*)no)->dir;

        if (pai != NULL) {
            if (((stNode*)pai)->esq == no) {
                ((stNode*)pai)->esq = filho;
            } else {
                ((stNode*)pai)->dir = filho;
            }
        } else {
            ((stSmuTreap*)t)->raiz = filho;
        }

        ((stNode*)filho)->pai = pai;
        free(no);
    }

    // Caso de no com dois filhos
    else {
        Node sucessor;
        if (((stNode*)no)->esq->priori > ((stNode*)no)->dir->priori) {
            sucessor = ((stNode*)no)->esq;
            while (((stNode*)sucessor)->dir != NULL) {
                sucessor = ((stNode*)sucessor)->dir;

            }
        } else {
            sucessor = ((stNode*)no)->dir;
            while (((stNode*)sucessor)->esq != NULL) {
                sucessor = ((stNode*)sucessor)->esq;
            }
        }
        
        ((stNode*)no)->anc.x = ((stNode*)sucessor)->anc.x;
        ((stNode*)no)->anc.y = ((stNode*)sucessor)->anc.y;
        ((stNode*)no)->info = ((stNode*)sucessor)->info;
        ((stNode*)no)->bbinfo = ((stNode*)sucessor)->bbinfo;
        ((stNode*)no)->d = ((stNode*)sucessor)->d;
        ((stNode*)no)->priori = ((stNode*)sucessor)->priori;
        ((stNode*)no)->promotionCount = ((stNode*)sucessor)->promotionCount;

        removeNoSmuT(t, sucessor);
    }
}

void visitaProfundidadeAux(SmuTreap t, Node r, FvisitaNo f, void *aux) {
    if(r == NULL) return;

    f(r, ((stNode*)r)->info, ((stNode*)r)->anc.x, ((stNode*)r)->anc.y, aux);

    visitaProfundidadeAux(t, ((stNode*)r)->esq, f, aux);
    visitaProfundidadeAux(t, ((stNode*)r)->dir, f, aux);
}

void visitaProfundidadeSmuT(SmuTreap t, FvisitaNo f, void *aux) {
    if(!t) return;
    visitaProfundidadeAux(t, ((stSmuTreap*)t)->raiz, f, aux);
}

void promoteNodeSmuT(SmuTreap t, Node n, double promotionRate) {
    if(!t || !n) return;
    
    ((stNode*)n)->priori = ((stNode*)n)->priori * promotionRate;
    ((stNode*)n)->promotionCount = 0;
    
    if(((stNode*)n)->priori > ((stNode*)n)->pai->priori) {
        ((stSmuTreap*)t)->raiz = RebalanceFromRoot(((stSmuTreap*)t)->raiz);
    }   
}

Node getNodeSmuTAux(SmuTreap t, Node r, double x, double y, int *promotion) {
    if (r == NULL) {
        printf("Nao existe node com estas coordenadas!!\n");
        return NULL;
    }
    
    double epsilon = ((stSmuTreap*)t)->epsilon;
    if ( fabs(((stNode*)r)->anc.x - x) < epsilon && fabs(((stNode*)r)->anc.y - y) < epsilon ) {
        ((stNode*)r)->promotionCount++;
        if (((stNode*)r)->promotionCount >= ((stSmuTreap*)t)->hitCount) {
            promoteNodeSmuT(t, r, ((stSmuTreap*)t)->promotionRate);
            *promotion = 1;
        }
        return r;
    }
    
    if (x > ((stNode*)r)->anc.x) {
        ((stNode*)r)->dir = getNodeSmuTAux(t, ((stNode*)r)->dir, x, y, promotion);
        if (*promotion) {
            r = rebalanceiaSmuTreap(r);
            uniaoGeralBoundingBox(r);
        }
    } else {
        ((stNode*)r)->esq = getNodeSmuTAux(t, ((stNode*)r)->esq, x, y, promotion);
        if (*promotion) {
            r = rebalanceiaSmuTreap(r);
            uniaoGeralBoundingBox(r);
        }
    }
    
    return r;
}

Node getNodeSmuT(SmuTreap t, double x, double y) {
    if(!t) return NULL;
    int promotion = 0;
    ((stSmuTreap*)t)->raiz = getNodeSmuTAux(t, ((stSmuTreap*)t)->raiz, x, y, &promotion);
    return ((stSmuTreap*)t)->raiz;
}


void getNodesDentroRegiaoSmuTAux(SmuTreap t, Node r, double x1, double y1, double x2, double y2, Lista L) {
    if(r == NULL) return;

    int x = ((stNode*)r)->anc.x;
    int y = ((stNode*)r)->anc.y;

    double epsilon = ((stSmuTreap*)t)->epsilon;

    if (x1 - epsilon <= x && x <= x2 + epsilon &&
        y1 + epsilon >= y && y >= y2 - epsilon)
    {
        ((stNode*)r)->promotionCount++;
        inserirLista(L, r);
        if (((stNode*)r)->promotionCount >= ((stSmuTreap*)t)->hitCount) {
            promoteNodeSmuT(t, r, ((stSmuTreap*)t)->promotionRate);
        }
    }

    getNodesDentroRegiaoSmuTAux(t, ((stNode*)r)->esq, x1, y1, x2, y2, L);
    getNodesDentroRegiaoSmuTAux(t, ((stNode*)r)->dir, x1, y1, x2, y2, L);
}


bool getNodesDentroRegiaoSmuT(SmuTreap t, double x1, double y1, double x2, double y2, Lista L) {
    bool verif = true;

    getNodesDentroRegiaoSmuTAux(t, ((stSmuTreap*)t)->raiz, x1, y1, x2, y2, L);
    if(tamLista(L) == 0) {
        verif = false;
        liberarLista(L);
    }

    //((stSmuTreap*)t)->raiz = RebalanceFromRoot(((stSmuTreap*)t)->raiz);
    return verif;
}

bool verificacaoDescida(SmuTreap t, Node r, double x1, double y1, double x2, double y2) {
    double bb_x = getXBoundingBox(((stNode*)r)->bbsub);
    double bb_y = getYBoundingBox(((stNode*)r)->bbsub);
    double bb_w = getWBoundingBox(((stNode*)r)->bbsub);
    double bb_h = getHBoundingBox(((stNode*)r)->bbsub);

    double bb_x2 = bb_x + bb_w;
    double bb_y2 = bb_y + bb_h;

    double epsilon = ((stSmuTreap*)t)->epsilon;
    // verifica se há interseção primeiro em X depois em Y entre os retângulos
    bool intersecta = 
    (x1 - epsilon <= bb_x2) && (x2 + epsilon >= bb_x) &&
    (y1 - epsilon <= bb_y2) && (y2 + epsilon >= bb_y);
  

    return intersecta;
}

void getInfoDentroRegiaoSmuTAux(SmuTreap t, Node r, double x1, double y1, double x2, double y2, FdentroDeRegiao f, Lista L) {
    if(r==NULL) return;

    // verificao boundingbox da forma interna a selr
    
    if(((stNode*)r)->esq != NULL && verificacaoDescida(t, ((stNode*)r)->esq, x1, y1, x2, y2)) {

        getInfoDentroRegiaoSmuTAux(t, ((stNode*)r)->esq, x1, y1, x2, y2, f, L);
    } 
    if(((stNode*)r)->dir != NULL && verificacaoDescida(t, ((stNode*)r)->dir, x1, y1, x2, y2)) {

        getInfoDentroRegiaoSmuTAux(t, ((stNode*)r)->dir, x1, y1, x2, y2, f, L);  
    }
    
    if( f(r, ((stNode*)r)->bbinfo, x1, y1, x2, y2) ) {
        ((stNode*)r)->promotionCount++;
        if (((stNode*)r)->promotionCount >= ((stSmuTreap*)t)->hitCount) {
            promoteNodeSmuT(t, r, ((stSmuTreap*)t)->promotionRate);
        }
        inserirLista(L, r);
    }
}

bool getInfosDentroRegiaoSmuT(SmuTreap t, double x1, double y1, double w, double h, FdentroDeRegiao f, Lista L) {
    bool verif = true;

    double x2, y2;
    x2 = x1 + w;
    y2 = y1 + h;

    getInfoDentroRegiaoSmuTAux(t, ((stSmuTreap*)t)->raiz, x1, y1, x2, y2, f, L);
    if(tamLista(L) == 0) {
        printf("Nao existem nos dentro da regiao solicitada!!\n");
        return false;
    }

    //((stSmuTreap*)t)->raiz = RebalanceFromRoot(((stSmuTreap*)t)->raiz);
    printf("\nTAM LISTA INFO DENTRO REGIAO = %d\n\n", tamLista(L));
    return verif;
}

bool verificacaoDescidaPonto(SmuTreap t, Node r, double x, double y) {
    if (r==NULL) return false;

    double bb_left = getXBoundingBox(((stNode*)r)->bbsub);
    double bb_bottom = getYBoundingBox(((stNode*)r)->bbsub);
    double bb_width = getWBoundingBox(((stNode*)r)->bbsub);
    double bb_height = getHBoundingBox(((stNode*)r)->bbsub);

    // calculo dos limites do bounding box
    double bb_right = bb_left + bb_width;
    double bb_top = bb_bottom + bb_height;

    double epsilon = ((stSmuTreap*)t)->epsilon;

    // verifica se o ponto (x, y) está dentro do bounding box
    bool pontoDentro = (x + epsilon >= bb_left && x - epsilon <= bb_right) &&
                   (y + epsilon >= bb_bottom && y - epsilon <= bb_top);

    
    return pontoDentro;
}


bool pertenceTreapAux(Node atual, Node r) {
    if (atual == NULL) return false;
    if (atual == r) return true;
    return pertenceTreapAux(((stNode*)atual)->esq, r) || 
           pertenceTreapAux(((stNode*)atual)->dir, r);
}

bool pertenceTreap(SmuTreap t, Node r) {
    return pertenceTreapAux(((stSmuTreap*)t)->raiz, r);
}

void getInfosAntigidoAux(SmuTreap t, Node r, double x, double y, FpontoInternoAInfo f, Lista l) {
    if(r==NULL) return;

    // if (!pertenceTreap(t, r)) {
    //     return;
    // }

    if(((stNode*)r)->esq != NULL && verificacaoDescidaPonto(t, ((stNode*)r)->esq, x, y)) {
        getInfosAntigidoAux(t, ((stNode*)r)->esq, x, y, f, l);
    }
    if(((stNode*)r)->dir != NULL && verificacaoDescidaPonto(t, ((stNode*)r)->dir, x, y)) {
        getInfosAntigidoAux(t, ((stNode*)r)->dir, x, y, f, l);
    }
    
    
    if(f(r, getInfoSmuT(t, r), x, y)) {
        ((stNode*)r)->promotionCount++;
        if (((stNode*)r)->promotionCount >= ((stSmuTreap*)t)->hitCount) {
            promoteNodeSmuT(t, r, ((stSmuTreap*)t)->promotionRate);
        }
        inserirLista(l, r);
    }
}

bool getInfosAtingidoPontoSmuT(SmuTreap t, double x, double y, FpontoInternoAInfo f, Lista L) {
    if(t==NULL) return false;

    getInfosAntigidoAux(t, ((stSmuTreap*)t)->raiz, x, y, f, L);
    if(tamLista(L) == 0) {
        return false;
    }

    printf("TAM LISTA INFO ATINGIDOS: %d\n\n", tamLista(L));
    return true;
}


DescritorTipoInfo getTypeInfoSrbT(SmuTreap t, Node n) {
    return ((stNode*)n)->d;
}

Info getInfoSmuT(SmuTreap t , Node n) {
    return ((stNode*)n)->info;
}

Info getBoundingBoxSmuT(SmuTreap t, Node r, double *x, double *y, double *w, double *h) {
    *x = getXBoundingBox(((stNode*)r)->bbinfo);
    *y = getYBoundingBox(((stNode*)r)->bbinfo);
    *w = getWBoundingBox(((stNode*)r)->bbinfo);
    *h = getHBoundingBox(((stNode*)r)->bbinfo);

    return ((stNode*)r)->bbinfo;
}

void killSmuTreapAux(Node r) {
    if(r == NULL)
        return;

    killSmuTreapAux(((stNode*)r)->esq);
    killSmuTreapAux(((stNode*)r)->dir);
    free(r);
}

void killSmuTreap(SmuTreap t) {
    if(t == NULL) {
        printf("Arvore NULA !!\n");
        return;
    }
    killSmuTreapAux(((stSmuTreap*)t)->raiz);
    free(t);
}

void printDotRecursive(SmuTreap t, Node root, FILE *fp) {
    if (root == NULL) return;
 
    int descritor = ((stNode*)root)->d;
    int x = ((stNode*)root)->anc.x;  
    int y = ((stNode*)root)->anc.y; 
    int priori = ((stNode*)root)->priori;
    
    char cor[10];
    if (descritor == 1)
        strcpy(cor, "purple");
    else if(descritor == 0)
        strcpy(cor, "green");
    else if(descritor == 2)
        strcpy(cor, "blue");
    else if(descritor == 3)
        strcpy(cor, "orange");
    else    
        return;

    // Imprimir o nó atual com as informações de x, y e id, sem o endereço de memória
    fprintf(fp, "\t\"%p\" [label=\"nX: %d\\nY: %d\\nPriori: %d\", color=black, fontcolor=white, style=filled, fillcolor=%s];\n",
         root, x, y, priori, cor);
 
    // Imprimir a conexão com o filho esq
    if (((stNode*)root)->esq != NULL) {
       fprintf(fp, "\t\"%p\" -- \"%p\";\n", root, ((stNode*)root)->esq);
       printDotRecursive(t, ((stNode*)root)->esq, fp);
    }
 
    // Imprimir a conexão com o filho dir
    if (((stNode*)root)->dir != NULL) {
       fprintf(fp, "\t\"%p\" -- \"%p\";\n", root, ((stNode*)root)->dir);
       printDotRecursive(t, ((stNode*)root)->dir, fp);
    }
}
 

// funcao principal do .dot da SmuTreap
bool printDotSmuTreap(SmuTreap t, char *fn) {
    FILE *fp;
    SmuTreap tree = t;
 
    // Abrir o arquivo DOT para escrita
    fp = fopen(fn, "w");
    if (fp == NULL) {
       perror("Erro ao criar o arquivo DOT");
       return false;
    }
 
    // Escrever o cabeçalho do arquivo DOT
    fprintf(fp, "graph G {\n");
    fprintf(fp, "\trankdir=TB;\n"); // Top-Bottom para hierarquia
    fprintf(fp, "\tnode [shape=circle];\n");
 
    // Gerar a representação da árvore
    printDotRecursive(t, ((stSmuTreap*)tree)->raiz, fp);
 
    // Fechar o grafo
    fprintf(fp, "}\n");
 
    // Fechar o arquivo
    fclose(fp);
 
    return true;
}


Node procuraNoSmuTAux(SmuTreap t, Node r, FsearchNo f, void *aux) {
    if(r==NULL) return NULL;

    if(f(r, getInfoSmuT(t, r), ((stNode*)r)->anc.x, ((stNode*)r)->anc.y, aux));

    ((stNode*)r)->esq = procuraNoSmuTAux(t, ((stNode*)r)->esq, f, aux);
    ((stNode*)r)->dir = procuraNoSmuTAux(t, ((stNode*)r)->dir, f, aux);

    return r;
}

Node procuraNoSmuT(SmuTreap t, FsearchNo f, void *aux) {
    if (t == NULL) return NULL;
    Node r = procuraNoSmuTAux(t, ((stSmuTreap*)t)->raiz, f, aux);
}



typedef struct FilaNo {
    Node r;
    struct FilaNo *prox;
} FilaNo;

typedef struct {
    FilaNo *ini, *fim;
} Fila;

void inserirFila(Fila *fila, Node n) {
    FilaNo *novo = malloc(sizeof(FilaNo));
    novo->r = n;
    novo->prox = NULL;
    if (fila->fim) {
        fila->fim->prox = novo;
    } else {
        fila->ini = novo;
    }
    fila->fim = novo;
}

Node retirarFila(Fila *fila) {
    if (!fila->ini) return NULL;

    FilaNo *rem = fila->ini;
    Node no = rem->r;
    fila->ini = rem->prox;

    if (!fila->ini) 
        fila->fim = NULL;

    free(rem);
    return no;
}

int filaVazia(Fila *fila) {
    return fila->ini == NULL;
}

void visitaLarguraSmuT(SmuTreap t, FvisitaNo f, void *aux) {
    if (t==NULL) return;
    Fila fila = {0};
    inserirFila(&fila, t);

    while (!filaVazia(&fila)) {

        Node atual = retirarFila(&fila);
        f(atual, ((stNode*)atual)->info, ((stNode*)atual)->anc.x, ((stNode*)atual)->anc.y, aux);
        
        if (((stNode*)atual)->esq) 
            inserirFila(&fila, ((stNode*)atual)->esq);
        if (((stNode*)atual)->dir) 
            inserirFila(&fila, ((stNode*)atual)->dir);
    }
}


