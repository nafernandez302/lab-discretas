#include "APIG24.h"
#include "API2024Parte2.h"
#include <stdbool.h>
#include <assert.h>

#define U32_MAX 4294967295
#define SUCCESS '0'
#define FAILURE '1'


typedef struct _bucket{
    color c;
    u32 gradoMax;
    u32 gradoMin;
    u32 sumM;
    u32 cantVert;
    u32* vertices;
} bucket;

/*

bucket[0].vertices: [1,5,10]
bucket[1].vertices: [2,4];
..




*/




static u32 min (u32 a, u32 b){
    return a < b ? a : b;
}

static u32 max (u32 a, u32 b){
    return a > b ? a : b;
}

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


/*


bucket0 0  0  0  0
        v1 v2 v4 v5



*/
// Imprime los vertices de un arreglo
static void printArray(u32 arr[], u32 size) {
    for (u32 i = 0; i < size; i++){
        printf("%u ", arr[i]);
    }
    printf("\n");
}

void swap(color* a, color* b) {
    color temp = *a;
    *a = *b;
    *b = temp;
}



void swapQuickSort(u32* a, u32* b)
{
    u32 temp = *a;
    *a = *b;
    *b = temp;
}

void swapBucket(bucket* a, bucket* b){
    bucket temp = *a;
    *a = *b;
    *b = temp;
}

u32 partitionM(bucket arr[], u32 low, u32 high)
{
    u32 pivot = arr[low].gradoMax;
    u32 i = low;
    u32 j = high;

    while (i < j) {
        while (arr[i].gradoMax<= pivot && i <= high - 1) {
            i++;
        }
        while (arr[j].gradoMax > pivot && j >= low + 1) {
            if(j == 0) break;
            j--;
        }
        if (i < j) {
            //printf("swap entre %u y %u\n", arr[i], arr[j]);
            swapBucket(&arr[i], &arr[j]);
        }
    }
    swapBucket(&arr[low], &arr[j]);
    return j;
}

u32 partitionm(bucket arr[], u32 low, u32 high)
{
    u32 pivot = arr[low].gradoMin;
    u32 i = low;
    u32 j = high;

    while (i < j) {
        while (arr[i].gradoMin<= pivot && i <= high - 1) {
            i++;
        }
        while (arr[j].gradoMin > pivot && j >= low + 1) {
            if(j == 0) break;
            j--;
        }
        if (i < j) {
            //printf("swap entre %u y %u\n", arr[i], arr[j]);
            swapBucket(&arr[i], &arr[j]);
        }
    }
    swapBucket(&arr[low], &arr[j]);
    return j;
}

u32 partitions(bucket arr[], u32 low, u32 high)
{
    u32 pivot = arr[low].sumM;
    u32 i = low;
    u32 j = high;

    while (i < j) {
        while (arr[i].sumM<= pivot && i <= high - 1) {
            i++;
        }
        while (arr[j].sumM > pivot && j >= low + 1) {
            if(j == 0) break;
            j--;
        }
        if (i < j) {
            //printf("swap entre %u y %u\n", arr[i], arr[j]);
            swapBucket(&arr[i], &arr[j]);
        }
    }
    swapBucket(&arr[low], &arr[j]);
    return j;
}

u32 partitione(bucket arr[], u32 low, u32 high)
{
    u32 pivot = arr[low].cantVert;
    u32 i = low;
    u32 j = high;

    while (i < j) {
        while (arr[i].cantVert<= pivot && i <= high - 1) {
            i++;
        }
        while (arr[j].cantVert > pivot && j >= low + 1) {
            if(j == 0) break;
            j--;
        }
        if (i < j) {
            //printf("swap entre %u y %u\n", arr[i], arr[j]);
            swapBucket(&arr[i], &arr[j]);
        }
    }
    swapBucket(&arr[low], &arr[j]);
    return j;
}

