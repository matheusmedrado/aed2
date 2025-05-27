#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

void exibir_menu()
{
    printf("\n===== Sistema de Compressão Huffman =====\n");
    printf("0. Como usar o programa\n");
    printf("1. Comprimir um arquivo\n");
    printf("2. Descomprimir um arquivo\n");
    printf("3. Mostrar informações de compressão\n");
    printf("4. Sair\n");
    printf("Digite sua escolha: ");
}

void exibir_tutorial()
{
    printf("\n===== Como Usar o Sistema de Compressão Huffman =====\n");
    printf("Este programa permite comprimir e descomprimir arquivos usando o algoritmo de Huffman.\n");
    printf("Siga as instruções abaixo para cada opção:\n\n");
    printf("1. Comprimir um arquivo:\n");
    printf("   - Escolha a opção 1.\n");
    printf("   - Digite o caminho do arquivo que deseja comprimir (ex.: texto.txt).\n");
    printf("   - Digite o nome do arquivo de saída (ex.: texto_comprimido.huf).\n");
    printf("   - O programa criará um arquivo comprimido e mostrará as informações de compressão.\n\n");
    printf("2. Descomprimir um arquivo:\n");
    printf("   - Escolha a opção 2.\n");
    printf("   - Digite o caminho do arquivo comprimido (ex.: texto_comprimido.huf).\n");
    printf("   - Digite o nome do arquivo de saída (ex.: texto_descomprimido.txt).\n");
    printf("   - O programa restaurará o arquivo original.\n\n");
    printf("3. Mostrar informações de compressão:\n");
    printf("   - Escolha a opção 3.\n");
    printf("   - Digite o caminho do arquivo original e do arquivo comprimido.\n");
    printf("   - O programa mostrará o tamanho original, o tamanho comprimido, o espaço economizado e a taxa de compressão.\n\n");
    printf("4. Sair:\n");
    printf("   - Escolha a opção 4 para fechar o programa.\n\n");
    printf("Dicas:\n");
    printf("- Certifique-se de que os arquivos existam e sejam acessíveis.\n");
    printf("- Use nomes de arquivos com extensões claras para evitar confusão (ex.: .huf para arquivos comprimidos).\n");
    printf("===================================================\n");
}

int main()
{
    int escolha;
    char arquivo_entrada[256];
    char arquivo_saida[256];

    while (1)
    {
        exibir_menu();
        if (scanf("%d", &escolha) != 1)
        {
            // Limpar buffer de entrada se a entrada for inválida
            while (getchar() != '\n')
                ;
            printf("Entrada inválida. Por favor, digite um número.\n");
            continue;
        }

        // Limpar buffer de entrada
        while (getchar() != '\n')
            ;

        switch (escolha)
        {
        case 0: // Exibir tutorial
            exibir_tutorial();
            break;

        case 1: // Comprimir
            printf("Digite o arquivo a ser comprimido: ");
            if (fgets(arquivo_entrada, sizeof(arquivo_entrada), stdin))
            {
                // Remover caractere de nova linha
                arquivo_entrada[strcspn(arquivo_entrada, "\n")] = 0;
            }

            printf("Digite o nome do arquivo de saída: ");
            if (fgets(arquivo_saida, sizeof(arquivo_saida), stdin))
            {
                arquivo_saida[strcspn(arquivo_saida, "\n")] = 0;
            }

            printf("Comprimindo %s para %s...\n", arquivo_entrada, arquivo_saida);
            if (comprimir_arquivo(arquivo_entrada, arquivo_saida))
            {
                printf("Compressão bem-sucedida!\n");

                // Exibir informações de compressão
                InformacaoCompressao info = obter_informacao_compressao(arquivo_entrada, arquivo_saida);
                printf("Tamanho original: %ld bytes\n", info.tamanho_original);
                printf("Tamanho comprimido: %ld bytes\n", info.tamanho_comprimido);
                printf("Taxa de compressão: %.2f:1\n", info.taxa_compressao);
            }
            else
            {
                printf("Falha na compressão!\n");
            }
            break;

        case 2: // Descomprimir
            printf("Digite o arquivo a ser descomprimido: ");
            if (fgets(arquivo_entrada, sizeof(arquivo_entrada), stdin))
            {
                arquivo_entrada[strcspn(arquivo_entrada, "\n")] = 0;
            }

            printf("Digite o nome do arquivo de saída: ");
            if (fgets(arquivo_saida, sizeof(arquivo_saida), stdin))
            {
                arquivo_saida[strcspn(arquivo_saida, "\n")] = 0;
            }

            printf("Descomprimindo %s para %s...\n", arquivo_entrada, arquivo_saida);
            if (descomprimir_arquivo(arquivo_entrada, arquivo_saida))
            {
                printf("Descompressão bem-sucedida!\n");
            }
            else
            {
                printf("Falha na descompressão!\n");
            }
            break;

        case 3: // Mostrar informações de compressão
            printf("Digite o arquivo original: ");
            if (fgets(arquivo_entrada, sizeof(arquivo_entrada), stdin))
            {
                arquivo_entrada[strcspn(arquivo_entrada, "\n")] = 0;
            }

            printf("Digite o arquivo comprimido: ");
            if (fgets(arquivo_saida, sizeof(arquivo_saida), stdin))
            {
                arquivo_saida[strcspn(arquivo_saida, "\n")] = 0;
            }

            InformacaoCompressao info = obter_informacao_compressao(arquivo_entrada, arquivo_saida);
            printf("\nInformações de Compressão:\n");
            printf("Tamanho do arquivo original: %ld bytes\n", info.tamanho_original);
            printf("Tamanho do arquivo comprimido: %ld bytes\n", info.tamanho_comprimido);
            printf("Espaço economizado: %ld bytes (%.2f%%)\n",
                   info.tamanho_original - info.tamanho_comprimido,
                   100.0 * (1.0 - (double)info.tamanho_comprimido / info.tamanho_original));
            printf("Taxa de compressão: %.2f:1\n", info.taxa_compressao);
            break;

        case 4: // Sair
            printf("Saindo do programa. Até logo!\n");
            return 0;

        default:
            printf("Escolha inválida. Tente novamente.\n");
        }
    }

    return 0;
}