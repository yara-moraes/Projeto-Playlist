#include <stdio.h>
#include <string.h>

#define MAX_MUSICAS 30

struct Musica
{
    char nome[50];
    char compositor[50];
    char categoria[50];
};

void limpaString(char string[])
{
    size_t tam = strlen(string);

    if (tam > 0 && string[tam - 1] == '\n')
        string[tam - 1] = '\0';
    
}

void salvarPlaylist(struct Musica playlist[], int tamanho)
{
    FILE *arquivo = fopen("playlist.json", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao criar arquivo!\n");
        return;
    }

    fprintf(arquivo, "[\n");

    for (int i = 0; i < tamanho; i++)
    {
        fprintf(
            arquivo,
            "  {\"nome\":\"%s\",\"compositor\":\"%s\",\"categoria\":\"%s\"}",
            playlist[i].nome,
            playlist[i].compositor,
            playlist[i].categoria);

        if (i < tamanho - 1)
            fprintf(arquivo, ",");

        fprintf(arquivo, "\n");
    }

    fprintf(arquivo, "]");
    fclose(arquivo);
}

int carregarPlaylist(struct Musica playlist[])
{
    FILE *arquivo = fopen("playlist.json", "r");

    if (arquivo == NULL)
    {
        arquivo = fopen("playlist.json", "w");

        if (arquivo != NULL)
        {
            fprintf(arquivo, "[]");
            fclose(arquivo);
        }

        return 0;
    }

    int i = 0;
    char c;

    fscanf(arquivo, " %c", &c);

    while (i < MAX_MUSICAS)
    {
        int lidos = fscanf(
            arquivo,
            " {\"nome\":\"%49[^\"]\",\"compositor\":\"%49[^\"]\",\"categoria\":\"%49[^\"]\"}",
            playlist[i].nome,
            playlist[i].compositor,
            playlist[i].categoria);

        if (lidos != 3)
            break;

        i++;

        fscanf(arquivo, " %c", &c);

        if (c == ']')
            break;
    }

    fclose(arquivo);
    return i;
}

void listarMusicas(struct Musica playlist[], int tamanho)
{
    if (tamanho == 0)
    {
        printf("\nNenhuma musica cadastrada.\n");
        return;
    }

    printf("\n=== PLAYLIST COMPLETA ===\n");

    for (int i = 0; i < tamanho; i++)
    {
        printf("\nMusica %d\n", i + 1);
        printf("Nome: %s\n", playlist[i].nome);
        printf("Compositor: %s\n", playlist[i].compositor);
        printf("Categoria: %s\n", playlist[i].categoria);
    }
}

void deletarMusica(struct Musica playlist[], int *tamanho)
{
    if (*tamanho == 0)
    {
        printf("\nNenhuma musica cadastrada.\n");
        return;
    }

    listarMusicas(playlist, *tamanho);

    int indice;
    printf("\nDigite o numero da musica que deseja deletar: ");
    scanf("%d", &indice);
    getchar();

    indice--;

    if (indice < 0 || indice >= *tamanho)
    {
        printf("\nMusica invalida!\n");
        return;
    }

    for (int i = indice; i < *tamanho - 1; i++)
    {
        playlist[i] = playlist[i + 1];
    }

    (*tamanho)--;

    salvarPlaylist(playlist, *tamanho);

    printf("\nMusica removida com sucesso!\n");
}

int main()
{
    struct Musica playlist[MAX_MUSICAS];
    int tamanho = carregarPlaylist(playlist);

    if (tamanho == 0)
    {
        strcpy(playlist[0].nome, "Se hoje me toca");
        strcpy(playlist[0].compositor, "Jose Jr");
        strcpy(playlist[0].categoria, "Gospel");

        strcpy(playlist[1].nome, "Chove chuva");
        strcpy(playlist[1].compositor, "Jorge Ben Jor");
        strcpy(playlist[1].categoria, "MPB");

        strcpy(playlist[2].nome, "No secreto");
        strcpy(playlist[2].compositor, "Luma Elpidio");
        strcpy(playlist[2].categoria, "Gospel");

        tamanho = 3;
        salvarPlaylist(playlist, tamanho);
    }
    
    void editarMusica(struct Musica playlist[], int tamanho)
{
    if (tamanho == 0)
    {
        printf("\nNenhuma musica cadastrada.\n");
        return;
    }

    listarMusicas(playlist, tamanho);

    int indice;

    printf("\nDigite o numero da musica que deseja editar: ");
    scanf("%d", &indice);
    getchar();

    indice--;

    if (indice < 0 || indice >= tamanho)
    {
        printf("\nMusica invalida!\n");
        return;
    }

    printf("\nNovo nome: ");
    fgets(playlist[indice].nome, 50, stdin);
    limpaString(playlist[indice].nome);

    printf("Novo compositor: ");
    fgets(playlist[indice].compositor, 50, stdin);
    limpaString(playlist[indice].compositor);

    printf("Nova categoria: ");
    fgets(playlist[indice].categoria, 50, stdin);
    limpaString(playlist[indice].categoria);

    salvarPlaylist(playlist, tamanho);

    printf("\nMusica editada com sucesso!\n");
}

    int opcao;
    int atual = 0;
    int tocando = 1;

    do
    {
        printf("\n=== SISTEMA DE MUSICAS ===\n");
        printf("1 - Cadastrar musica\n");
        printf("2 - Iniciar playlist\n");
        printf("3 - Ver playlist completa\n");
        printf("4 - Deletar musica\n");
        printf("5 - Editar musica\n");
        printf("0 - Sair\n\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

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
                salvarPlaylist(playlist, tamanho);

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
                printf("\nNenhuma musica cadastrada.\n");
            }
            else
            {
                int opcao_player;
                atual = 0;

                do
                {
                    printf("\n=== PLAYER DE MUSICA ===\n");
                    printf("Status: %s\n", tocando ? "TOCANDO" : "PAUSADO");
                    printf("Musica Atual: %s (%s) - %s\n",
                           playlist[atual].nome,
                           playlist[atual].categoria,
                           playlist[atual].compositor);

                    printf("\n1 - (Des)Pausar musica\n");
                    printf("2 - Pular musica\n");
                    printf("3 - Voltar musica\n");
                    printf("0 - Voltar\n\n");
                    printf("Escolha: ");

                    scanf("%d", &opcao_player);
                    getchar();

                    switch (opcao_player)
                    {
                    case 1:
                        tocando = !tocando;
                        break;

                    case 2:
                        if (atual < tamanho - 1)
                            atual++;
                        else
                            printf("Ultima musica!\n");
                        break;

                    case 3:
                        if (atual > 0)
                            atual--;
                        else
                            printf("Primeira musica!\n");
                        break;
                    }

                } while (opcao_player != 0);
            }
            break;

        case 3:
            listarMusicas(playlist, tamanho);
            break;

        case 4:
            deletarMusica(playlist, &tamanho);
            break;
            
        case 5:
            editarMusica(playlist, tamanho);
            break;
    
        case 0:
            printf("\nEncerrando...\n");
            break;

        default:
            printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
