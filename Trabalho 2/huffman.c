#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

// Estrutura para nós da árvore de Huffman
struct NoHuffman
{
    unsigned char caractere;
    int frequencia;
    struct NoHuffman *esquerda;
    struct NoHuffman *direita;
};

// Função para criar um novo nó da árvore de Huffman
struct NoHuffman *criar_no(unsigned char caractere, int frequencia)
{
    struct NoHuffman *no = (struct NoHuffman *)malloc(sizeof(struct NoHuffman));
    if (no)
    {
        no->caractere = caractere;
        no->frequencia = frequencia;
        no->esquerda = NULL;
        no->direita = NULL;
    }
    return no;
}

// Função para liberar a árvore de Huffman
void liberar_arvore_huffman(struct NoHuffman *raiz)
{
    if (raiz)
    {
        liberar_arvore_huffman(raiz->esquerda);
        liberar_arvore_huffman(raiz->direita);
        free(raiz);
    }
}

// Função para calcular frequências de caracteres em um arquivo
FrequenciaCaractere *calcular_frequencias(const char *nome_arquivo, int *caracteres_unicos)
{
    FILE *arquivo = fopen(nome_arquivo, "rb");
    if (!arquivo)
    {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return NULL;
    }

    // Inicializar array de frequências para todos os valores de byte possíveis (0-255)
    int frequencias[256] = {0};
    unsigned char byte;

    // Ler arquivo byte a byte e contar frequências
    while (fread(&byte, 1, 1, arquivo) == 1)
    {
        frequencias[byte]++;
    }

    fclose(arquivo);

    // Contar caracteres únicos
    *caracteres_unicos = 0;
    for (int i = 0; i < 256; i++)
    {
        if (frequencias[i] > 0)
        {
            (*caracteres_unicos)++;
        }
    }

    // Criar e preencher a tabela de frequências
    FrequenciaCaractere *tabela_freq = (FrequenciaCaractere *)malloc(*caracteres_unicos * sizeof(FrequenciaCaractere));
    if (!tabela_freq)
    {
        printf("Erro de alocação de memória\n");
        return NULL;
    }

    int indice = 0;
    for (int i = 0; i < 256; i++)
    {
        if (frequencias[i] > 0)
        {
            tabela_freq[indice].caractere = (unsigned char)i;
            tabela_freq[indice].frequencia = frequencias[i];
            indice++;
        }
    }

    return tabela_freq;
}

// Implementação de heap mínimo para fila de prioridade
struct HeapMinimo
{
    unsigned tamanho;
    unsigned capacidade;
    struct NoHuffman **array;
};

// Criar um novo heap mínimo
struct HeapMinimo *criar_heap_minimo(unsigned capacidade)
{
    struct HeapMinimo *heap = (struct HeapMinimo *)malloc(sizeof(struct HeapMinimo));
    heap->tamanho = 0;
    heap->capacidade = capacidade;
    heap->array = (struct NoHuffman **)malloc(capacidade * sizeof(struct NoHuffman *));
    return heap;
}

// Trocar dois nós
void trocar_nos(struct NoHuffman **a, struct NoHuffman **b)
{
    struct NoHuffman *temp = *a;
    *a = *b;
    *b = temp;
}

// Algoritmo de heapify
void heapificar_minimo(struct HeapMinimo *heap, int idx)
{
    int menor = idx;
    int esquerda = 2 * idx + 1;
    int direita = 2 * idx + 2;

    if (esquerda < heap->tamanho &&
        heap->array[esquerda]->frequencia < heap->array[menor]->frequencia)
        menor = esquerda;

    if (direita < heap->tamanho &&
        heap->array[direita]->frequencia < heap->array[menor]->frequencia)
        menor = direita;

    if (menor != idx)
    {
        trocar_nos(&heap->array[menor], &heap->array[idx]);
        heapificar_minimo(heap, menor);
    }
}

// Verificar se o tamanho do heap é 1
int tamanho_eh_um(struct HeapMinimo *heap)
{
    return (heap->tamanho == 1);
}

// Extrair o nó com valor mínimo do heap
struct NoHuffman *extrair_minimo(struct HeapMinimo *heap)
{
    struct NoHuffman *temp = heap->array[0];
    heap->array[0] = heap->array[heap->tamanho - 1];
    --heap->tamanho;
    heapificar_minimo(heap, 0);
    return temp;
}

