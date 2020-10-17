#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void showMenuInformation();
void startGame();

int main()
{
    setlocale(LC_ALL, "portuguese");
    showMenuInformation();
    return 0;
}

void showMenuInformation()
{
    char choosedOption;

    printf("\nQUIZ GAME");
    printf("\n_________\n");
    printf("\nSeja bem vindo!");
    printf("\n_________\n");
    printf("QUIZ GAME");
    printf("\n_________\n\n");
    printf("> Pressione S para começar o jogo\n");
    printf("> Pressione Q para sair do jogo\n\n");
    scanf("%c", &choosedOption);

    switch(choosedOption)
    {
        case 's':
            startGame();
            break;
        case 'q':
            printf("Saindo...");
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

