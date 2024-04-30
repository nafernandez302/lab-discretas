#include "APIG24.h"
#include "API2024Parte2.h"
#include "assert.h"


#define ITERACIONES 50
int main()
{
    Grafo G = ConstruirGrafo();
    u32 n = NumeroDeVertices(G);
    //u32 orden1[N] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    u32 orden2[n];

    for (u32 i = 0; i < n; i++)
    {
        orden2[i] = i;
    }

    assert(biyectivo(orden2, n));

    u32 cantidad = 0;
    char succesDukat;
    char succesGarak;

    printf("delta: %u\n", Delta(G));
    for (int i = 0; i < ITERACIONES; i++) {
        assert(biyectivo(orden2, n));
        cantidad = Greedy(G, orden2);
        printf("se pinto con %u colores\n", cantidad);
        succesGarak = ElimGarak(G, orden2);
        assert(succesGarak == '0');
    }


    for (int i = 0; i < ITERACIONES; i++) {
        assert(biyectivo(orden2, n));
        cantidad = Greedy(G, orden2);
        printf("se pinto con %u colores\n", cantidad);
        succesDukat = GulDukat(G, orden2);
        assert(succesDukat == '0');
    }
    DestruirGrafo(G);


    return 0;
}
