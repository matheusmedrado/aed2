#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

/**
 * Cria um novo grafo com capacidade inicial maxVertices
 */
Grafo* criaGrafo(int maxVertices, int isDirected, int isWeighted) {
    Grafo* G = (Grafo*)malloc(sizeof(Grafo));
    if (G == NULL) {
        return NULL;
    }
    
    G->numVertices = 0;
    G->maxVertices = maxVertices;
    G->isDirected = isDirected;
    G->isWeighted = isWeighted;
    
    // Aloca o array de listas de adjacência
    G->array = (AdjList*)malloc(maxVertices * sizeof(AdjList));
    if (G->array == NULL) {
        free(G);
        return NULL;
    }
    
    // Inicializa cada lista de adjacência
    for (int i = 0; i < maxVertices; i++) {
        G->array[i].head = NULL;
        G->array[i].label = NULL;
    }
    
    return G;
}

/**
 * Libera toda a memória alocada para o grafo
 */
void liberaGrafo(Grafo* G) {
    if (G == NULL) {
        return;
    }
    
    // Libera as listas de adjacência
    for (int i = 0; i < G->maxVertices; i++) {
        AdjListNode* temp = G->array[i].head;
        
        // Libera cada nó na lista
        while (temp) {
            AdjListNode* next = temp->next;
            free(temp);
            temp = next;
        }
        
        // Libera a etiqueta do vértice
        if (G->array[i].label != NULL) {
            free(G->array[i].label);
        }
    }
    
    free(G->array);
    free(G);
}

/**
 * Função auxiliar para criar um novo nó de lista de adjacência
 */
AdjListNode* novoAdjListNode(int dest, float weight) {
    AdjListNode* novo = (AdjListNode*)malloc(sizeof(AdjListNode));
    if (novo == NULL) {
        return NULL;
    }
    
    novo->vertex = dest;
    novo->weight = weight;
    novo->next = NULL;
    
    return novo;
}

/**
 * Função auxiliar para redimensionar o array de vértices quando necessário
 */
int redimensionaGrafo(Grafo* G) {
    int novaCapacidade = G->maxVertices * 1.5;  // Aumenta em 50%
    
    // Realoca o array de listas de adjacência
    AdjList* novoArray = (AdjList*)realloc(G->array, novaCapacidade * sizeof(AdjList));
    if (novoArray == NULL) {
        return 0;  // Falha ao realocar
    }
    
    // Inicializa os novos espaços alocados
    for (int i = G->maxVertices; i < novaCapacidade; i++) {
        novoArray[i].head = NULL;
        novoArray[i].label = NULL;
    }
    
    G->array = novoArray;
    G->maxVertices = novaCapacidade;
    
    return 1;  // Sucesso
}

/**
 * Insere um novo vértice no grafo com a etiqueta especificada
 */
int insereVertice(Grafo* G, char* label) {
    if (G == NULL) {
        return 0;
    }
    
    // Verifica se precisamos redimensionar o array
    if (G->numVertices >= G->maxVertices) {
        if (!redimensionaGrafo(G)) {
            return 0;  // Falha ao redimensionar
        }
    }
    
    // Aloca e copia a etiqueta
    if (label != NULL) {
        G->array[G->numVertices].label = strdup(label);
        if (G->array[G->numVertices].label == NULL) {
            return 0;  // Falha ao alocar etiqueta
        }
    } else {
        G->array[G->numVertices].label = NULL;
    }
    
    G->array[G->numVertices].head = NULL;
    G->numVertices++;
    
    return 1;  // Sucesso
}

/**
 * Insere uma aresta entre os vértices u e v com peso w
 */
int insereAresta(Grafo* G, int u, int v, float w) {
    if (G == NULL) {
        return 0;
    }
    
    // Verifica se os vértices existem
    if (u < 0 || u >= G->numVertices || v < 0 || v >= G->numVertices) {
        return 0;
    }
    
    // Cria um novo nó para a lista de adjacência de u
    AdjListNode* novo = novoAdjListNode(v, w);
    if (novo == NULL) {
        return 0;
    }
    
    // Insere o novo nó no início da lista de adjacência de u
    novo->next = G->array[u].head;
    G->array[u].head = novo;
    
    // Se o grafo não for direcionado, adiciona a aresta em ambas as direções
    if (!G->isDirected && u != v) {
        AdjListNode* novo2 = novoAdjListNode(u, w);
        if (novo2 == NULL) {
            return 0;
        }
        
        novo2->next = G->array[v].head;
        G->array[v].head = novo2;
    }
    
    return 1;  // Sucesso
}

