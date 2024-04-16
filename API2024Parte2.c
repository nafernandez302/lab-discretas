#include "APIG24.h"
#include "API2024Parte2.h"
#include <stdbool.h>


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


u32 Greedy(Grafo G, u32* Orden);
char GulDukat(Grafo G, u32* Orden);

char ElimGarak(Grafo G, u32* Orden);
