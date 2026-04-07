#include <stdio.h>

#define MAX_VERTICES 10

int grafo[MAX_VERTICES][MAX_VERTICES];
int num_vertices;

// Converte índice para letra: 0 -> 'A', 1 -> 'B', ...
char vertice_para_letra(int i) {
    return 'A' + i;
}

void inicializar(int n) {
    num_vertices = n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            grafo[i][j] = 0;
}

void adicionar_aresta(int u, int v) {
    grafo[u][v] = 1;
    grafo[v][u] = 1; // grafo não-dirigido
}

void imprimir_matriz() {
    printf("Matriz de Adjacencia:\n\n");
    printf("   ");
    for (int i = 0; i < num_vertices; i++)
        printf("%2c ", vertice_para_letra(i));
    printf("\n");

    for (int i = 0; i < num_vertices; i++) {
        printf("%2c ", vertice_para_letra(i));
        for (int j = 0; j < num_vertices; j++)
            printf("%2d ", grafo[i][j]);
        printf("\n");
    }
}

void calcular_grau() {
    printf("\nGrau de cada vertice:\n");
    for (int i = 0; i < num_vertices; i++) {
        int grau = 0;
        for (int j = 0; j < num_vertices; j++)
            grau += grafo[i][j];
        printf("  Vertice %c: grau %d\n", vertice_para_letra(i), grau);
    }
}

int main() {
    inicializar(5);

    // A=0, B=1, C=2, D=3, E=4
    adicionar_aresta(0, 1); // A -- B
    adicionar_aresta(0, 2); // A -- C
    adicionar_aresta(1, 3); // B -- D
    adicionar_aresta(2, 3); // C -- D
    adicionar_aresta(3, 4); // D -- E

    imprimir_matriz();
    calcular_grau();

    return 0;
}
