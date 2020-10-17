#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <dirent.h>
#include <string.h>

/** Define the default output */
#define CONF_DEFAULT_CODEPAGE 1252
#define CONF_FILE_NAME_CHARACTERS 20

void showMenuInformation();
void startGame();
int getTotalNumberOfQuestions(char directoryName[CONF_FILE_NAME_CHARACTERS]);

int main()
{
    SetConsoleOutputCP(CONF_DEFAULT_CODEPAGE);
    SetConsoleCP(CONF_DEFAULT_CODEPAGE);
    // setlocale(LC_ALL, "portuguese");
    // showMenuInformation();
    printf("O n�mero total de arquivos na pasta � de: %d", getTotalNumberOfQuestions("questions"));
    return 0;
}

void showMenuInformation()
{
    char choosedOption;

    printf("\nQUIZ GAME");
    printf("\n_________\n");
    printf("\nSeja b鴴d�saem vindo!");
    printf("\n_________\n");
    printf("QUIZ GAME");
    printf("\n_________\n\n");
    printf("> Pressione S para come�ar o jogo\n");
    printf("> Pressione Q para sair do jogo\n\n");

    printf("\n\nDigite sua op��o: ");
    scanf("%c", &choosedOption);

    switch(choosedOption)
    {
        case 's':
            startGame();
            break;
        case 'q': case 'Q':
            printf("\nSaindo...\n\n");
            exit(0);
            break;
        default:
            break;
    }
}

void startGame()
{
    system("cls");
    printf("Come�ando o jogo");
    exit(0);
}

int getTotalNumberOfQuestions(char directoryName[CONF_FILE_NAME_CHARACTERS])
{
    int totalFiles = 0;
    DIR *directory;
    struct dirent *entry;

    directory = opendir(directoryName);

    if (directory == NULL)
    {
        printf("\n\nAlgo deu errado ao abrir o diret�rio %s!", directoryName);
        return 0;
    }

    while ((entry = readdir(directory)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcasecmp(entry->d_name, "..") != 0)
        {
            totalFiles++;
        }
    }

    closedir(directory);
    return totalFiles;
}

void askQuestion()
{
}

