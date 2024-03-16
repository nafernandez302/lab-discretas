#ifndef ESTRUCTURA_GRAFO_24_H
#define ESTRUCTURA_GRAFO_24_H


typedef unsigned int u32;
typedef u32 color;

struct vertices{
    u32** vecinos; // vecinos[i][j] = el vecino j-ésimo del vértice i
    u32 tamaño;
};

typedef struct _Grafo {
    struct vertices* vertices;
    u32 delta;
    color* list_color;
} GrafoSt;

#endif


