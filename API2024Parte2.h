

#include "APIG24.h"
#include <stdbool.h>


bool biyectivo(u32* arr, u32 tam);

u32 Greedy(Grafo G, u32* Orden);

void quickSortGrado(u32 arr[], u32 low, u32 high, Grafo G);

void printArrayGrado(u32 arr[], Grafo G, u32 size);

void printArray(u32 arr[],u32 size);

char GulDukat(Grafo G, u32* Orden);

char ElimGarak(Grafo G, u32* Orden);

