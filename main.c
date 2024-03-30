#include "APIG24.h"

int main()
{
    Grafo g = ConstruirGrafo();
    u32 vertices = NumeroDeVertices(g);
    u32 lados = NumeroDeLados(g);
    printf("vertices: %u, lados: %u\n", vertices, lados);
    u32 i = 3;
    u32 j = 2s;
    /* 
    Para ingresar un vértice de forma manual:

    printf("Indique un vértice con un número del 0 al %d: \n", g->cantidad_vertices-1);
    scanf("%u",&i);
    if(i > vertices) { //No se contemplan los negativos.
        printf("Error: El vértice especificado no existe.\n");
    } else {
        printf("El vértice %d tiene grado: %u.\n",i,Grado(i, g));
    }
    */
    
    printf("El vértice %d tiene grado: %u.\n", i, Grado(i, g));
    printf("El vértice %d tiene color: %u.\n", i, Color(i, g));
    printf("El vecino %d del vértice %d es el vértice %d.\n", j, i, Vecino(j,i,g));
    /*
    u32 v0_0 = Vecino(0,0,g);
    u32 v0_1 = Vecino(0,1,g);
    u32 v1_1 = Vecino(1,1,g);
    printf("el vecino 0 de 0 es: %u\n", v0_0);
    printf("el vecino 0 de 1 es: %u\n", v0_1);
    printf("el vecino 1 de 1 es: %u\n", v1_1);*/
    DestruirGrafo(g);
    return 0;
}
