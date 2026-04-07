#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10

typedef struct No
{
    int vertice;
    struct No *proximo;
} No;

No *lista[MAX_VERTICES];
int num_vertices;

// Converte índice para letra: 0 -> 'A', 1 -> 'B', ...
char vertice_para_letra(int i) {
    return 'A' + i;
}

void inicializar(int n)
{
    num_vertices = n;
    for (int i = 0; i < n; i++)
        lista[i] = NULL;
}

void adicionar_vizinho(int origem, int destino)
{
    No *novo = (No *)malloc(sizeof(No));
    novo->vertice = destino;
    novo->proximo = lista[origem];
    lista[origem] = novo;
}

void adicionar_aresta(int u, int v)
{
    adicionar_vizinho(u, v);
    adicionar_vizinho(v, u); // grafo não-dirigido
}

void imprimir_lista()
{
    printf("Lista de Adjacencia:\n\n");
    for (int i = 0; i < num_vertices; i++)
    {
        printf("  Vertice %c: ", vertice_para_letra(i));
        No *atual = lista[i];
        while (atual != NULL)
        {
            printf("%c", vertice_para_letra(atual->vertice));
            if (atual->proximo != NULL)
                printf(" -> ");
            atual = atual->proximo;
        }
        printf("\n");
    }
}

void calcular_grau()
{
    printf("\nGrau de cada vertice:\n");
    for (int i = 0; i < num_vertices; i++)
    {
        int grau = 0;
        No *atual = lista[i];
        while (atual != NULL)
        {
            grau++;
            atual = atual->proximo;
        }
        printf("  Vertice %c: grau %d\n", vertice_para_letra(i), grau);
    }
}

void liberar_memoria()
{
    for (int i = 0; i < num_vertices; i++)
    {
        No *atual = lista[i];
        while (atual != NULL)
        {
            No *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
}

int main()
{
    inicializar(5);

    // A=0, B=1, C=2, D=3, E=4
    adicionar_aresta(0, 1); // A -- B
    adicionar_aresta(0, 2); // A -- C
    adicionar_aresta(1, 3); // B -- D
    adicionar_aresta(2, 3); // C -- D
    adicionar_aresta(3, 4); // D -- E

    imprimir_lista();
    calcular_grau();

    liberar_memoria();
    return 0;
}
