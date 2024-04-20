#include "APIG24.h"
#include "API2024Parte2.h"
#include <stdbool.h>

#define U32_MAX 4294967295
#define SUCCESS '0'
#define FAILURE '1'

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

/*void combSort(color a[], u32 n)
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
}*/

void swapQuickSort(u32* a, u32* b) 
{ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 

int partitionM(u32 arr[], int low, int high, Grafo G) 
{ 
  
    u32 pivot = Grado(arr[low], G); 
    int i = low; 
    int j = high; 
  
    while (i < j) {  
        while (Grado(arr[i],G) <= pivot && i <= high - 1) { 
            i++; 
        } 
        while (Grado(arr[j],G) > pivot && j >= low + 1) { 
            j--; 
        } 
        if (i < j) { 
            swapQuickSort(&arr[i], &arr[j]); 
        } 
    } 
    swapQuickSort(&arr[low], &arr[j]); 
    return j; 
} 

int partition(u32 arr[], int low, int high) 
{ 
  
    u32 pivot = arr[low]; 
    int i = low; 
    int j = high; 
  
    while (i < j) {  
        while (arr[i] <= pivot && i <= high - 1) { 
            i++; 
        } 
        while (arr[j] > pivot && j >= low + 1) { 
            j--; 
        } 
        if (i < j) { 
            swapQuickSort(&arr[i], &arr[j]); 
        } 
    } 
    swapQuickSort(&arr[low], &arr[j]); 
    return j; 
} 
  
void quickSort(u32 arr[], int low, int high, Grafo G, char modo) 
{
    
    if (low < high) { 
        int partitionIndex;
        if (modo == 'M'){
            partitionIndex = partitionM(arr, low, high, G); 
        } else {
            partitionIndex = partition(arr, low, high);
        } 
        quickSort(arr, low, partitionIndex - 1, G, modo); 
        quickSort(arr, partitionIndex + 1, high, G, modo); 
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
    //u32 m = NumeroDeLados(G);

    if(!biyectivo(Orden, n)){
        return U32_MAX;
    }

    color globalCol[n];
    AsignarColor(0, Orden[0], G);
    globalCol[0] = Color(0, G);
    u32 cantidad_colores = 1;

    for(u32 i = 1; i < n; i++) {
        u32 actual_vert = Orden[i];
        u32 actual_grado = Grado(actual_vert, G);
        color actual_col[actual_grado];
        for(u32 j = 0; j < actual_grado; j++){

            // Marco el arreglo de colores y lo relleno con sus colores
            u32 actual_vecino = Vecino(j, i, G);
            actual_col[j] = Color(actual_vecino, G);
        }

        color min_sin_usar = 0;
        //combSort(actual_col, actual_grado);
        quickSort(actual_col, 0, actual_grado-1, G, 'g');
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

//Retorna el mínimo grado de los vértices con color x del grafo G.
u32 m(u32 x, Grafo G){
    u32 gradoActual;
    u32 n = NumeroDeVertices(G);
    u32 minGrado = U32_MAX;
    for(u32 i = 1; i <= n; i++){
        if(Color(i,G) == x){
            gradoActual = Grado(i,G);
            if(gradoActual < minGrado){
                minGrado = gradoActual;
            }
        }
    }
    return minGrado;
}

//Retorna el mayor grado de los vértices con color x del grafo G.
u32 M(u32 x, Grafo G){
    u32 gradoActual;
    u32 n = NumeroDeVertices(G);
    u32 maxGrado = 0;
    for(u32 i = 1; i <= n; i++){
        if(Color(i,G) == x) {
            gradoActual = Grado(i,G);
            if(gradoActual > maxGrado){
                maxGrado = gradoActual;
            }
        }
        
    }
    return maxGrado;
}


char GulDukat(Grafo G, u32* Orden) {
    u32 n = NumeroDeVertices(G);
    u32 verticeActual;
    u32 colorVertActual;
    u32 ult_posX1 = 0;
    u32 ult_posX2 = 0;
    u32 ult_posX3 = 0;
    u32 x1[n];
    u32 x2[n];
    u32 x3[n];
    //Para saber la cantidad de colores independientemente de la implementación.
    color arrayColores[n]; 
    ExtraerColores(G,arrayColores);
    //Itera sobre los vértices y va clasificándolos según las características de sus colores.
    for(u32 i = 0; i < n; i++){ // CHEQUEAR
        verticeActual = i;
        colorVertActual = Color(verticeActual,G);
        if(colorVertActual % 4 == 0) {
            x1[ult_posX1] = verticeActual;
            ult_posX1++;
        } else if (colorVertActual % 4 != 0 && colorVertActual % 2 == 0) {
            x2[ult_posX2] = verticeActual;
            ult_posX2++;
        } else if (colorVertActual % 2 != 0) {
            x3[ult_posX3] = verticeActual;
            ult_posX3++;
        }
        //Hasta ahora tenemos los bloques listos, falta ordenarlos de acuerdo a la especificación.
    }        
    int largoX1 = ult_posX1;
    //Ordenar X1 según M(x)
    /*
    u32 x1Sorted[];
    int x1SortedPos = 0;
    int maxMinimoGrado = 0;
    u32 maxVert = 0;
    for(j = 0)
        for(i = 0; i < largoX1; i++){
            gradoActual = Grado(i,G);
            if(gradoActual > maxMinimoGrado){
                maxMinimoGrado = gradoActual;
                maxVert = i;
            }
        }
        x1Sorted[x1SortedPos] = maxVert;
    */
    quickSort(x1, 0, largoX1 - 1, G, 'M');
    //REVERSE X1
    
    printArray(x1, largoX1);
    return SUCCESS;
}

char ElimGarak(Grafo G, u32* Orden);
