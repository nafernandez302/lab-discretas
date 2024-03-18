#include "../APIG24.h"

int main()
{
    Grafo g = ConstruirGrafo();
    u32 vertices = NumeroDeVertices(g);
    u32 lados = NumeroDeLados(g);
    printf("vertices: %u, lados: %u\n", vertices, lados);

    u32 delta = Delta(g);
    printf("delta: %u\n", delta);

    color c = 1;
    for(u32 i = 0; i < NumeroDeVertices(g); ++i) {
        AsignarColor(c,i,g);
        c++;
    }

    printf("Los colores de los primeros vertices son: \n");
    u32 cota_vertice = NumeroDeVertices(g);
    if(cota_vertice > 10) {
        cota_vertice = 10;
    }
    for(u32 i = 0; i < cota_vertice; ++i ){
        printf("vertice %u, color %u\n", i, Color(i,g));
    }
    DestruirGrafo(g);
    return 0;
}
