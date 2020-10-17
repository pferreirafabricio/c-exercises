#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/** Define the default output */
#define CONF_DEFAULT_CODEPAGE 1252

void showMenuInformation();
void startGame();

int main()
{
    SetConsoleOutputCP(CONF_DEFAULT_CODEPAGE);
    SetConsoleCP(CONF_DEFAULT_CODEPAGE);
    // setlocale(LC_ALL, "portuguese");
    showMenuInformation();
    return 0;
}

void showMenuInformation()
{
    char choosedOption;

    printf("\nQUIZ GAME");
    printf("\n_________\n");
    printf("\nSeja bé´´d´saem vindo!");
    printf("\n_________\n");
    printf("QUIZ GAME");
    printf("\n_________\n\n");
    printf("> Pressione S para começar o jogo\n");
    printf("> Pressione Q para sair do jogo\n\n");

    printf("\n\nDigite sua opção: ");
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
    printf("Começando o jogo");
    exit(0);
}

