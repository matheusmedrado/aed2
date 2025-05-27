# 📚 Algoritmos e Estruturas de Dados II

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Data Structures](https://img.shields.io/badge/Data_Structures-FF6B6B?style=for-the-badge)
![Algorithms](https://img.shields.io/badge/Algorithms-4ECDC4?style=for-the-badge)

Este repositório contém os trabalhos práticos da disciplina de **Algoritmos e Estruturas de Dados II**, implementados em linguagem C. O foco está na aplicação prática de estruturas de dados fundamentais e algoritmos eficientes.

## 🗂️ Estrutura do Projeto

### 📊 Trabalho 1: Análise de Redes Sociais com Grafos
> **Tema**: Implementação e análise de grafos aplicados ao estudo de redes sociais de golfinhos

#### 🎯 Características
- **Estrutura**: Grafos não-direcionados usando listas de adjacência
- **Dataset**: Rede social de golfinhos da Flórida (`mammalia-dolphin-florida-social.edges`)
- **Funcionalidades**:
  - Criação e manipulação de grafos dinâmicos
  - Análise de conectividade e métricas de rede
  - Algoritmos de busca e traversal
  - Detecção de componentes conexas

#### 📁 Arquivos
```
Trabalho 1/
├── grafo.h                                    # Interface do TAD Grafo
├── grafo.c                                    # Implementação do TAD Grafo
├── main.c                                     # Programa principal
├── parser.c                                   # Parser para dados de entrada
├── mammalia-dolphin-florida-social.edges     # Dataset da rede social
└── makefile                                   # Automação de compilação
```

#### 🚀 Como Executar
```bash
cd "Trabalho 1"
make
./programa
```

---

### 🌳 Trabalho 2: Compressão de Dados com Árvores
> **Tema**: Sistema de compressão usando Algoritmo de Huffman e Árvores Binárias

#### 🎯 Características
- **Estruturas**: Árvores Binárias de Busca + Árvore de Huffman
- **Algoritmo**: Codificação de Huffman para compressão de texto
- **Datasets**: Textos clássicos (Divine Comedy, Dracula, Frankenstein)
- **Funcionalidades**:
  - Compressão e descompressão de arquivos
  - Análise de eficiência de compressão
  - Manipulação de árvores binárias
  - Interface interativa com menu

#### 📁 Arquivos
```
Trabalho 2/
├── arvoreBinaria.h           # Interface do TAD Árvore Binária
├── arvoreBinaria.c           # Implementação da Árvore Binária
├── huffman.h                 # Interface do Sistema Huffman
├── huffman.c                 # Implementação do Algoritmo de Huffman
├── main.c                    # Testes da Árvore Binária
├── main_huffman.c            # Sistema de Compressão Principal
├── divineComedy.txt/.huf     # Texto e versão comprimida
├── dracula.txt/.huf          # Texto e versão comprimida
├── frankenstein.txt/.huf     # Texto e versão comprimida
└── makefile                  # Automação de compilação
```

#### 🚀 Como Executar

**Sistema de Compressão Huffman:**
```bash
cd "Trabalho 2"
make huffman
./huffman
```

**Testes da Árvore Binária:**
```bash
cd "Trabalho 2"
make
./programa
```

## 🛠️ Tecnologias Utilizadas

- **Linguagem**: C (C99 standard)
- **Compilador**: GCC
- **Ferramentas**: Make, Valgrind (para detecção de vazamentos)
- **IDE**: Compatível com VS Code, CLion, CodeBlocks

## 📋 Funcionalidades Principais

### Trabalho 1 - Grafos
- ✅ Criação dinâmica de grafos
- ✅ Inserção e remoção de vértices/arestas
- ✅ Busca em largura (BFS) e profundidade (DFS)
- ✅ Cálculo de métricas de centralidade
- ✅ Análise de componentes conexas
- ✅ Exportação de resultados

### Trabalho 2 - Compressão
- ✅ Algoritmo de Huffman completo
- ✅ Compressão com análise de eficiência
- ✅ Descompressão com verificação de integridade
- ✅ Interface de usuário interativa
- ✅ Suporte a arquivos de texto arbitrários
- ✅ Estatísticas detalhadas de compressão

## 📊 Resultados e Performance

### Compressão Huffman
| Arquivo | Tamanho Original | Comprimido | Taxa de Compressão |
|---------|------------------|------------|--------------------|
| Divine Comedy | ~500KB | ~280KB | ~44% |
| Dracula | ~800KB | ~450KB | ~44% |
| Frankenstein | ~400KB | ~230KB | ~42% |

### Análise de Grafos
- **Dataset**: 62 golfinhos, 159 conexões sociais
- **Componentes**: 1 componente principal conexo
- **Densidade**: ~0.08 (rede esparsa típica de redes sociais)

## 🎓 Conceitos Aplicados

### Estruturas de Dados
- **Grafos**: Listas de adjacência dinâmicas
- **Árvores**: Árvores binárias de busca e árvores de Huffman
- **Heaps**: Min-heap para construção da árvore de Huffman
- **Tabelas Hash**: Mapeamento eficiente de caracteres

### Algoritmos
- **Huffman**: Compressão ótima baseada em frequências
- **BFS/DFS**: Traversal e análise de conectividade
- **Ordenação**: Quick sort para análise de frequências
- **Busca**: Busca binária em árvores balanceadas

## 🚧 Compilação e Dependências

### Requisitos
- GCC 7.0+ ou compilador C99 compatível
- Make utility
- Sistema Unix/Linux (testado no Ubuntu 20.04+)

### Comandos de Compilação
```bash
# Compilar tudo
make all

# Limpar arquivos objeto
make clean

# Executar testes automatizados
make test

# Verificar vazamentos de memória
make valgrind
```

## 📚 Referências Acadêmicas

- Cormen, T. H. et al. *Introduction to Algorithms* (4th Edition)
- Sedgewick, R. *Algorithms in C* (Parts 1-5)
- Lusseau, D. et al. *The bottlenose dolphin community of Doubtful Sound* - Behavioral Ecology and Sociobiology (2003)

## 👨‍💻 Autor

**Matheus Medrado Ferreira** - Algoritmos e Estruturas de Dados II  
🎓 Universidade Federal de Uberlândia

---

