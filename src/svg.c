#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "svg.h"
#include "enderecos.h"
#include "circulo.h"
#include "linha.h"
#include "retangulo.h"
#include "texto.h"
#include "registradores.h"

// c2 = (0 0 10500 3500)
// c1 = (0 0 1700 1200)
void printSVGCabecalho(FILE *svg) {
    fprintf(svg, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(svg, "<svg viewBox=\"0 0 10500 3500\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" version=\"1.1\">\n");
}

void fecharSVG(FILE *svg) {
    fprintf(svg, "</svg>\n");
    fclose(svg);
}

void insertQuadraSVG(FILE *svg, Quadra q) {
    fprintf(svg, "<rect id=\"%s\" style=\"fill:%s;fill-opacity:0.5;stroke:%s\" height=\"%lf\" width=\"%lf\" y=\"%lf\" x=\"%lf\" stroke-width=\"%s\" />\n", getNomeQuadra(q), getCorpQuadra(q), getCorbQuadra(q), getHQuadra(q), getWQuadra(q), getYQuadra(q), getXQuadra(q), getSWQuadra(q));
}

void insertCircleSVG(FILE *svg, Circulo c) {
    fprintf(svg, "<circle id=\"%d\" style=\"fill:%s;opacity:0.5;stroke:%s\" r=\"%lf\" cy=\"%lf\" cx=\"%lf\" stroke-width=\"%lf\" />\n", getICirculo(c), getCorpCirculo(c), getCorbCirculo(c), getRCirculo(c), getYCirculo(c), getXCirculo(c), getSWCirculo(c));
}

void insertRectSVG(FILE *svg, Retangulo r) {
    fprintf(svg, "<rect id=\"%d\" style=\"fill:%s;fill-opacity:0.5;stroke:%s\" height=\"%lf\" width=\"%lf\" y=\"%lf\" x=\"%lf\" stroke-width=\"%lf\" />\n", getIRetangulo(r),getCorpRetangulo(r), getCorbRetangulo(r), getHRetangulo(r), getWRetangulo(r), getYRetangulo(r), getXRetangulo(r), getSWRetangulo(r));
}

void insertLineSVG(FILE *svg, Linha l) {

    if(getPontilhadaLinha(l))
        fprintf(svg, "<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"%lf\" stroke-dasharray=\"5 2\" />\n", getILinha(l), getX1Linha(l), getY1Linha(l), getX2Linha(l), getY2Linha(l), getCorLinha(l), getSWLinha(l));
    else
        fprintf(svg, "<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"%lf\" />\n", getILinha(l), getX1Linha(l), getY1Linha(l), getX2Linha(l), getY2Linha(l), getCorLinha(l), getSWLinha(l));

}

void insertTextSVG(FILE *svg, Texto t) {
    char a = getATexto(t);
    switch(a) {
        case 'i':
            fprintf(svg, "<text id=\"%d\" font-size=\"%s\" line-height=\"0\" text-anchor=\"start\" fill=\"%s\" stroke=\"%s\" font-family=\"%s\" y=\"%lf\" x=\"%lf\" stroke-width=\"%lf\" ><![CDATA[%s]]></text>\n", getITexto(t), getSize(getStyle(t)), getCorpTexto(t), getCorbTexto(t), getFamily(getStyle(t)) , getYTexto(t), getXTexto(t), getSWTexto(t) ,getTextTexto(t));
            break;
        case 'm':
            fprintf(svg, "<text id=\"%d\" font-size=\"%s\" line-height=\"0\" text-anchor=\"middle\" fill=\"%s\" stroke=\"%s\" font-family=\"%s\" y=\"%lf\" x=\"%lf\" stroke-width=\"%lf\" ><![CDATA[%s]]></text>\n", getITexto(t), getSize(getStyle(t)), getCorpTexto(t), getCorbTexto(t) ,getFamily(getStyle(t)) , getYTexto(t), getXTexto(t), getSWTexto(t) ,getTextTexto(t));
            break;
        case 'f':
            fprintf(svg, "<text id=\"%d\" font-size=\"%s\" line-height=\"0\" text-anchor=\"end\" fill=\"%s\" stroke=\"%s\" font-family=\"%s\" y=\"%lf\" x=\"%lf\" stroke-width=\"%lf\" ><![CDATA[%s]]></text>\n", getITexto(t), getSize(getStyle(t)), getCorpTexto(t), getCorbTexto(t), getFamily(getStyle(t)) , getYTexto(t), getXTexto(t), getSWTexto(t) ,getTextTexto(t));
            break;
    }
}


void printPathCMCSVG(FILE *svg, Percurso p, char *nomepath) {
    Lista path = getPathCMCPercurso(p);
    double x, y;

    fprintf(svg, "<path d=\"M");

    for(Celula p = getInicioLista(path); p != NULL; p = getProxCelula(p)) {
        Coordenadas atual = getConteudoCelula(p);

        x = getXCoord(atual);
        y = getYCoord(atual);

        fprintf(svg, " %lf,%lf", x, y);
    }

    strcat(nomepath, "cmc");
    fprintf(svg, "\" id=\"%s\" fill=\"none\" stroke=\"none\" />", nomepath);
}

void printPathCMRSVG(FILE *svg, Percurso p, char *nomepath) {
    Lista path = getPathCMRPercurso(p);
    double x, y;

    fprintf(svg, "<path d=\"M");

    for(Celula p = getInicioLista(path); p != NULL; p = getProxCelula(p)) {
        Coordenadas atual = getConteudoCelula(p);

        x = getXCoord(atual);
        y = getYCoord(atual);

        fprintf(svg, " %lf,%lf", x, y);
    }

    strcat(nomepath, "cmr");
    fprintf(svg, "\" id=\"%s\" fill=\"none\" stroke=\"none\" />", nomepath);
}

void printAnimationSVG(FILE *svg, char *idpath, double animationTime) {
    fprintf(svg, "<g transform=\"scale(0.12) translate(-96,-96)\">\n");

    fprintf(svg, "  <path d=\"M22.509 184.252zm74.063-.301c-22.804-8.9-41.099-21.232-53.867-38.307-13.264-17.771-19.808-40.633-19.808-72.482V8.504h147.35v64.658c0 31.849-6.543 54.71-19.807 72.482-12.77 17.075-31.065 29.407-53.868 38.307z\"/>\n");
    fprintf(svg, "  <path d=\"M96.572 178.891c-10.238-4.102-19.575-8.9-27.865-14.688h55.729c-8.29 5.787-17.625 10.586-27.864 14.688zm-49.563-35.514c-4.393-5.904-8.086-12.508-11.053-19.895h121.231c-2.967 7.387-6.66 13.99-11.053 19.895H47.009zm-17.423-43.076c-1.018-6.051-1.658-12.508-1.92-19.401h137.781c-.232 6.894-.873 13.351-1.891 19.401H29.586zm69.43-64.689h66.578v22.833H99.016V35.612zM27.55 13.187h66.782v63.03H27.55v-63.03z\" fill=\"#cd3529\"/>\n");
    fprintf(svg, "  <path d=\"M72.052 73.396c-1.629-.524-3.607-4.945-3.52-7.068v-.291c-2.124-3.607-4.276-6.486-5.759-8.29l.029 9.336c-.117 3.142-.902 5.148-3.17 6.225 1.861.262 4.712.64 6.399-1.861.466 1.075 3.665 2.762 6.021 1.949zm5.73-20.797c.582 1.309.959 3.578-2.618 6.457 4.362-.552 6.341-2.181 6.544-4.305.349-3.926-.959-3.956-.058-9.278.291-1.803 1.425-3.054 3.374-4.625-4.072.61-6.573 2.617-7.853 7.126l-8.639-.029V32.587h2.705c-.262-1.687-.756-3.345-1.774-5.206h-4.159c-2.094 0-2.996-.815-5.032-.087 1.483.873 2.531 2.007 2.531 3.287v17.685c1.949.989 3.956 2.588 5.526 4.333h9.453zm3.694-20.012h4.421c0 2.472 2.851 7.359 7.068 7.504-2.124-3.054-2.967-5.207-2.036-9.395 2.123-5.468.465-9.831-2.007-10.442.465 1.512.785 5.992-1.774 7.155h-8.202c.785 2.619 1.948 4.742 2.53 5.178zM61.494 64.059c-17.48 6.253-25.247-2.24-30.046-14.892-.669-1.6-.727-2.705-2.618-3.897 2.124-.698 2.501-2.007 2.821-3.345 1.193-8.552 6.486-15.765 14.805-18.412v4.218c-5.876 2.938-9.046 10.762-8.842 18.062.262 8.26 7.969 16.841 15.793 16.637 2.56-.058 5.469-.349 8.086-2.297v3.926h.001zm-6.661-41.913c1.28-.058 2.647-.117 4.101-.146-.32 1.862-.989 9.075 1.92 11.518-.553 1.192-2.065 2.501-3.52 2.473-.989-.029-1.279-.466-1.804-1.193-.232-.349-.465-.698-.698-1.076V22.146h.001zm-1.338 29.929v8.987c-.582.087-1.28.087-2.152-.087-.931-.174-2.269-.523-3.578-1.367v-37.55c0-2.327-1.745-4.392-4.683-5.584 2.85-1.833 8.318-.116 9.22 1.949 2.851-1.861 6.253-2.734 9.627-2.705 6.428.058 12.739 3.49 15.154 10.035 1.25 3.461 1.891 6.981 4.45 8.29a5.218 5.218 0 0 0-1.716 1.454c-1.309 1.717-2.152 4.305-4.305 7.476-.844 1.28-1.89 2.501-3.141 3.694h-2.56v-3.055c1.803-2.879 2.792-6.515 2.734-10.035-.058-5.148-4.043-13.001-13.176-13.525-2.618-.146-4.857.64-5.875 1.28v26.032c5.352 0 9.22 1.891 12.1 4.421 2.763 2.414 4.683 5.527 6.399 8.755 2.443 4.596 4.13 8.639 7.097 8.551 2.24-.116 3.287-1.192 4.276-2.589.989 4.596-2.56 6.516-4.741 6.574-2.327.029-5.119-1.949-6.894-4.508-2.705-3.839-5.293-9.278-9.046-12.856-4.158-4.015-7.096-3.637-9.19-3.637zm.524 15.27c.61 2.473 1.832 5.439 3.926 6.777-5.497-.058-5.905-1.978-6.69-2.821-1.309 1.309-3.316 3.49-7.504 3.054 2.356-2.182 3.374-4.363 3.781-7.097 2.037.32 4.567.407 6.487.087z\" fill=\"#fff\"/>\n");

    fprintf(svg, "      <animateMotion dur=\"%.2lfs\" repeatCount=\"indefinite\">\n", animationTime);
    fprintf(svg, "          <mpath xlink:href=\"#%s\"/>\n", idpath);
    fprintf(svg, "      </animateMotion>\n");

    fprintf(svg, "</g>\n");
}


