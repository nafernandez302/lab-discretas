#include "../APIG24.h"

int main()
{
    Grafo g = ConstruirGrafo();
    u32 vertices = NumeroDeVertices(g);
    u32 lados = NumeroDeLados(g);
    printf("vertices: %u, lados: %u\n", vertices, lados);

    u32 delta = Delta(g);
    printf("delta: %u\n", delta);
    DestruirGrafo(g);
    return 0;
}
