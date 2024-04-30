#ifndef MIGRAFO_H

#define MIGRAFO_H

typedef unsigned int u32;
typedef unsigned int color;

typedef struct _data {
    color color;
    u32 grado; // logintud del array vecino para cada vertice.
    u32 size;
}data;

typedef struct _grafo {
    u32 n; //numero de vertices
    u32 m; //numero de lados
    u32 delta; //mayor numero de vecinos de un vertice x
    data *vertices; // array de structs con color y grado
    u32 **vecinos; //matriz con los vecinos
} GrafoSt;

#endif