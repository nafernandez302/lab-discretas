#include "APIG24.h"

int main()
{
    Grafo g = ConstruirGrafo();
    u32 vertices = NumeroDeVertices(g);
    u32 lados = NumeroDeLados(g);
    printf("vertices: %u, lados: %u\n", vertices, lados);
    /*
    u32 v0_0 = Vecino(0,0,g);
    u32 v0_1 = Vecino(0,1,g);
    u32 v1_1 = Vecino(1,1,g);
    printf("el vecino 0 de 0 es: %u\n", v0_0);
    printf("el vecino 0 de 1 es: %u\n", v0_1);
    printf("el vecino 1 de 1 es: %u\n", v1_1);*/
    return 0;
}
