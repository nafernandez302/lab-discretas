#include "APIG24.h"
#include "API2024Parte2.h"
#include <stdbool.h>

#define U32_MAX 4294967295

void swap(color *a, color *b) {
    color temp = *a;
    *a = *b;
    *b = temp;
}

int getNextGap(u32 gap)
{
    gap = (gap*10)/13;
 
    if (gap < 1)
        return 1;
    return gap;
}
 

 // El buen combSort
void combSort(color a[], u32 n)
{
    u32 gap = n;
    bool swapped = true;

    while (gap != 1 || swapped == true)
    {
        // Find next gap
        gap = getNextGap(gap);
 
        // Initialize swapped as false so that we can
        // check if swap happened or not
        swapped = false;
 
        for (u32 i=0; i<n-gap; i++)
        {
            if (a[i] > a[i+gap])
            {
                swap(&a[i], &a[i+gap]);
                swapped = true;
            }
        }
    }
}

void printArray(color arr[], u32 size) {
    for (u32 i = 0; i < size; i++)
        printf("%u ", arr[i]);
    printf("\n");
}

bool biyectivo(u32* arr, u32 tam){
    bool es_biy = true;
    u32 conj_nat[tam];

    // Inicializo en 0;
    for(u32 i = 0; i < tam; ++i){
        conj_nat[i] = 0;
    }

    // Marco los valores
    for(u32 i = 0; i < tam; ++i){
        if(arr[i] < tam){
            conj_nat[arr[i]] = 1;
        }
    }

    // Compruebo que todos los valores {0..n-1} estén marcados
    for(u32 i = 0; i < tam; ++i){
        if(conj_nat[i] != 1){
            es_biy = false;
            break;
        }
    }
    return es_biy;
}


u32 Greedy(Grafo G, u32* Orden){

    u32 n = NumeroDeVertices(G);
    u32 m = NumeroDeLados(G);

    if(!biyectivo(Orden, n)){
        return U32_MAX;
    }

    color globalCol[n];
    AsignarColor(0, Orden[0], G);
    globalCol[0] = Color(0, G);
    u32 cantidad_colores = 1;

    for(u32 i = 1; i < n; i++){
        u32 actual_vert = Orden[i];
        u32 actual_grado = Grado(actual_vert, G);
        color actual_col[actual_grado];
        for(u32 j = 0; j < actual_grado; j++){

            // Marco el arreglo de colores y lo relleno con sus colores
            u32 actual_vecino = Vecino(j, i, G);
            actual_col[j] = Color(actual_vecino, G);
        }

        color min_sin_usar = 0;
        combSort(actual_col, actual_grado);
        // Buscamos el menor "hueco" disponible 
        // Ej: [0, 0, 0, 1, 1, 2, 4,..] --> 3 es el menor hueco disponible
        for(u32 j = 0; j < actual_grado; j++){
            printf("min_sin_usar: %u\n actual_col[%u]: %u\n", min_sin_usar, j, actual_col[j]);
            if(min_sin_usar == actual_col[j]){
                min_sin_usar++;
            }
            else if(min_sin_usar < actual_col[j]) {
                break;
            }
        }
        printf("\n numero elegido: %u\n", min_sin_usar);
        globalCol[i] = min_sin_usar;
        AsignarColor(globalCol[i],i, G);
        if(cantidad_colores == min_sin_usar){
            cantidad_colores++;
        }
    }

    return cantidad_colores;
}



char GulDukat(Grafo G, u32* Orden);

char ElimGarak(Grafo G, u32* Orden);
