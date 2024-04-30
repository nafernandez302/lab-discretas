#include "APIG24.h"
#include "EstructuraGrafo24.h"
#include <limits.h>

#define SIZE 200 // recomendado para poca memoria ram 2-4gb : 200, en caso de tener mas memoria se puede aumentar este numero

Grafo ConstruirGrafo()
{
    char inicio;
    // busca si hay lineas comentario en el archivo y las saltea
    while (scanf(" %c",&inicio) == 1 && inicio == 'c')
    {
        while((char)getchar() != '\n');
    }
    // si encuentra algo distinto de comentario o el inicio del grafo, devuelve grafo vacio
    if(inicio != 'p') return NULL;

    u32 numero_de_vertices , numero_de_lados;
    int error_code = scanf(" edge %u %u", &numero_de_vertices , &numero_de_lados);
    if(error_code != 2)
    {
        return NULL;
    }
    Grafo g = malloc(sizeof(struct _grafo));
    g->n = numero_de_vertices;
    g->m = numero_de_lados;
    g->delta = 0u;
    g->vertices = malloc((g->n)*sizeof(struct _data));
    g->vecinos = malloc((g->n)*sizeof(u32*));
    // ciclo para inicilizar el struct data
    // y tambien aprovecho el ciclo para crear la matriz N x N
    for (u32 i = 0; i < g->n; ++i)
    {
        g->vertices[i].color = 0;
        g->vertices[i].grado = 0;
        g->vertices[i].size = SIZE;
        g->vecinos[i] = malloc(SIZE*sizeof(u32));
    }
    u32 check_m = 0u;
    for (u32 i = 0u; i < g->m; ++i)
    {
        u32 vertice_x , vertice_y; // juntos forman el lado xy
        int error_code = scanf("\ne %u %u", &vertice_x , &vertice_y);
        if(error_code != 2)
        {
        	DestruirGrafo(g);
        	return NULL;
        }
        // llenado de la matriz de vecinos en un mismo ciclo para ahorrar costo
        g->vecinos[vertice_x][(g->vertices[vertice_x].grado)] = vertice_y; // con vertice_x un numero entre 0 y n por lo tanto no se sale de la matriz
        g->vecinos[vertice_y][(g->vertices[vertice_y].grado)] = vertice_x; // con vertice_y un numero entre 0 y n por lo tanto no se sale de la matriz
        
        // si la cantidad de vecinos llega a la cantidad SIZE definidad arriba esta cantidad se duplica para darle mas espacio al array
        if(g->vertices[vertice_x].grado >= g->vertices[vertice_x].size)
        {
            g->vertices[vertice_x].size = 2*g->vertices[vertice_x].size;
            g->vecinos[vertice_x] = realloc(g->vecinos[vertice_x] , g->vertices[vertice_x].size* sizeof(u32));
        }
        g->vertices[vertice_x].grado += 1;
        if(g->vertices[vertice_y].grado >= g->vertices[vertice_y].size)
        {
            g->vertices[vertice_y].size = 2*g->vertices[vertice_y].size;
            g->vecinos[vertice_y] = realloc(g->vecinos[vertice_y] , g->vertices[vertice_y].size* sizeof(u32));
        }
        g->vertices[vertice_y].grado += 1;

        check_m++;
    }
    if(check_m!=g->m)
    {
        DestruirGrafo(g);
        return NULL;
    }

    // calculo delta
    for (u32 i = 0u; i < g->n; ++i)
    {
        if(g->delta < g->vertices[i].grado)
        {
            g->delta = g->vertices[i].grado;
        }
    }
    
    return g;
}

void DestruirGrafo(Grafo g)
{
    if(g != NULL) 
    {
        for (u32 i = 0; i < g->n; ++i)
        {
            free(g->vecinos[i]);
        }
        free(g->vecinos);
        free(g->vertices);
        free(g);
        g = NULL;
    }
}

u32 NumeroDeVertices(Grafo g)
{
    if(g != NULL)
    {
        return g->n;
    }
    else
    {
        return 0u; 
    }
}

u32 NumeroDeLados(Grafo g)
{
    if(g != NULL)
    {
        return g->m;
    }
    else
    {
        return 0u;  
    }
}

u32 Delta(Grafo g)
{
    if(g != NULL)
    {
        return g->delta;
    }
    else
    {
        return 0u;    
    }
}

u32 Grado(u32 i,Grafo g)
{
    if(g != NULL && i < g->n)
    {
        return g->vertices[i].grado;
    }
    else
    {
        return 0u;
    }
}

color Color(u32 i,Grafo g)
{
    if(g != NULL && i < g->n)
    {
        return g->vertices[i].color;
    }
    else
    {
        return INT_MAX;
    }
}

u32 Vecino(u32 j,u32 i,Grafo g)
{
    if(g != NULL && i < g->n && j < g->vertices[i].grado)
    {
        return g->vecinos[i][j];
    }
    else
    {
        return INT_MAX;
    }
}

void AsignarColor(color x,u32 i,Grafo  g)
{
    if(g != NULL && i < g->n)
    {
        g->vertices[i].color = x;
    }
}

void ExtraerColores(Grafo g,color* c)
{
    if(g != NULL)
    {
        for (u32 i = 0; i < g->n; ++i)
        {
            c[i] = g->vertices[i].color;
        }
    }
}

void ImportarColores(color* c,Grafo  g)
{
    if(g != NULL)
    {
        for (u32 i = 0; i < g->n; ++i)
        {
            g->vertices[i].color = c[i];
        }
    }
}