u32 partition(u32 arr[], u32 low, u32 high)
{

    u32 pivot = arr[low];
    u32 i = low;
    u32 j = high;

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

void quickSort(bucket arr[], u32 low, u32 high, char modo)
{

    if (low < high && high != U32_MAX) {
        u32 partitionIndex = 0;
        // Modo M(x)
        if (modo == 'M') { // Modo M(x)
            partitionIndex = partitionM(arr, low, high);
        }
        else if (modo == 'm') { // Modo m(x)
            partitionIndex = partitionm(arr, low, high);
        }
        else if (modo == 's'){ // Modo M(x) + m(x)
            partitionIndex = partitions(arr, low, high);
        }
        else if(modo == 'e'){ // Modo ElimGarak
            partitionIndex = partitione(arr, low, high);
        }
        quickSort(arr, low, partitionIndex - 1, modo);
        quickSort(arr, partitionIndex + 1, high, modo);
    }
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

void quickSort1(u32 arr[], u32 low, u32 high)
{

    if (low < high && high != U32_MAX) {
        u32 partitionIndex = 0;
        partitionIndex = partition(arr, low, high);
        quickSort1(arr, low, partitionIndex - 1);
        quickSort1(arr, partitionIndex + 1, high);
    }
}

bool coloreoPropio(Grafo G){
    bool es_propio = true;
    u32 n = NumeroDeVertices(G);
    for(u32 i = 0; i < n; i++){
        for(u32 j = 0; j < Grado(i,G); j++){
            u32 vecino_actual = Vecino(j,i, G);
            es_propio &= Color(i, G) != Color(vecino_actual, G);
        }
    }

    return es_propio;
}

u32 Greedy(Grafo G, u32* Orden) { 

    u32 n = NumeroDeVertices(G);
    printf("n: %u, m:%u\n", n, NumeroDeLados(G));
    if (!biyectivo(Orden, n)) {
        return U32_MAX;
    }

    color globalCol[n];
    u32 usados[n];
    
    for (u32 i = 0; i < n; i++)
    {
        globalCol[i] = 0;
        usados[i] = 0;
    }
    globalCol[Orden[0]] = 1;
    AsignarColor(globalCol[Orden[0]], Orden[0], G);

    u32 cantidad_colores = 1;

    for (u32 i = 1; i < n; i++) {
        u32 actual_vert = Orden[i];
        u32 actual_grado = Grado(actual_vert, G);
        color actual_col[actual_grado];
        for(u32 j = 0; j < actual_grado; j++){
            usados[j] = 0;
        }
        for (u32 j = 0; j < actual_grado; j++) {
            
            // Marco el arreglo de colores y lo relleno con sus colores
            u32 actual_vecino = Vecino(j, Orden[i], G);
            actual_col[j] = globalCol[actual_vecino];
            if(actual_col[j] != 0){
                usados[actual_col[j] - 1] = 1;
            }
        }

        color min_sin_usar = 1;
        // Buscamos el menor "hueco" disponible 
        // Ej: [0, 0, 0, 1, 1, 2, 4,..] --> 3 es el menor hueco disponible
        for (u32 j = 0; j < actual_grado; j++) {
            if (usados[j] == 1) {
                min_sin_usar++;
            }
            else{
                break;
            }
        }
        assert(min_sin_usar != 0);
        globalCol[Orden[i]] = min_sin_usar;
        AsignarColor(min_sin_usar, actual_vert , G);
        if (cantidad_colores < min_sin_usar) {
            cantidad_colores = min_sin_usar;
        }
    }

    //printArrayColor(Orden, G, n);
    //printArray(Orden, n);

    assert(coloreoPropio(G));
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
    u32 r = 0;
    // Para saber el grado máximo del color i
    u32 contar_colores[n];


    for(u32 i = 0; i<n;i++){
        contar_colores[i] = 0;
    }
    for(u32 i = 0; i<n;i++){
        assert(Color(i,G) != 0);
        contar_colores[Color(i,G)-1] = 1;
    }
    for(u32 i = 0; i<n; i++){
        if(contar_colores[i] == 1){
            r++;
        }
    }

    struct _bucket b[r];

    for (u32 i = 0; i < r; i++){
        b[i].c = i+1;
        b[i].gradoMax = 0;
        b[i].gradoMin = U32_MAX;
        b[i].cantVert = 0;
        b[i].vertices = malloc(sizeof(u32) * n);
    }

    //Itera sobre los vértices y va clasificándolos según las características de sus colores.
    for (u32 i = 0; i < n; i++) { // CHEQUEAR
        
        verticeActual = i;
        if(Color(verticeActual, G) == 0){
            printf("el vertice %u no se pintó bien\n", i);
        }
        colorVertActual = Color(verticeActual, G) - 1;
        b[colorVertActual].gradoMax = max(b[colorVertActual].gradoMax, Grado(i, G));
        b[colorVertActual].gradoMin = min(b[colorVertActual].gradoMin, Grado(i, G));
        //printf("cantVert: %u, vertactual: %u\n", b[colorVertActual].cantVert, verticeActual);
        u32 pos = b[colorVertActual].cantVert;
        b[colorVertActual].vertices[pos] = verticeActual;
        assert(Color(verticeActual, G) == Color(b[colorVertActual].vertices[pos], G));
        //printf("%u, %u\n", b[colorVertActual].c, Color(verticeActual, G));
        b[colorVertActual].cantVert++;
        //printArrayColor(b[colorVertActual].vertices, G, b[colorVertActual].cantVert);
        //Hasta ahora tenemos los bloques listos, falta ordenarlos de acuerdo a la especificación.
    }

    for(u32 i = 0; i < r; i++){
        b[i].sumM = b[i].gradoMax + b[i].gradoMin; 
    }

    /*
    for(u32 i = 0; i < r; i++){
        printf("b %u, de tamaño %u\n", i, b[i].cantVert);
        printArrayColor(b[i].vertices, G, b[i].cantVert);
    }
    */

    u32 countX1 = 0;
    u32 countX2 = 0;
    u32 countX3 = 0;

    struct _bucket x1[r];
    struct _bucket x2[r];
    struct _bucket x3[r];
    for(u32 i = 0; i < r;i++){
        if(b[i].c % 4 == 0){
            x1[countX1] = b[i];
            countX1++;
        }
        else if(b[i].c % 4 == 2){
            x2[countX2] = b[i];
            countX2++;
        }
        else{
            x3[countX3] = b[i];
            countX3++;
        }
    }

    
    // b1 < b2 sii    b1.maxGrado < b2.maxGrado

    
    quickSort(x1, 0, countX1 - 1, 'M');
    quickSort(x2, 0, countX2 - 1, 's');
    quickSort(x3, 0, countX3 - 1, 'm');
    
    u32 cant_actual = 0;
    for(u32 i = 0; i < countX1; ++i){
        for(u32 j = 0; j < x1[i].cantVert; j++){
            Orden[cant_actual] = x1[i].vertices[j];
            cant_actual++;
        }
    }

    for(u32 i = 0; i < countX2; ++i){
        for(u32 j = 0; j < x2[i].cantVert; j++){
            Orden[cant_actual] = x2[i].vertices[j];
            cant_actual++;
        }
    }
    for(u32 i = 0; i < countX3; ++i){
        for(u32 j = 0; j < x3[i].cantVert; j++){
            Orden[cant_actual] = x3[i].vertices[j];
            cant_actual++;
        }
    }

    // Free de los buckets

    for (u32 i = 0; i < r; i++){
        free(b[i].vertices);
    }

    assert(biyectivo(Orden, NumeroDeVertices(G)));
    return SUCCESS;
}

char ElimGarak(Grafo G, u32* Orden){

    u32 n = NumeroDeVertices(G);
    u32 verticeActual;
    u32 colorVertActual;
    u32 r = 0;
    color colorGradoMaximo[n];
    color colorGradoMinimo[n];
    // Para saber el grado máximo del color i
    u32 contar_colores[n];


    for(u32 i = 0; i<n;i++){
        contar_colores[i] = 0;
    }
    for(u32 i = 0; i<n;i++){
        assert(Color(i,G) != 0);
        contar_colores[Color(i,G)-1] = 1;
    }
    for(u32 i = 0; i<n; i++){
        if(contar_colores[i] == 1){
            r++;
        }
    }

    struct _bucket b[r];

    // Inicialización de buckets
    for (u32 i = 0; i < r; i++){
        b[i].c = i+1;
        b[i].cantVert = 0;
        b[i].vertices = malloc(sizeof(u32) * n);
    }

    // Llenado de buckets
    for (u32 i = 0; i < n; i++) { 
        verticeActual = i;
        if(Color(verticeActual, G) == 0){
            printf("el vertice %u no se pintó bien\n", i);
        }
        colorVertActual = Color(verticeActual, G) - 1;
        //printf("cantVert: %u, vertactual: %u\n", bucket[colorVertActual].cantVert, verticeActual);
        u32 pos = b[colorVertActual].cantVert;
        b[colorVertActual].vertices[pos] = verticeActual;
        assert(Color(verticeActual, G) == Color(b[colorVertActual].vertices[pos], G));
        b[colorVertActual].cantVert++;
        //Hasta ahora tenemos los bloques listos, falta ordenarlos de acuerdo a la especificación.
    }  


    struct _bucket bucket_a_ordenar[r];

    u32 comienzo = 2;
    // i comienza en 2 ya que bucket[0] y bucket[1] tienen los colores 1 y 2 respect.
    for(u32 i = comienzo; i < r; ++i){
        bucket_a_ordenar[i-2] = b[i];
    }

    // Ordenamos de acuerdo al que tenga mínimo color
    quickSort(bucket_a_ordenar, 0, r - 3, 'e');

    u32 cant_actual = 0;
    for(u32 i = comienzo; i < r; ++i){
        for(u32 j = 0; j < bucket_a_ordenar[i-2].cantVert; j++){
            Orden[cant_actual] = bucket_a_ordenar[i-2].vertices[j];
            cant_actual++;
        }
    }
    // Ahora pongo los de color 2, que estan en el bucket1
    for(u32 j = 0; j < b[1].cantVert; j++){
        Orden[cant_actual] = b[1].vertices[j];
        cant_actual++;
    }

    // Ahora pongo los de color 1, que estan en el bucket0
    for(u32 j = 0; j < b[0].cantVert; j++){
        Orden[cant_actual] = b[0].vertices[j];
        cant_actual++;
    }


    // Free de los buckets

    for (u32 i = 0; i < r; i++){
        free(b[i].vertices);
    }

    assert(biyectivo(Orden, n));
    return SUCCESS;
}