/**
 * Remove a aresta entre os vértices u e v
 */
int removeAresta(Grafo* G, int u, int v) {
    if (G == NULL) {
        return 0;
    }
    
    // Verifica se os vértices existem
    if (u < 0 || u >= G->numVertices || v < 0 || v >= G->numVertices) {
        return 0;
    }
    
    int encontrou = 0;
    
    // Remove a aresta da lista de adjacência de u
    AdjListNode* atual = G->array[u].head;
    AdjListNode* anterior = NULL;
    
    while (atual != NULL) {
        if (atual->vertex == v) {
            if (anterior == NULL) {
                // Remove o primeiro nó
                G->array[u].head = atual->next;
            } else {
                // Remove um nó intermediário
                anterior->next = atual->next;
            }
            
            free(atual);
            encontrou = 1;
            break;
        }
        
        anterior = atual;
        atual = atual->next;
    }
    
    // Se o grafo não for direcionado, remove a aresta na direção oposta
    if (!G->isDirected && encontrou && u != v) {
        atual = G->array[v].head;
        anterior = NULL;
        
        while (atual != NULL) {
            if (atual->vertex == u) {
                if (anterior == NULL) {
                    G->array[v].head = atual->next;
                } else {
                    anterior->next = atual->next;
                }
                
                free(atual);
                break;
            }
            
            anterior = atual;
            atual = atual->next;
        }
    }
    
    return encontrou;  // Retorna 1 se a aresta foi encontrada e removida, 0 caso contrário
}

/**
 * Retorna o grau do vértice v
 */
int grau(Grafo* G, int v) {
    if (G == NULL) {
        return -1;
    }
    
    // Verifica se o vértice existe
    if (v < 0 || v >= G->numVertices) {
        return -1;
    }
    
    int count = 0;
    AdjListNode* atual = G->array[v].head;
    
    while (atual != NULL) {
        count++;
        atual = atual->next;
    }
    
    return count;
}

/**
 * Retorna o grau médio do grafo
 */
float grauMedio(Grafo* G) {
    if (G == NULL || G->numVertices == 0) {
        return -1;
    }
    
    int somaGraus = 0;
    
    for (int i = 0; i < G->numVertices; i++) {
        somaGraus += grau(G, i);
    }
    
    return (float)somaGraus / G->numVertices;
}

/**
 * Retorna o grau máximo do grafo e armazena o índice do vértice em *v
 */
int grauMax(Grafo* G, int* v) {
    if (G == NULL || G->numVertices == 0 || v == NULL) {
        return -1;
    }
    
    int maxGrau = -1;
    *v = -1;
    
    for (int i = 0; i < G->numVertices; i++) {
        int grauAtual = grau(G, i);
        
        if (grauAtual > maxGrau) {
            maxGrau = grauAtual;
            *v = i;
        }
    }
    
    return maxGrau;
}

/**
 * Função auxiliar para DFS usada em componentes conexas
 */
void DFSUtil(Grafo* G, int v, int visitado[], int* tamanho) {
    visitado[v] = 1;
    (*tamanho)++;
    
    AdjListNode* atual = G->array[v].head;
    
    while (atual != NULL) {
        int u = atual->vertex;
        if (!visitado[u]) {
            DFSUtil(G, u, visitado, tamanho);
        }
        atual = atual->next;
    }
}

/**
 * Retorna o número de componentes conexas do grafo
 */
int numComponentesConexas(Grafo* G) {
    if (G == NULL || G->numVertices == 0) {
        return 0;
    }
    
    int* visitado = (int*)calloc(G->numVertices, sizeof(int));
    if (visitado == NULL) {
        return -1;
    }
    
    int count = 0;
    int tamanhoComponente;
    
    for (int v = 0; v < G->numVertices; v++) {
        if (!visitado[v]) {
            tamanhoComponente = 0;
            DFSUtil(G, v, visitado, &tamanhoComponente);
            count++;
        }
    }
    
    free(visitado);
    return count;
}

/**
 * Retorna o tamanho da maior componente conexa do grafo
 */
int tamanhoMaiorComponente(Grafo* G) {
    if (G == NULL || G->numVertices == 0) {
        return 0;
    }
    
    int* visitado = (int*)calloc(G->numVertices, sizeof(int));
    if (visitado == NULL) {
        return -1;
    }
    
    int maxTamanho = 0;
    
    for (int v = 0; v < G->numVertices; v++) {
        if (!visitado[v]) {
            int tamanhoComponente = 0;
            DFSUtil(G, v, visitado, &tamanhoComponente);
            
            if (tamanhoComponente > maxTamanho) {
                maxTamanho = tamanhoComponente;
            }
        }
    }
    
    free(visitado);
    return maxTamanho;
}

