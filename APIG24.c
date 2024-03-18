#include "APIG24.h"
#include <stdint.h>

#define U32_MAX 4294967295

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
        //Si no leí correctamente los dos campos, error.
        if (r!=2) {
            printf("Error: La entrada tiene un formato inválido.\n");
            free(g);
            exit(EXIT_FAILURE);
            return NULL;
        }

        // Vértice con nuevo vécino, aumenta su grado
        g->vecinos[v1][g->list_vertices[v1].grado] = v2;
        g->vecinos[v2][g->list_vertices[v2].grado] = v1;
        g->list_vertices[v1].grado++;
        g->list_vertices[v2].grado++;
    }
    return g;
}

void DestruirGrafo(Grafo G){
    for(u32 i = 0; i < G->cantidad_vertices;++i){
        free(G->vecinos[i]);
    }
    free(G->vecinos);
    free(G->list_vertices);
    free(G);
}
u32 NumeroDeVertices(Grafo G) { 
    return G->cantidad_vertices;
}

u32 NumeroDeLados(Grafo G) {
    return G->cantidad_lados;
}

u32 Vecino(u32 j,u32 i,Grafo G) { //Retorna el j-ésimo vecino del vértice i. 
    if (i >= G->cantidad_vertices || (i < G->cantidad_vertices && j >= Grado(i,G))) {
        return U32_MAX;
    } else {
        return G->vecinos[i][j];
    }
}
    
    

u32 Delta(Grafo G) {
    return G->delta;
}

u32 Grado(u32 i,Grafo G) {
    if (i < G->cantidad_vertices) {
        return G->list_vertices[i].grado;
    } else {
        return U32_MAX;
    }
    
} 


color Color(u32 i,Grafo G) {
    if (i < G->cantidad_vertices) {
        return G->list_vertices[i].color;
    } else {
        return U32_MAX;
    }
    
}

