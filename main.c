#include "APIG24.h"
#include "API2024Parte2.h"

#define N 9
int main()
{
    //u32 orden1[N] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    u32 orden2[256];
    for (size_t i = 0; i < 256; i++)
    {
        orden2[i] = i;
    }
    
   // u32 orden2[N] = {0, 3, 2, 1, 4};
   // u32 orden3[N] = {4, 3, 0, 1, 2};

    Grafo G = ConstruirGrafo();
    u32 cantidad = Greedy(G, orden2);
    printf("%u\n", cantidad);
    printf("delta: %u\n", Delta(G));
    char xd = GulDukat(G,orden2);
    printf("%c", xd);
    DestruirGrafo(G);

    return 0;
}
