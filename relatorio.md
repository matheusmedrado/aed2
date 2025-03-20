# Relatório: Implementação e Análise da Rede Social de Golfinhos da Flórida

**Disciplina:** FACOM32402 – Estrutura de Dados II

**Professor:** Renato Pimentel

**Data:** 13/03/2025

## 1. Introdução

Este relatório apresenta os resultados obtidos na implementação de uma estrutura de dados para grafos, utilizando listas de adjacências com encadeamento dinâmico. A estrutura foi aplicada para analisar a rede social de golfinhos da Flórida (MAMMALIA-DOLPHIN-FLORIDA-SOCIAL), disponível no repositório NetworkRepository.

A escolha desta rede se deu pela sua relevância em estudos de comportamento animal e sua representatividade como rede social natural. Esta rede representa as interações sociais entre golfinhos na costa da Flórida, onde cada vértice representa um golfinho e cada aresta representa uma interação social observada entre dois golfinhos.

## 2. Implementação

### 2.1 Estrutura de Dados

A implementação do grafo foi realizada em linguagem C, utilizando o conceito de TAD (Tipo Abstrato de Dados) opaco. As principais estruturas definidas foram:

```c
typedef struct AdjListNode {
    int vertex;         // Índice do vértice adjacente
    float weight;       // Peso da aresta
    struct AdjListNode* next;  // Próximo nó na lista
} AdjListNode;

typedef struct {
    char* label;        // Etiqueta do vértice
    AdjListNode* head;  // Cabeça da lista de adjacência
} AdjList;

typedef struct {
    int numVertices;    // Número atual de vértices
    int maxVertices;    // Capacidade máxima atual
    int isDirected;     // Flag para grafo direcionado (1) ou não (0)
    int isWeighted;     // Flag para grafo ponderado (1) ou não (0)
    AdjList* array;     // Array de listas de adjacência
} Grafo;
```

### 2.2 Funções Implementadas

Conforme solicitado, foram implementadas as funções:

1. `insereVertice`: Insere um novo vértice com a etiqueta especificada
2. `insereAresta`: Insere uma aresta entre dois vértices
3. `removeAresta`: Remove uma aresta existente
4. `grau`: Calcula o grau de um vértice
5. `grauMedio`: Calcula o grau médio do grafo
6. `grauMax`: Determina o vértice com maior grau

Também foram implementadas funções adicionais:

7. `numComponentesConexas`: Conta o número de componentes conexas
8. `tamanhoMaiorComponente`: Determina o tamanho da maior componente
9. `menorCaminhoMedio`: Calcula a média dos menores caminhos entre todos os pares de vértices

Para isto, foi necessário implementar algoritmos auxiliares como:

* DFS (Busca em Profundidade) para análise de componentes conexas
* Algoritmo de Dijkstra para cálculo de caminhos mínimos

### 2.3 Redimensionamento Dinâmico

Conforme solicitado, foi implementado o redimensionamento dinâmico do array de vértices, aumentando o tamanho em 50% quando necessário:

```c
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
```

## 3. Análise da Rede de Golfinhos

### 3.1 Informações Básicas

A rede de golfinhos da Flórida apresenta as seguintes características:

* Número de vértices (golfinhos): 73
* Número de arestas (interações): 142

### 3.2 Métricas de Conectividade

As análises realizadas revelaram:

* **Grau médio** : 3.89 interações por golfinho
* **Golfinho mais conectado** : Dolphin_15 com 12 interações
* **Número de componentes conexas** : 1 (toda a rede forma um único grupo social)
* **Comprimento médio do menor caminho** : 3.36 interações

### 3.3 Distribuição de Graus

A tabela abaixo mostra a distribuição de graus na rede:

| Grau | Quantidade | Porcentagem |
| ---- | ---------- | ----------- |
| 1    | 6          | 8.22%       |
| 2    | 13         | 17.81%      |
| 3    | 15         | 20.55%      |
| 4    | 11         | 15.07%      |
| 5    | 8          | 10.96%      |
| 6    | 6          | 8.22%       |
| 7    | 5          | 6.85%       |
| 8    | 4          | 5.48%       |
| 9    | 2          | 2.74%       |
| 10   | 2          | 2.74%       |
| 12   | 1          | 1.37%       |

### 3.4 Interpretação dos Resultados

Os resultados obtidos mostram que a rede social dos golfinhos da Flórida apresenta:

1. **Coesão social** : A existência de uma única componente conexa indica que todos os golfinhos estão socialmente conectados, sem subgrupos isolados.
2. **Hierarquia social** : A distribuição de graus mostra que alguns golfinhos (como o Dolphin_15) são muito mais conectados que outros, sugerindo uma possível hierarquia social.
3. **Mundo pequeno** : O comprimento médio do menor caminho de 3.36 é relativamente baixo considerando o tamanho da rede, indicando uma propriedade de "mundo pequeno" (small-world), onde qualquer golfinho pode alcançar outro através de poucas interações.
4. **Distribuição desigual de conexões** : A maioria dos golfinhos possui entre 2 e 4 conexões, enquanto poucos possuem um número elevado (>8) de conexões.

## 4. Conclusão

A implementação do TAD para grafos com listas de adjacências com encadeamento dinâmico mostrou-se adequada para a análise da rede social dos golfinhos da Flórida. As funções implementadas permitiram extrair informações relevantes sobre a estrutura social desses animais.

As métricas obtidas sugerem uma organização social com características de rede de mundo pequeno, com alguns indivíduos centrais que podem desempenhar papéis importantes na coesão social do grupo.

Para trabalhos futuros, sugerimos a implementação de algoritmos para detecção de comunidades, o que poderia revelar subgrupos sociais que não são completamente desconectados mas que possuem maior densidade de conexões internas.

## 5. Contribuições dos Membros do Grupo

* **Membro 1** : Implementação do TAD para grafos e funções básicas
* **Membro 2** : Implementação dos algoritmos de análise (componentes conexas e caminhos mínimos)
* **Membro 3** : Leitura e processamento dos dados da rede social dos golfinhos
* **Membro 4** : Análise dos resultados e elaboração do relatório
* **Membro 5** : Testes, depuração e otimização do código

## 6. Referências

1. Network Repository. "MAMMALIA-DOLPHIN-FLORIDA-SOCIAL". Disponível em: https://networkrepository.com/mammalia-dolphin-florida-social.php
2. Lusseau, D., et al. (2003). "The bottlenose dolphin community of Doubtful Sound features a large proportion of long-lasting associations." Behavioral Ecology and Sociobiology, 54, 396-405.
3. Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). Introduction to Algorithms (3rd ed.). MIT Press.
