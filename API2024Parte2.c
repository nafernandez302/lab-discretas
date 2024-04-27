#include "APIG24.h"
#include "API2024Parte2.h"
#include <stdbool.h>

#define U32_MAX 4294967295
#define SUCCESS '0'
#define FAILURE '1'

static u32 min (u32 a, u32 b){
    return a < b ? a : b;
}

static u32 max (u32 a, u32 b){
    return a > b ? a : b;
}

void swap(color* a, color* b) {
    color temp = *a;
    *a = *b;
    *b = temp;
}



void swapQuickSort(u32* a, u32* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partitionM(u32 arr[], int low, int high, Grafo G, color arrayMaximos[])
{

    u32 pivot = Grado(arr[low], G);
    int i = low;
    int j = high;

    while (i < j) {
        while (Grado(arr[i], G) <= pivot && i <= high - 1) {
            i++;
        }
        while (Grado(arr[j], G) > pivot && j >= low + 1) {
            j--;
        }
        if (arrayMaximos[i] < arrayMaximos[j]) {
            swapQuickSort(&arr[i], &arr[j]);
        }
    }
    swapQuickSort(&arr[low], &arr[j]);
    return j;
}

int partitionm(u32 arr[], int low, int high, Grafo G, color arrayMinimos[])
{

    u32 pivot = Grado(arr[low], G);
    int i = low;
    int j = high;

    while (i < j) {
        while (Grado(arr[i], G) <= pivot && i <= high - 1) {
            i++;
        }
        while (Grado(arr[j], G) > pivot && j >= low + 1) {
            j--;
        }
        if (arrayMinimos[i] < arrayMinimos[j]) {
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

void quickSort(u32 arr[], int low, int high, Grafo G, char modo, color arrayMaximos[], color arrayMinimos[], color colorGradoSum[])
{

    if (low < high) {
        int partitionIndex;
        if (modo == 'M') {
            partitionIndex = partitionM(arr, low, high, G, arrayMaximos);
        }
        else if (modo == 'm') {
            partitionIndex = partitionm(arr, low, high, G, arrayMinimos);
        } else {
            partitionIndex = partition(arr, low, high);

        }
        quickSort(arr, low, partitionIndex - 1, G, modo, arrayMaximos, arrayMinimos, colorGradoSum);
        quickSort(arr, partitionIndex + 1, high, G, modo, arrayMaximos, arrayMinimos, colorGradoSum);
    }
}

static void reverseArr(u32 arr[], u32 n) {
    for (u32 i = 0; i < (n / 2); i++) {
        swapQuickSort(&arr[i], &arr[n - i - 1]);
    }
}


// Imprime los grados de un arreglo
static void printArrayGrado(u32 arr[], Grafo G, u32 size) {
    for (u32 i = 0; i < size; i++) {
        printf("%u ", Grado(arr[i], G));
    }
    printf("\n");
}

static void printArrayColor(u32 arr[], Grafo G, u32 size) {
    for (u32 i = 0; i < size; i++) {
        printf("%u ", Color(arr[i], G));
    }
    printf("\n");
}

// Imprime los vertices de un arreglo
static void printArray(u32 arr[], u32 size) {
    for (u32 i = 0; i < size; i++){
        printf("%u ", arr[i]);
    }
    printf("\n");
}

bool biyectivo(u32* arr, u32 tam) {
    bool es_biy = true;
    u32 conj_nat[tam];

    // Inicializo en 0;
    for (u32 i = 0; i < tam; ++i) {
        conj_nat[i] = 0;
    }

    // Marco los valores
    for (u32 i = 0; i < tam; ++i) {
        if (arr[i] < tam) {
            conj_nat[arr[i]] = 1;
        }
    }

    // Compruebo que todos los valores {0..n-1} estén marcados
    for (u32 i = 0; i < tam; ++i) {
        if (conj_nat[i] != 1) {
            es_biy = false;
            break;
        }
    }
    return es_biy;
}

void quickSort1(u32 arr[], int low, int high, Grafo G, char modo)
{

    if (low < high) {
        int partitionIndex;
        partitionIndex = partition(arr, low, high);
        quickSort1(arr, low, partitionIndex - 1, G, modo);
        quickSort1(arr, partitionIndex + 1, high, G, modo);
    }
}

u32 Greedy(Grafo G, u32* Orden) {

    u32 n = NumeroDeVertices(G);

    if (!biyectivo(Orden, n)) {
        return U32_MAX;
    }

    color globalCol[n];
    AsignarColor(0, Orden[0], G);
    globalCol[0] = Color(0, G);
    u32 cantidad_colores = 1;

    for (u32 i = 1; i < n; i++) {
        u32 actual_vert = Orden[i];
        u32 actual_grado = Grado(actual_vert, G);
        color actual_col[actual_grado];
        for (u32 j = 0; j < actual_grado; j++) {

            // Marco el arreglo de colores y lo relleno con sus colores
            u32 actual_vecino = Vecino(j, i, G);
            actual_col[j] = Color(actual_vecino, G);
        }

        color min_sin_usar = 0;
        //combSort(actual_col, actual_grado);
        quickSort1(actual_col, 0, actual_grado - 1, G, 'g');
        // Buscamos el menor "hueco" disponible 
        // Ej: [0, 0, 0, 1, 1, 2, 4,..] --> 3 es el menor hueco disponible
        for (u32 j = 0; j < actual_grado; j++) {
            if (min_sin_usar == actual_col[j]) {
                min_sin_usar++;
            }
            else if (min_sin_usar < actual_col[j]) {
                break;
            }
        }
        globalCol[i] = min_sin_usar;
        AsignarColor(globalCol[i], i, G);
        if (cantidad_colores == min_sin_usar) {
            cantidad_colores++;
        }
    }

    return cantidad_colores;
}

//Retorna el mínimo grado de los vértices con color x del grafo G.
u32 m(u32 x, Grafo G) {
    u32 gradoActual;
    u32 n = NumeroDeVertices(G);
    u32 minGrado = U32_MAX;
    for (u32 i = 1; i <= n; i++) {
        if (Color(i, G) == x) {
            gradoActual = Grado(i, G);
            if (gradoActual < minGrado) {
                minGrado = gradoActual;
            }
        }
    }
    return minGrado;
}

//Retorna el mayor grado de los vértices con color x del grafo G.
u32 M(u32 x, Grafo G) {
    u32 gradoActual;
    u32 n = NumeroDeVertices(G);
    u32 maxGrado = 0;
    for (u32 i = 1; i <= n; i++) {
        if (Color(i, G) == x) {
            gradoActual = Grado(i, G);
            if (gradoActual > maxGrado) {
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
    color colorGradoMaximo[n];
    color colorGradoMinimo[n];
    // Para saber el grado máximo del color i
    for (u32 i = 0; i < n; n++){
        colorGradoMaximo[i] = 0;
    }

    // Para saber el grado mínimo del color i
    for (u32 i = 0; i < n; n++){
        colorGradoMinimo[i] = U32_MAX;
    }

    //Itera sobre los vértices y va clasificándolos según las características de sus colores.
    for (u32 i = 0; i < n; i++) { // CHEQUEAR
        verticeActual = i;
        colorVertActual = Color(verticeActual, G);
        colorGradoMaximo[colorVertActual] = max(colorGradoMaximo[i], Grado(i, G));
        colorGradoMinimo[colorVertActual] = min(colorGradoMaximo[i], Grado(i, G));
        if (colorVertActual % 4 == 0) {
            x1[ult_posX1] = verticeActual;
            ult_posX1++;
        }
        else if (colorVertActual % 4 != 0 && colorVertActual % 2 == 0) {
            x2[ult_posX2] = verticeActual;
            ult_posX2++;
        }
        else if (colorVertActual % 2 != 0) {
            x3[ult_posX3] = verticeActual;
            ult_posX3++;
        }
        //Hasta ahora tenemos los bloques listos, falta ordenarlos de acuerdo a la especificación.
    }

    
    u32 largoX1 = ult_posX1;
    u32 largoX2 = ult_posX2;
    u32 largoX3 = ult_posX3;
    u32 colorGradoSum[largoX2];

    for (u32 i = 0; i < largoX2; i++){
        u32 colorDisponible = Color(x2[i], G);
        colorGradoSum[colorDisponible] = colorGradoMaximo[colorDisponible] + colorGradoMinimo[colorDisponible];
    }
    

    printf("---Arreglos sin ordenar--- \n");
    printf("X1\n");
    printArrayGrado(x1, G, largoX1);
    printArrayColor(x1, G, largoX1);
    printf("X2\n");
    printArrayGrado(x2, G, largoX2);
    printArrayColor(x2, G, largoX2);
    printf("X3\n");
    printArrayGrado(x3, G, largoX3);
    printArrayColor(x3, G, largoX3);
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
    quickSort(x1, 0, largoX1 - 1, G, 'M', colorGradoMaximo, colorGradoMinimo, colorGradoSum);
    quickSort(x2, 0, largoX2 - 1, G, 'S', colorGradoSum, colorGradoMinimo, colorGradoSum);
    quickSort(x3, 0, largoX3 - 1, G, 'm', colorGradoMinimo, colorGradoMinimo, colorGradoSum);


    //REVERSE x1, x2, x3

    reverseArr(x1, largoX1);
    reverseArr(x2, largoX2);
    reverseArr(x3, largoX3);
    printf("\n ---Arreglos ordenados y dados vuelta tras quicksort--- \n");
    printf("X1\n");
    printArrayGrado(x1, G, largoX1);
    printArrayColor(x1, G, largoX1);
    printf("X2\n");
    printArrayGrado(x2, G, largoX2);
    printArrayColor(x2, G, largoX2);
    printf("X3\n");
    printArrayGrado(x3, G, largoX3);
    printArrayColor(x3, G, largoX3);
    return SUCCESS;
}

char ElimGarak(Grafo G, u32* Orden);
