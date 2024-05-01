#include "APIG24.h"
#include "API2024Parte2.h"
#include <assert.h>


#define N 9
int main()
{
    Grafo G = ConstruirGrafo();
    u32 n = NumeroDeVertices(G);
    u32 Orden1[n];
    u32 Orden2[n];
    u32 Orden3[n];
    u32 Orden4[n];
    u32 Orden5[n];

    /*

    Corremos Greedy en 5 órdenes distintos.
    1) Orden natural 0, 1, 2, ..., n-1 de los vértices.
    2) Orden natural inverso n-1, ..., 2, 1, 0 de los vértices.
    3) Orden primero todos los pares decreciente y los impares creciente.
    4) Ordenados por grado de mayor a menor.
    5) Orden con offset de 1.

    */


    // 1) Orden natural de los elementos.

    for (u32 i = 0; i < n; i++) {
        Orden1[i] = i;
    }

    // 2) Orden natural inverso de los elementos.

    for (int i = 0; i < n; i++) {
        Orden2[i] = n - i - 1;
    }

    // 3) Orden primero todos los pares decrecientes y después los impares crecientes.

    int posicionPar = 0;
    int posicionImpar = n - 1;
    for (int i = n - 1; i >= 0; i--) {
        if (i % 2 != 0) {
            Orden3[posicionImpar] = i;
            posicionImpar--;
        }
        else {
            Orden3[posicionPar] = i;
            posicionPar++;
        }
    }

    // 4) Orden por grado de mayor a menor.
    for (u32 i = 0; i < n; i++) {
        Orden4[i] = i;
    }
    quickSortGrado(Orden4, 0, n - 1, G);

    // 5) Orden con un offset de 1
    u32 offset = 1;
    for (u32 i = 0; i < n - 1; i++) {
        Orden5[i] = i + 1;
    }
    Orden5[n - 1] = 0;

    // primeros prints

    printf("Cantidad de colores usando el orden 5: %u\n", Greedy(G, Orden1));
    printf("Cantidad de colores usando el orden 5: %u\n", Greedy(G, Orden2));
    printf("Cantidad de colores usando el orden 5: %u\n", Greedy(G, Orden3));
    printf("Cantidad de colores usando el orden 5: %u\n", Greedy(G, Orden4));
    printf("Cantidad de colores usando el orden 5: %u\n", Greedy(G, Orden5));






    DestruirGrafo(G);

    return 0;
}