/**
 * Implementação do algoritmo de Dijkstra para cálculo de caminhos mínimos
 */
float* dijkstra(Grafo* G, int src) {
    float* dist = (float*)malloc(G->numVertices * sizeof(float));
    int* visitado = (int*)calloc(G->numVertices, sizeof(int));
    
    if (dist == NULL || visitado == NULL) {
        free(dist);
        free(visitado);
        return NULL;
    }
    
    // Inicializa todas as distâncias como infinito
    for (int i = 0; i < G->numVertices; i++) {
        dist[i] = FLT_MAX;
    }
    
    // A distância do vértice de origem para ele mesmo é 0
    dist[src] = 0;
    
    // Encontra o caminho mais curto para todos os vértices
    for (int count = 0; count < G->numVertices - 1; count++) {
        // Pega o vértice com distância mínima do conjunto de vértices ainda não processados
        float min = FLT_MAX;
        int min_index = -1;
        
        for (int v = 0; v < G->numVertices; v++) {
            if (!visitado[v] && dist[v] <= min) {
                min = dist[v];
                min_index = v;
            }
        }
        
        // Se não houver vértice alcançável, pare
        if (min_index == -1) {
            break;
        }
        
        // Marca o vértice selecionado como visitado
        visitado[min_index] = 1;
        
        // Atualiza o valor de dist dos vértices adjacentes do vértice selecionado
        AdjListNode* atual = G->array[min_index].head;
        while (atual != NULL) {
            int v = atual->vertex;
            // Se o vértice v não está visitado e existe um caminho para ele que é menor
            if (!visitado[v] && dist[min_index] != FLT_MAX && 
                dist[min_index] + atual->weight < dist[v]) {
                dist[v] = dist[min_index] + atual->weight;
            }
            atual = atual->next;
        }
    }
    
    free(visitado);
    return dist;
}

/**
 * Calcula o menor caminho médio entre todos os pares de vértices
 */
float menorCaminhoMedio(Grafo* G) {
    if (G == NULL || G->numVertices <= 1) {
        return -1;
    }
    
    int totalPares = 0;
    float somaDistancias = 0;
    
    // Para cada vértice, calcular os caminhos mínimos para todos os outros vértices
    for (int i = 0; i < G->numVertices; i++) {
        float* dist = dijkstra(G, i);
        if (dist == NULL) {
            return -1;
        }
        
        for (int j = 0; j < G->numVertices; j++) {
            if (i != j && dist[j] != FLT_MAX) {
                somaDistancias += dist[j];
                totalPares++;
            }
        }
        
        free(dist);
    }
    
    return (totalPares > 0) ? somaDistancias / totalPares : -1;
}

/**
 * Lê um grafo de um arquivo
 * Formato do arquivo:
 * - Primeira linha: número de vértices e número de arestas
 * - Linhas seguintes: pares de vértices que formam arestas (e peso, se for grafo ponderado)
 */
Grafo* leGrafo(char* nomeArquivo, int isDirected, int isWeighted) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        return NULL;
    }
    
    int numVertices, numArestas;
    if (fscanf(arquivo, "%d %d", &numVertices, &numArestas) != 2) {
        fclose(arquivo);
        return NULL;
    }
    
    Grafo* G = criaGrafo(numVertices, isDirected, isWeighted);
    if (G == NULL) {
        fclose(arquivo);
        return NULL;
    }
    
    // Adiciona os vértices
    for (int i = 0; i < numVertices; i++) {
        char label[20];
        sprintf(label, "V%d", i);
        insereVertice(G, label);
    }
    
    // Lê as arestas
    for (int i = 0; i < numArestas; i++) {
        int u, v;
        float w = 1.0;  // Peso padrão se não for ponderado
        
        if (isWeighted) {
            if (fscanf(arquivo, "%d %d %f", &u, &v, &w) != 3) {
                liberaGrafo(G);
                fclose(arquivo);
                return NULL;
            }
        } else {
            if (fscanf(arquivo, "%d %d", &u, &v) != 2) {
                liberaGrafo(G);
                fclose(arquivo);
                return NULL;
            }
        }
        
        insereAresta(G, u, v, w);
    }
    
    fclose(arquivo);
    return G;
}