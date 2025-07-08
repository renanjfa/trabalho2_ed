#include <stdio.h>
#include <stdlib.h>

#include "svg.h"
#include "enderecos.h"
#include "circulo.h"
#include "linha.h"
#include "retangulo.h"
#include "texto.h"

void printSVGCabecalho(FILE *svg) {
    fprintf(svg, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(svg, "<svg width=\"2000\" height=\"2000\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
}

void fecharSVG(FILE *svg) {
    fprintf(svg, "</svg>\n");
    fclose(svg);
}

void insertQuadraSVG(FILE *svg, Quadra q) {
    fprintf(svg, "<rect id=\"%s\" style=\"fill:%s;fill-opacity:0.5;stroke:%s\" height=\"%lf\" width=\"%lf\" y=\"%lf\" x=\"%lf\" stroke-width=\"%lf\" />\n", getNomeQuadra(q), getCorpQuadra(q), getCorbQuadra(q), getHQuadra(q), getWQuadra(q), getYQuadra(q), getXQuadra(q), getSWQuadra(q));
}

void insertCircleSVG(FILE *svg, Circulo c) {
    fprintf(svg, "<circle id=\"%d\" style=\"fill:%s;fill-opacity:0.5;stroke:%s\" r=\"%lf\" cy=\"%lf\" cx=\"%lf\" stroke-width=\"%lf\" />\n", getICirculo(c), getCorpCirculo(c), getCorbCirculo(c), getRCirculo(c), getYCirculo(c), getXCirculo(c), getSWCirculo(c));
}

void insertRectSVG(FILE *svg, Retangulo r) {
    fprintf(svg, "<rect id=\"%d\" style=\"fill:%s;fill-opacity:0.5;stroke:%s\" height=\"%lf\" width=\"%lf\" y=\"%lf\" x=\"%lf\" stroke-width=\"%lf\" />\n", getIRetangulo(r),getCorpRetangulo(r), getCorbRetangulo(r), getHRetangulo(r), getWRetangulo(r), getYRetangulo(r), getXRetangulo(r), getSWRetangulo(r));
}

void insertLineSVG(FILE *svg, Linha l) {
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
