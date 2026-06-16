#include <stdio.h>
#include <string.h>

#define MAX_MUSICAS 30

struct Musica
{
    char nome[50];
    char compositor[50];
    char categoria[50];
};

// Função auxiliar para remover a quebra de linha do fgets
void limpaString(char string[])
{
    size_t tam = strlen(string);
    if (tam > 0 && string[tam - 1] == '\n')
    {
        string[tam - 1] = '\0';
    }
}

int main()
{
    struct Musica playlist[MAX_MUSICAS] = {
        {"Se hoje me toca", "José Jr", "Gospel"},
        {"Chove chuva", "Jorge Ben Jor", "MPB"},
        {"No secreto", "Luma Elpídio", "Gospel"},
    };

    int tamanho = 3;
    int opcao;
    int atual = 0;
    int tocando = 1;

    do
    {
        printf("\n=== SISTEMA DE MUSICAS ===\n");
        printf("1 - Cadastrar musica\n");
        printf("2 - Iniciar playlist\n");
        printf("0 - Sair\n\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // consome o Enter

        switch (opcao)
        {
        case 1:
            if (tamanho < MAX_MUSICAS)
            {
                printf("\nNome da musica: ");
                fgets(playlist[tamanho].nome, 50, stdin);
                limpaString(playlist[tamanho].nome);

                printf("Compositor: ");
                fgets(playlist[tamanho].compositor, 50, stdin);
                limpaString(playlist[tamanho].compositor);

                printf("Categoria: ");
                fgets(playlist[tamanho].categoria, 50, stdin);
                limpaString(playlist[tamanho].categoria);

                tamanho++;
                printf("\nMusica cadastrada com sucesso!\n");
            }
            else
            {
                printf("\nLimite de musicas atingido!\n");
            }
            break;

        case 2:
            if (tamanho == 0)
            {
                printf("\nNenhuma musica cadastrada para iniciar.\n");
            }
            else
            {
                int opcao_player;
                do
                {
                    printf("\n=== PLAYER DE MUSICA ===\n");
                    printf("Status: %s\n", tocando ? "▶️ TOCANDO" : "⏸️ PAUSADO");
                    printf("Musica Atual: %s (%s) - %s\n",
                           playlist[atual].nome,
                           playlist[atual].categoria,
                           playlist[atual].compositor);

                    printf("\n=== CASO QUEIRA, TECLE: ===\n");
                    printf("1 - (Des)Pausar musica\n");
                    printf("2 - Pular musica\n");
                    printf("3 - Voltar musica\n");
                    printf("0 - Voltar ao menu inicial\n\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opcao_player);
                    getchar();

                    switch (opcao_player)
                    {
                    case 1:
                        tocando = !tocando;
                        break;
                    case 2:
                        if (atual < tamanho - 1)
                        {
                            atual++;
                            tocando = 1;
                        }
                        else
                        {
                            printf("\nVoce ja esta na ultima musica da playlist!\n");
                        }
                        break;
                    case 3:
                        if (atual > 0)
                        {
                            atual--;
                            tocando = 1;
                        }
                        else
                        {
                            printf("\nVoce ja esta na primeira musica da playlist!\n");
                        }
                        break;
                    case 0:
                        printf("\nVoltando ao menu inicial...\n");
                        break;
                    default:
                        printf("\nOpcao invalida!\n");
                    }
                } while (opcao_player != 0);
            }
            break;

        case 0:
            printf("\nEncerrando o sistema...\n");
            break;

        default:
            printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}