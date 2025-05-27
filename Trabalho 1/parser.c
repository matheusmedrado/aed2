#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Programa auxiliar para converter o formato de dados dos golfinhos da Florida
 * do NetworkRepository para o formato exigido pelo programa principal
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <arquivo_entrada> <arquivo_saida>\n", argv[0]);
        return 1;
    }
    
    FILE *entrada = fopen(argv[1], "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada %s\n", argv[1]);
        return 1;
    }
    
    FILE *saida = fopen(argv[2], "w");
    if (saida == NULL) {
        printf("Erro ao criar o arquivo de saída %s\n", argv[2]);
        fclose(entrada);
        return 1;
    }
    
    // Escreve cabeçalho no arquivo de saída
    fprintf(saida, "# Dolphin social network - Florida\n");
    fprintf(saida, "# Source: https://networkrepository.com/mammalia-dolphin-florida-social.php\n");
    fprintf(saida, "# Format: node1 node2\n");
    
    char linha[256];
    int numVertices = 0;
    int numArestas = 0;
    int u, v;
    
    // Primeira passagem: contar vértices e arestas
    while (fgets(linha, sizeof(linha), entrada) != NULL) {
        // Ignora linhas de comentário
        if (linha[0] == '%' || linha[0] == '#') {
            continue;
        }
        
        // Lê aresta
        if (sscanf(linha, "%d %d", &u, &v) == 2) {
            numArestas++;
            
            // Atualiza o número máximo de vértices
            if (u > numVertices) numVertices = u;
            if (v > numVertices) numVertices = v;
        }
    }
    
    // Escreve o número de vértices e arestas no início do arquivo
    rewind(entrada);
    fprintf(saida, "%d %d\n", numVertices, numArestas);
    
    // Segunda passagem: copiar as arestas
    while (fgets(linha, sizeof(linha), entrada) != NULL) {
        // Ignora linhas de comentário
        if (linha[0] == '%' || linha[0] == '#') {
            continue;
        }
        
        // Lê e escreve aresta
        if (sscanf(linha, "%d %d", &u, &v) == 2) {
            fprintf(saida, "%d %d\n", u, v);
        }
    }
    
    printf("Conversão concluída.\n");
    printf("Número de vértices: %d\n", numVertices);
    printf("Número de arestas: %d\n", numArestas);
    
    fclose(entrada);
    fclose(saida);
    
    return 0;
}