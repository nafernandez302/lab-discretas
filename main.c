#include "APIG24.h"
#include "API2024Parte2.h"
#include <assert.h>
#include <time.h>

#define U32_MAX 4294967295
#define N 9
typedef struct _bucketG {
    u32 cantVert;
    u32* vertices;
} bucketG;

int main()
{
    srand(time(NULL));
    Grafo G = ConstruirGrafo();
    u32 n = NumeroDeVertices(G);

    printf("n: %u, m:%u\n", n, NumeroDeLados(G));
    printf("Delta: %u\n", Delta(G));
    u32 cantidad_it = 0;
    u32* Orden1 = malloc(sizeof(u32) * n);
    u32* Orden2 = malloc(sizeof(u32) * n);
    u32* Orden3 = malloc(sizeof(u32) * n);
    u32* Orden4 = malloc(sizeof(u32) * n);
    u32* Orden5 = malloc(sizeof(u32) * n);
    u32* arr_color = malloc(sizeof(u32) * n);
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

    for (u32 i = 0; i < n; i++) {
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
    struct _bucketG* o = malloc(sizeof(struct _bucketG) * (Delta(G)+1));

    for (u32 i = 0; i < Delta(G)+1; i++) {
        o[i].cantVert = 0;
        o[i].vertices = malloc(sizeof(u32) * n);
    }

    u32 pos;
    for (u32 i = 0; i < n; i++) { 
        pos = o[Grado(i,G)].cantVert;
        o[Grado(i,G)].vertices[pos] = i;
        o[Grado(i,G)].cantVert++;
    }


    u32 cant_actual = 0;
    u32 cant_total = 0;
    for (u32 i = 0; i < Delta(G) + 1; ++i) {
        cant_total += o[i].cantVert;
        for (u32 j = 0; j < o[i].cantVert; j++) {
            Orden4[n -cant_actual - 1] = o[i].vertices[j];
            cant_actual++;
        }
    }


    bool buenOrden = true;
    for (u32 i = 0; i < n-1; i++) {
        if (Grado(Orden4[i], G) < Grado(Orden4[i + 1], G)) {
            buenOrden = false;
            break;
        }
    }

    assert(biyectivo(Orden4, n));
    assert(buenOrden);

    for (u32 i = 0; i < Delta(G)+1; i++) {
        free(o[i].vertices);
    }

    free(o);

    // 5) Orden con un offset de 1
    for (u32 i = 0; i < n - 1; i++) {
        Orden5[i] = i + 1;
    }
    Orden5[n - 1] = 0;

    // primeros prints

    printf("Cantidad de colores usando el orden 1: %u\n", Greedy(G, Orden1));
    printf("Cantidad de colores usando el orden 2: %u\n", Greedy(G, Orden2));
    printf("Cantidad de colores usando el orden 3: %u\n", Greedy(G, Orden3));
    printf("Cantidad de colores usando el orden 4: %u\n", Greedy(G, Orden4));
    printf("Cantidad de colores usando el orden 5: %u\n", Greedy(G, Orden5));

    u32 min_color = U32_MAX;
    u32 coloreo = U32_MAX;

    printf("--- Inicio Orden1 ---\n");
    Greedy(G, Orden1);
    for(u32 i = 0; i < 50; i++){
        GulDukat(G, Orden1);
        coloreo = Greedy(G, Orden1);
        printf("Iteración %u: %u\n", cantidad_it, coloreo);
        cantidad_it++;  
        ElimGarak(G, Orden1);
        coloreo = Greedy(G, Orden1);
        printf("Iteración %u: %u\n", cantidad_it, coloreo);    
        cantidad_it++;
    }
    
    if(coloreo < min_color) {
        min_color = coloreo;
        ExtraerColores(G, arr_color);
    }
    
    printf("--- Inicio Orden2 ---\n");
    Greedy(G, Orden2);
    for(u32 i = 0; i < 50; i++){
        GulDukat(G, Orden2);
        coloreo = Greedy(G, Orden2);
        printf("Iteración %u: %u\n", cantidad_it, coloreo); 
        cantidad_it++;  
        ElimGarak(G, Orden2);
        coloreo = Greedy(G, Orden2);
        printf("Iteración %u: %u\n", cantidad_it, coloreo);  
        cantidad_it++;
    }
    
    if(coloreo < min_color) {
        min_color = coloreo;
        ExtraerColores(G, arr_color);
    }
    free(Orden2);


    printf("--- Inicio Orden3 ---\n");
    Greedy(G, Orden3);
    for(u32 i = 0; i < 50; i++){
        GulDukat(G, Orden3);
        coloreo = Greedy(G, Orden3);
        printf("Iteración %u: %u\n", cantidad_it, coloreo); 
        cantidad_it++;  
        ElimGarak(G, Orden3);
        coloreo = Greedy(G, Orden3);
        printf("Iteración %u: %u\n", cantidad_it, coloreo);  
        cantidad_it++;
    }
    free(Orden3);
    
    if(coloreo < min_color) {
        min_color = coloreo;
        ExtraerColores(G, arr_color);
    } 

    printf("--- Inicio Orden4 ---\n");
    Greedy(G, Orden4);
    for(u32 i = 0; i < 50; i++){
        GulDukat(G, Orden4);
        coloreo = Greedy(G, Orden4);
        printf("Iteración %u: %u\n", cantidad_it, coloreo);  
        cantidad_it++; 
        ElimGarak(G, Orden4);
        coloreo = Greedy(G, Orden4);
        printf("Iteración %u: %u\n", cantidad_it, coloreo); 
        cantidad_it++; 
    }
    free(Orden4);
    
    if(coloreo < min_color) {
        min_color = coloreo;
        ExtraerColores(G, arr_color);
    }

    printf("--- Inicio Orden5 ---\n");
    Greedy(G, Orden5);
    for(u32 i = 0; i < 50; i++){
        GulDukat(G, Orden5);
        coloreo = Greedy(G, Orden5);
        printf("Iteración %u: %u\n", cantidad_it, coloreo); 
        cantidad_it++;  
        ElimGarak(G, Orden5);
        coloreo = Greedy(G, Orden5);
        printf("Iteración %u: %u\n", cantidad_it, coloreo); 
        cantidad_it++; 
    }
    free(Orden5);

    if(coloreo < min_color) {
        min_color = coloreo;
        ExtraerColores(G, arr_color);
    }


    // Iteraciones finales
    printf("--- Iteraciones finales ---\n");
    ImportarColores(arr_color, G);

    int random = 0;
    for(u32 i = 0; i < 500; i++){
        random = rand() % 2;
        if(random == 0){
            GulDukat(G, Orden1); // guardo en Orden1, total no usa Orden1 guldukat
        }
        else{
            ElimGarak(G, Orden1);
        }
        coloreo = Greedy(G, Orden1);
        printf("Iteración %u: %u\n", cantidad_it, coloreo); 
        cantidad_it++; 
    }

    free(Orden1);
    free(arr_color);
    DestruirGrafo(G);

    return 0;
}