// Inserir um novo nó no heap mínimo
void inserir_heap_minimo(struct HeapMinimo *heap, struct NoHuffman *no)
{
    ++heap->tamanho;
    int i = heap->tamanho - 1;

    while (i && no->frequencia < heap->array[(i - 1) / 2]->frequencia)
    {
        heap->array[i] = heap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    heap->array[i] = no;
}

// Construir heap mínimo
void construir_heap_minimo(struct HeapMinimo *heap)
{
    int n = heap->tamanho - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        heapificar_minimo(heap, i);
}

// Criar um heap mínimo a partir da tabela de frequências
struct HeapMinimo *criar_e_construir_heap_minimo(FrequenciaCaractere *tabela_freq, int tamanho)
{
    struct HeapMinimo *heap = criar_heap_minimo(tamanho);

    for (int i = 0; i < tamanho; ++i)
    {
        heap->array[i] = criar_no(tabela_freq[i].caractere, tabela_freq[i].frequencia);
    }

    heap->tamanho = tamanho;
    construir_heap_minimo(heap);

    return heap;
}

// Construir a árvore de Huffman
struct NoHuffman *construir_arvore_huffman(FrequenciaCaractere *tabela_freq, int tamanho)
{
    struct NoHuffman *esquerda, *direita, *topo;

    // Criar um heap mínimo com capacidade igual ao tamanho
    struct HeapMinimo *heap = criar_e_construir_heap_minimo(tabela_freq, tamanho);

    // Iterar até o tamanho do heap não ser 1
    while (!tamanho_eh_um(heap))
    {
        // Extrair os dois nós com menor frequência
        esquerda = extrair_minimo(heap);
        direita = extrair_minimo(heap);

        // Criar um novo nó interno com frequência igual à soma
        // das frequências dos dois nós. Fazer os dois nós extraídos
        // como filhos à esquerda e à direita desse novo nó.
        topo = criar_no('$', esquerda->frequencia + direita->frequencia);
        topo->esquerda = esquerda;
        topo->direita = direita;

        // Adicionar este nó ao heap mínimo
        inserir_heap_minimo(heap, topo);
    }

    // O nó restante é a raiz e a árvore está completa
    struct NoHuffman *raiz = extrair_minimo(heap);

    // Liberar o heap mínimo
    free(heap->array);
    free(heap);

    return raiz;
}

// Gerar códigos a partir da árvore de Huffman
void gerar_codigos_auxiliar(struct NoHuffman *raiz, char *codigo, int topo, CodigoHuffman *codigos, int *indice)
{
    // Atribuir 0 à aresta esquerda e recursar
    if (raiz->esquerda)
    {
        codigo[topo] = '0';
        gerar_codigos_auxiliar(raiz->esquerda, codigo, topo + 1, codigos, indice);
    }

    // Atribuir 1 à aresta direita e recursar
    if (raiz->direita)
    {
        codigo[topo] = '1';
        gerar_codigos_auxiliar(raiz->direita, codigo, topo + 1, codigos, indice);
    }

    // Se for um nó folha, armazenar o código
    if (!raiz->esquerda && !raiz->direita)
    {
        codigo[topo] = '\0';
        codigos[*indice].caractere = raiz->caractere;
        codigos[*indice].codigo = strdup(codigo);
        (*indice)++;
    }
}

// Função auxiliar para gerar códigos de Huffman
CodigoHuffman *gerar_codigos(struct NoHuffman *raiz, int caracteres_unicos)
{
    if (!raiz)
        return NULL;

    CodigoHuffman *codigos = (CodigoHuffman *)malloc(caracteres_unicos * sizeof(CodigoHuffman));
    if (!codigos)
        return NULL;

    char *codigo_temp = (char *)malloc(caracteres_unicos * sizeof(char));
    int indice = 0;

    gerar_codigos_auxiliar(raiz, codigo_temp, 0, codigos, &indice);

    free(codigo_temp);
    return codigos;
}

// Função para liberar o array de códigos
void liberar_codigos(CodigoHuffman *codigos, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        free(codigos[i].codigo);
    }
    free(codigos);
}

// Escrever um bit no arquivo de saída
void escrever_bit(FILE *arquivo, int bit, unsigned char *byte, int *pos_bit)
{
    if (bit)
        *byte |= (1 << (7 - *pos_bit));

    (*pos_bit)++;

    if (*pos_bit == 8)
    {
        fwrite(byte, 1, 1, arquivo);
        *byte = 0;
        *pos_bit = 0;
    }
}

