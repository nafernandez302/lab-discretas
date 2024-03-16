#ifndef ESTRUCTURA_GRAFO_24_H
#define ESTRUCTURA_GRAFO_24_H


typedef unsigned int u32;
typedef u32 color;


typedef struct _Grafo {
    u32* list_vertices;
    u32 cantidad_vertices;
    u32** lados;
    u32 cantidad_lados;
    u32 delta;
    color* list_color;
} GrafoSt;


#endif


