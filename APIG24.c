#include "APIG24.h"
#include <stdint.h>

Grafo ConstruirGrafo() {
    Grafo g = malloc(sizeof(GrafoSt));
    scanf("p edge %u %u", &(g->cantidad_vertices), &(g->cantidad_lados));
    
    // Inicialización de grados
    g->list_vertices = malloc(sizeof(struct _vertices) * g->cantidad_vertices);
    for (unsigned int i = 0; i < g->cantidad_vertices; ++i) {
        g->list_vertices[i].grado = 0;
    }

    // Inicialización lista de vecinos
    g->vecinos = malloc(sizeof(uint32_t*) * g->cantidad_vertices);
    for(u32 i = 0; i<g->cantidad_vertices; i++) {
        g->vecinos[i] = malloc(sizeof(u32) * g->cantidad_lados);
    }

    // Llenado de matriz de vecinos
    for(u32 i = 0; i < g->cantidad_lados;++i) {
        u32 v1, v2;
        int r = scanf("\ne %u %u", &v1, &v2); // TODO: chequear que r=2

        // Vértice con nuevo vécino, aumenta su grado

        
        g->vecinos[v1][g->list_vertices[v1].grado] = v2;
        g->vecinos[v2][g->list_vertices[v2].grado] = v1;
        g->list_vertices[v1].grado++;
        g->list_vertices[v2].grado++;
    }
    return g;
}

u32 NumeroDeVertices(Grafo G) { 
    return G->cantidad_vertices;
}

u32 NumeroDeLados(Grafo G){
    return G->cantidad_lados;
}

u32 Vecino(u32 j,u32 i,Grafo G) {
    u32 vecino = G->vecinos[i][j];
    return vecino;
}