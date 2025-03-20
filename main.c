#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * Função para ler o grafo dos golfinhos da Flórida
 * Formato específico do arquivo da rede de golfinhos
 */
Grafo* leDadosGolfinhos(char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return NULL;
    }
    
    // Cria um grafo não direcionado e não ponderado
    Grafo* G = criaGrafo(100, 0, 0);  // Começamos com capacidade para 100 vértices
    if (G == NULL) {
        fclose(arquivo);
        return NULL;
    }
    
    // Mapeamento para IDs de golfinhos
    char linha[256];
    int totalVertices = 0;
    int u, v;
    
    // Primeira passagem: contar vértices únicos e criar mapeamento
    int* verticesUnicos = (int*)calloc(1000, sizeof(int));  // Assumimos um máximo de 1000 vértices
    int maxVertice = -1;
    
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Ignora linhas de comentário
        if (linha[0] == '%' || linha[0] == '#') {
            continue;
        }
        
        if (sscanf(linha, "%d %d", &u, &v) == 2) {
            // Ajusta os índices para base 0 se necessário
            if (u > 0) u--;
            if (v > 0) v--;
            
            verticesUnicos[u] = 1;
            verticesUnicos[v] = 1;
            
            if (u > maxVertice) maxVertice = u;
            if (v > maxVertice) maxVertice = v;
        }
    }
    
    // Conta o número de vértices únicos
    for (int i = 0; i <= maxVertice; i++) {
        if (verticesUnicos[i]) {
            totalVertices++;
        }
    }
    
    free(verticesUnicos);
    rewind(arquivo);
    
    // Cria os vértices
    for (int i = 0; i <= maxVertice; i++) {
        char label[20];
        sprintf(label, "Dolphin_%d", i+1);  // Numera a partir de 1 para legibilidade
        insereVertice(G, label);
    }
    
    // Segunda passagem: adicionar arestas
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Ignora linhas de comentário
        if (linha[0] == '%' || linha[0] == '#') {
            continue;
        }
        
        if (sscanf(linha, "%d %d", &u, &v) == 2) {
            // Ajusta os índices para base 0 se necessário
            if (u > 0) u--;
            if (v > 0) v--;
            
            insereAresta(G, u, v, 1.0);
        }
    }
    
    fclose(arquivo);
    return G;
}

/**
 * Função para analisar o grafo dos golfinhos
 */
void analisaRedeGolfinhos(Grafo* G) {
    printf("=== Análise da Rede Social dos Golfinhos da Flórida ===\n\n");
    
    // Número de vértices e arestas
    int numVertices = G->numVertices;
    int numArestas = 0;
    
    for (int i = 0; i < numVertices; i++) {
        numArestas += grau(G, i);
    }
    // Divide por 2 porque cada aresta é contada duas vezes em um grafo não direcionado
    numArestas /= 2;
    
    printf("1. Informações básicas:\n");
    printf("   - Número de golfinhos (vértices): %d\n", numVertices);
    printf("   - Número de interações sociais (arestas): %d\n", numArestas);
    
    // Grau médio
    float gMedio = grauMedio(G);
    printf("\n2. Conectividade:\n");
    printf("   - Grau médio: %.2f interações por golfinho\n", gMedio);
    
    // Golfinho com maior grau
    int idGolfinhoMaiorGrau;
    int maiorGrau = grauMax(G, &idGolfinhoMaiorGrau);
    printf("   - Golfinho mais conectado: %s (ID: %d) com %d interações\n", 
           G->array[idGolfinhoMaiorGrau].label, idGolfinhoMaiorGrau + 1, maiorGrau);
    
    // Componentes conexas
    int numComponentes = numComponentesConexas(G);
    int tamMaiorComponente = tamanhoMaiorComponente(G);
    printf("\n3. Estrutura comunitária:\n");
    printf("   - Número de grupos sociais (componentes conexas): %d\n", numComponentes);
    printf("   - Tamanho do maior grupo social: %d golfinhos (%.1f%% da rede)\n", 
           tamMaiorComponente, (float)tamMaiorComponente * 100 / numVertices);
    
    // Caminho médio
    float caminhoMedio = menorCaminhoMedio(G);
    printf("\n4. Distância social:\n");
    printf("   - Comprimento médio do menor caminho: %.2f interações\n", caminhoMedio);
    printf("   - Isso significa que, em média, qualquer golfinho está a %.2f passos de qualquer outro\n", caminhoMedio);
    
    // Distribuição de graus
    printf("\n5. Distribuição de graus:\n");
    int maxGrau = maiorGrau;
    int* contGraus = (int*)calloc(maxGrau + 1, sizeof(int));
    
    for (int i = 0; i < numVertices; i++) {
        int g = grau(G, i);
        contGraus[g]++;
    }
    
    printf("   Grau  | Quantidade | Porcentagem\n");
    printf("   -----------------------------\n");
    for (int i = 0; i <= maxGrau; i++) {
        if (contGraus[i] > 0) {
            printf("   %4d  | %10d | %6.2f%%\n", 
                   i, contGraus[i], (float)contGraus[i] * 100 / numVertices);
        }
    }
    
    free(contGraus);
    
    printf("\n=== Fim da Análise ===\n");
}

/**
 * Função principal
 */
int main() {
    clock_t inicio, fim;
    double tempoExecucao;
    
    inicio = clock();
    
    printf("Programa de Análise de Grafos - Rede de Golfinhos da Flórida\n");
    printf("----------------------------------------------------------\n\n");
    
    // Carrega o grafo a partir do arquivo
    Grafo* G = leDadosGolfinhos("dolphins.edges");
    
    if (G == NULL) {
        printf("Erro ao carregar o grafo. Verifique o arquivo de entrada.\n");
        return 1;
    }
    
    // Analisa a rede de golfinhos
    analisaRedeGolfinhos(G);
    
    // Libera memória
    liberaGrafo(G);
    
    fim = clock();
    tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    
    printf("\nTempo de execução: %.2f segundos\n", tempoExecucao);
    
    return 0;
}