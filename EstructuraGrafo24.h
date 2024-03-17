#ifndef ESTRUCTURA_GRAFO_24_H
#define ESTRUCTURA_GRAFO_24_H


typedef unsigned int u32;
typedef u32 color;

typedef struct _vertices{
    u32 grado;
    color color;
} vertices;

typedef struct _Grafo {
    vertices* list_vertices;
    u32** vecinos;
    u32 cantidad_vertices;
    u32 cantidad_lados;
    u32 delta;
} GrafoSt;

#endif


