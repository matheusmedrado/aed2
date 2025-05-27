#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "arvoreBinaria.h"

// Estrutura para a tabela de frequências
typedef struct
{
    unsigned char caractere;
    int frequencia;
} FrequenciaCaractere;

// Estrutura para armazenar códigos de Huffman
typedef struct
{
    unsigned char caractere;
    char *codigo;
} CodigoHuffman;

// Estrutura para o cabeçalho dos dados comprimidos
typedef struct
{
    int tamanho_original;   // Tamanho do arquivo original em bytes
    int tamanho_comprimido; // Tamanho dos dados comprimidos em bytes
    int caracteres_unicos;  // Número de caracteres únicos no arquivo original
} CabecalhoCompressao;

// Função para comprimir um arquivo usando codificação de Huffman
int comprimir_arquivo(const char *nome_arquivo_entrada, const char *nome_arquivo_saida);

// Função para descomprimir um arquivo comprimido com codificação de Huffman
int descomprimir_arquivo(const char *nome_arquivo_entrada, const char *nome_arquivo_saida);

// Estrutura para informações de compressão
typedef struct
{
    long tamanho_original;
    long tamanho_comprimido;
    double taxa_compressao;
} InformacaoCompressao;

// Função para obter informações de compressão
InformacaoCompressao obter_informacao_compressao(const char *arquivo_original, const char *arquivo_comprimido);

#endif // HUFFMAN_H