#include "APIG24.h"
#include "EstructuraGrafo24.h"



Grafo ConstruirGrafo(FILE* fp) {
    Grafo g = malloc(sizeof(GrafoSt));
    g->list_vertices = NULL;
    g->lados = NULL;
    g->list_color = NULL;
    fscanf(fp,"p edge %u %u", &(g->cantidad_vertices), &(g->cantidad_lados));
    g->lados = malloc(sizeof(u32) * g->cantidad_lados);
    for(int i = 0; i<g->cantidad_lados;++i) {
        int v1;
        int v2;
        fscanf(fp, "e %u %u", &v1, &v2);


    }
    return g;
}


u32 NumeroDeVertices(Grafo G) { 
    return G->cantidad_vertices;
}
u32 NumeroDeLados(Grafo G){
    return G->cantidad_lados;
}
int main(int argc, char const *argv[])
{
    FILE* fp = fopen("K5.txt", "r");
    Grafo g = ConstruirGrafo(fp);
    u32 vertices = NumeroDeVertices(g);
    u32 lados = NumeroDeLados(g);
    printf("vertices: %u, lados: %u\n", vertices, lados);
    fclose(fp);
    return 0;
}
