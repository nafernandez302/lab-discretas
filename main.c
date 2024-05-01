#include "APIG24.h"
#include "API2024Parte2.h"

#define N 9
int main()
{
    /*
    
    Corremos Greedy en 5 órdenes distintos.
    1) Orden natural 0, 1, 2, ..., n-1 de los vértices.
    2) Orden natural inverso n-1, ..., 2, 1, 0 de los vértices.
    3) Orden primero todos los pares decreciente y los impares creciente.
    4) Ordenados por grado de mayor a menor.
    5) Orden a elegir.
    
    */
    
    // 1) Orden natural de los elementos.
    Grafo G = ConstruirGrafo();
    u32 n = NumeroDeVertices(G);
    u32 Orden1[n];
    for(u32 i = 0; i < n; i++){
        Orden1[i] = i;
    }
    printf("Cantidad de colores usando el orden 1: %u\n", Greedy(G, Orden1));
    

    // 2) Orden natural inverso de los elementos.
    u32 Orden2[n];
    for(int i = n-1; i >= 0; i--){
        Orden2[i] = i;
    }
    printf("Cantidad de colores usando el orden 2: %u\n", Greedy(G, Orden2));
    
    // 3) Orden primero todos los pares decrecientes y después los impares crecientes.
    u32 Orden3[n];
    int posicionPar = 0;
    int posicionImpar = n-1;
    for(int i = n-1; i >= 0; i--){
        if(i % 2 != 0){
            Orden3[posicionImpar] = i;
            posicionImpar--;
        } else {
            Orden3[posicionPar] = i;
            posicionPar++;
        }
    }
    printf("Cantidad de colores usando el orden 3: %u\n", Greedy(G, Orden3));

    // 4) Orden por grado de mayor a menor.
    u32 Orden4[n];
    for(u32 i = 0; i < n; i++){
        Orden4[i] = i;
    }
    quickSortGrado(Orden4, 0, n-1, G);
    printf("Cantidad de colores usando el orden 4: %u\n", Greedy(G, Orden4));

    // 5) Orden personalizado.

    //TODO

    DestruirGrafo(G);

    return 0;
}
