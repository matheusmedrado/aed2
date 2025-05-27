#ifndef GRAFO_H
#define GRAFO_H

/**
 * Estrutura para representação de grafos usando listas de adjacência com encadeamento dinâmico
 */

// Estrutura para um nó na lista de adjacência
typedef struct AdjListNode {
    int vertex;         // Índice do vértice adjacente
    float weight;       // Peso da aresta
    struct AdjListNode* next;  // Próximo nó na lista
} AdjListNode;

// Estrutura para lista de adjacência
typedef struct {
    char* label;        // Etiqueta do vértice
    AdjListNode* head;  // Cabeça da lista de adjacência
} AdjList;

// Estrutura principal do grafo
typedef struct {
    int numVertices;    // Número atual de vértices
    int maxVertices;    // Capacidade máxima atual
    int isDirected;     // Flag para grafo direcionado (1) ou não (0)
    int isWeighted;     // Flag para grafo ponderado (1) ou não (0)
    AdjList* array;     // Array de listas de adjacência
} Grafo;

// Funções de criação e liberação do grafo
Grafo* criaGrafo(int maxVertices, int isDirected, int isWeighted);
void liberaGrafo(Grafo* G);

// Funções básicas de manipulação do grafo
int insereVertice(Grafo* G, char* label);
int insereAresta(Grafo* G, int u, int v, float w);
int removeAresta(Grafo* G, int u, int v);

// Funções para análise de propriedades básicas
int grau(Grafo* G, int v);
float grauMedio(Grafo* G);
int grauMax(Grafo* G, int* v);

// Funções para análise de componentes conexas
int numComponentesConexas(Grafo* G);
int tamanhoMaiorComponente(Grafo* G);

// Funções para cálculo de caminhos mínimos
float menorCaminhoMedio(Grafo* G);

// Funções para leitura de grafos de arquivos
Grafo* leGrafo(char* nomeArquivo, int isDirected, int isWeighted);

#endif