// Encontrar o código de um caractere no array de códigos
char *encontrar_codigo(CodigoHuffman *codigos, int tamanho, unsigned char caractere)
{
    for (int i = 0; i < tamanho; i++)
    {
        if (codigos[i].caractere == caractere)
        {
            return codigos[i].codigo;
        }
    }
    return NULL; // Não deveria chegar aqui se todos os caracteres do arquivo de entrada foram processados corretamente
}

// Função para comprimir um arquivo
int comprimir_arquivo(const char *nome_arquivo_entrada, const char *nome_arquivo_saida)
{
    // Calcular frequências de caracteres
    int caracteres_unicos = 0;
    FrequenciaCaractere *tabela_freq = calcular_frequencias(nome_arquivo_entrada, &caracteres_unicos);
    if (!tabela_freq)
        return 0;

    // Construir árvore de Huffman
    struct NoHuffman *raiz = construir_arvore_huffman(tabela_freq, caracteres_unicos);
    if (!raiz)
    {
        free(tabela_freq);
        return 0;
    }

    // Gerar códigos de Huffman
    CodigoHuffman *codigos = gerar_codigos(raiz, caracteres_unicos);
    if (!codigos)
    {
        liberar_arvore_huffman(raiz);
        free(tabela_freq);
        return 0;
    }

    // Abrir arquivos de entrada e saída
    FILE *arquivo_entrada = fopen(nome_arquivo_entrada, "rb");
    FILE *arquivo_saida = fopen(nome_arquivo_saida, "wb");

    if (!arquivo_entrada || !arquivo_saida)
    {
        printf("Erro ao abrir arquivos\n");
        liberar_codigos(codigos, caracteres_unicos);
        liberar_arvore_huffman(raiz);
        free(tabela_freq);
        if (arquivo_entrada)
            fclose(arquivo_entrada);
        if (arquivo_saida)
            fclose(arquivo_saida);
        return 0;
    }

    // Obter tamanho do arquivo original
    fseek(arquivo_entrada, 0, SEEK_END);
    int tamanho_original = ftell(arquivo_entrada);
    fseek(arquivo_entrada, 0, SEEK_SET);

    // Escrever cabeçalho: tamanho original e tabela de caracteres
    CabecalhoCompressao cabecalho;
    cabecalho.tamanho_original = tamanho_original;
    cabecalho.caracteres_unicos = caracteres_unicos;
    cabecalho.tamanho_comprimido = 0; // Será atualizado depois

    fwrite(&cabecalho, sizeof(CabecalhoCompressao), 1, arquivo_saida);

    // Escrever a tabela de frequências (necessária para descompressão)
    fwrite(tabela_freq, sizeof(FrequenciaCaractere), caracteres_unicos, arquivo_saida);

    // Salvar a posição atual para atualizar o tamanho comprimido depois
    long pos_fim_cabecalho = ftell(arquivo_saida);

    // Escrever os dados comprimidos
    unsigned char byte = 0;
    int pos_bit = 0;
    unsigned char byte_lido;

    // Ler o arquivo de entrada e escrever dados comprimidos
    while (fread(&byte_lido, 1, 1, arquivo_entrada) == 1)
    {
        char *codigo = encontrar_codigo(codigos, caracteres_unicos, byte_lido);
        for (int i = 0; codigo[i]; i++)
        {
            escrever_bit(arquivo_saida, codigo[i] == '1', &byte, &pos_bit);
        }
    }

    // Escrever bits restantes (completando o byte com 0s)
    if (pos_bit > 0)
    {
        fwrite(&byte, 1, 1, arquivo_saida);
    }

    // Atualizar o tamanho comprimido no cabeçalho
    long pos_fim_comprimido = ftell(arquivo_saida);
    cabecalho.tamanho_comprimido = pos_fim_comprimido - pos_fim_cabecalho;

    fseek(arquivo_saida, 0, SEEK_SET);
    fwrite(&cabecalho, sizeof(CabecalhoCompressao), 1, arquivo_saida);

    // Limpar
    fclose(arquivo_entrada);
    fclose(arquivo_saida);
    liberar_codigos(codigos, caracteres_unicos);
    liberar_arvore_huffman(raiz);
    free(tabela_freq);

    return 1;
}

// Função para ler um bit do arquivo de entrada
int ler_bit(FILE *arquivo, unsigned char *byte, int *pos_bit)
{
    if (*pos_bit == 0)
    {
        if (fread(byte, 1, 1, arquivo) != 1)
        {
            return -1; // Fim do arquivo
        }
        *pos_bit = 8;
    }

    (*pos_bit)--;
    return (*byte >> *pos_bit) & 1;
}

// Função para descomprimir um arquivo
int descomprimir_arquivo(const char *nome_arquivo_entrada, const char *nome_arquivo_saida)
{
    FILE *arquivo_entrada = fopen(nome_arquivo_entrada, "rb");
    if (!arquivo_entrada)
    {
        printf("Erro ao abrir arquivo de entrada\n");
        return 0;
    }

    // Ler cabeçalho
    CabecalhoCompressao cabecalho;
    if (fread(&cabecalho, sizeof(CabecalhoCompressao), 1, arquivo_entrada) != 1)
    {
        printf("Erro ao ler cabeçalho\n");
        fclose(arquivo_entrada);
        return 0;
    }

    // Ler tabela de frequências
    FrequenciaCaractere *tabela_freq = (FrequenciaCaractere *)malloc(cabecalho.caracteres_unicos * sizeof(FrequenciaCaractere));
    if (!tabela_freq)
    {
        printf("Erro de alocação de memória\n");
        fclose(arquivo_entrada);
        return 0;
    }

    if (fread(tabela_freq, sizeof(FrequenciaCaractere), cabecalho.caracteres_unicos, arquivo_entrada) != cabecalho.caracteres_unicos)
    {
        printf("Erro ao ler tabela de frequências\n");
        free(tabela_freq);
        fclose(arquivo_entrada);
        return 0;
    }

    // Reconstruir árvore de Huffman
    struct NoHuffman *raiz = construir_arvore_huffman(tabela_freq, cabecalho.caracteres_unicos);
    if (!raiz)
    {
        printf("Erro ao construir árvore de Huffman\n");
        free(tabela_freq);
        fclose(arquivo_entrada);
        return 0;
    }

    // Abrir arquivo de saída
    FILE *arquivo_saida = fopen(nome_arquivo_saida, "wb");
    if (!arquivo_saida)
    {
        printf("Erro ao abrir arquivo de saída\n");
        liberar_arvore_huffman(raiz);
        free(tabela_freq);
        fclose(arquivo_entrada);
        return 0;
    }

    // Decodificar os dados
    int bytes_escritos = 0;
    unsigned char byte = 0;
    int pos_bit = 0;
    struct NoHuffman *atual = raiz;

    while (bytes_escritos < cabecalho.tamanho_original)
    {
        int bit = ler_bit(arquivo_entrada, &byte, &pos_bit);
        if (bit == -1)
            break; // Fim do arquivo

        // Percorrer a árvore de acordo com o bit
        if (bit == 0)
        {
            atual = atual->esquerda;
        }
        else
        {
            atual = atual->direita;
        }

        // Se alcançar um nó folha, escrever o caractere e voltar à raiz
        if (!atual->esquerda && !atual->direita)
        {
            fwrite(&atual->caractere, 1, 1, arquivo_saida);
            bytes_escritos++;
            atual = raiz;
        }
    }

    // Limpar
    fclose(arquivo_entrada);
    fclose(arquivo_saida);
    liberar_arvore_huffman(raiz);
    free(tabela_freq);

    return 1;
}

// Função para obter informações de compressão
InformacaoCompressao obter_informacao_compressao(const char *arquivo_original, const char *arquivo_comprimido)
{
    InformacaoCompressao info = {0, 0, 0.0};

    FILE *orig = fopen(arquivo_original, "rb");
    FILE *comp = fopen(arquivo_comprimido, "rb");

    if (!orig || !comp)
    {
        if (orig)
            fclose(orig);
        if (comp)
            fclose(comp);
        return info;
    }

    // Obter tamanho do arquivo original
    fseek(orig, 0, SEEK_END);
    info.tamanho_original = ftell(orig);

    // Obter tamanho do arquivo comprimido
    fseek(comp, 0, SEEK_END);
    info.tamanho_comprimido = ftell(comp);

    // Calcular taxa de compressão
    if (info.tamanho_original > 0)
    {
        info.taxa_compressao = (double)info.tamanho_original / info.tamanho_comprimido;
    }

    fclose(orig);
    fclose(comp);

    return info;
}