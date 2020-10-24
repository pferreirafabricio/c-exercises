#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

#define CONF_DEFAULT_CODEPAGE 1252
#define CONF_FILE_NAME_CHARACTERS 20

/**
    QUESTION
*/
#define CONF_SIZE_QUESTION_STRUCT 321
#define CONF_QUESTION 100
#define CONF_QUESTION_EXPLANATION 100
#define CONF_QUESTION_ALTERNATIVE 30

typedef struct
{
    char question[CONF_QUESTION];
    char alternativeA[CONF_QUESTION];
    char alternativeB[CONF_QUESTION];
    char alternativeC[CONF_QUESTION];
    char alternativeD[CONF_QUESTION];
    char correctAnswer;
    char explanation[CONF_QUESTION_EXPLANATION];
} question;

typedef struct
{
    int correctAnswers;
    int incorrectAnswers;
    int finalScore;
} game;

/** Initialize functions */
void showMenuInformation();
void startGame();
int getTotalNumberOfQuestions(char directoryName[CONF_FILE_NAME_CHARACTERS]);
void readQuestions(int totalNumberOfQuestions);
int askQuestion(question questionToShow);

int main()
{
    // SetConsoleOutputCP(CONF_DEFAULT_CODEPAGE);
    // SetConsoleCP(CONF_DEFAULT_CODEPAGE);
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
    printf("==== Começando o jogo ==== \n\n");

    readQuestions(getTotalNumberOfQuestions("questions"));
    exit(0);
}

void readQuestions(int totalNumberOfQuestions)
{
    for (int questionNumer = 1; questionNumer <= 1; questionNumer++)
    {
        /*
        ===== GERAR O NOME DO ARQUIVO ====
        char questionFileName[CONF_FILE_NAME_CHARACTERS];
        char buffer[CONF_FILE_NAME_CHARACTERS];
        snprintf(buffer, CONF_FILE_NAME_CHARACTERS, "%d", questionNumer);
        strcat(questionFileName, buffer); */

        /*
        strcat(questionFileName, "question");
        strcat(questionFileName, sprintf(questionFileName, "%d", questionNumer));
        strcat(questionFileName, ".txt");
        */

        char questionFileName[CONF_FILE_NAME_CHARACTERS] = "question1.txt";

        FILE *fileQuestion;
        fileQuestion = fopen(questionFileName, "r");

        if (fileQuestion == NULL)
        {
            printf("\n\nOcorreu um erro ao abrir a pergunta %s!", questionFileName);
            return;
        }

        question mountQuestion;
        char chainOfCharacters[CONF_QUESTION];
        int currentLine = 0;

        while(!feof(fileQuestion))
        {

            /* for(int i = 0; i < CONF_QUESTION; i++)
            {
                mountQuestion.question[i] = '\0';
                mountQuestion.explanation[i] = '\0';
            }

            for(int i = 0; i < CONF_QUESTION_ALTERNATIVE; i++)
            {
                mountQuestion.alternativeA[CONF_QUESTION_ALTERNATIVE] = '\0';
                mountQuestion.alternativeB[CONF_QUESTION_ALTERNATIVE] = '\0';
                mountQuestion.alternativeC[CONF_QUESTION_ALTERNATIVE] = '\0';
                mountQuestion.alternativeD[CONF_QUESTION_ALTERNATIVE] = '\0';
            } */

            fgets(chainOfCharacters, CONF_QUESTION, fileQuestion);
            ++currentLine;
            printf("Na linha %d: %s", currentLine, chainOfCharacters);

            if (currentLine == 1)
            {
                strcpy(mountQuestion.question, chainOfCharacters);
            }

            if (currentLine == 2)
            {
                strcpy(mountQuestion.alternativeA, chainOfCharacters);
            }

            if (currentLine == 3)
            {
                strcpy(mountQuestion.alternativeB, chainOfCharacters);
            }

            if (currentLine == 4)
            {
                strcpy(mountQuestion.alternativeC, chainOfCharacters);
            }

            if (currentLine == 5)
            {
                strcpy(mountQuestion.alternativeD, chainOfCharacters);
            }

            if (currentLine == 6)
            {
                mountQuestion.correctAnswer = chainOfCharacters;
            }

            if (currentLine == 7)
            {
                strcpy(mountQuestion.explanation, chainOfCharacters);
            }
        }

        if (askQuestion(mountQuestion) == 1)
        {
            printf("\n\nAcertou!!!");
        }


        if(fclose(fileQuestion) != 0)
        {
            printf("\n\nOcorreu um erro ao fechar o arquivo %s!", questionFileName);
        }

        printf("\n\nTodas as funções foram concluídas!");
    }
}

int askQuestion(question questionToShow)
{
    char userResponse;

    printf("%s \n", questionToShow.question);
    printf("A) %s \n", questionToShow.alternativeA);
    printf("B) %s \n", questionToShow.alternativeB);
    printf("C) %s \n", questionToShow.alternativeC);
    printf("D) %s \n", questionToShow.alternativeD);

    printf("\n\nDigite a sua resposta: ");
    scanf("%c", &userResponse);

    printf("Letra correta é: %c", questionToShow.correctAnswer);

    if (userResponse == questionToShow.correctAnswer)
    {
        return 1;
    }

    return 0;
}


/**
 * HELPERS
 */
int getTotalNumberOfQuestions(char directoryName[CONF_FILE_NAME_CHARACTERS])
{
    int totalFiles = 0;
    DIR *directory;
    struct dirent *entry;

    directory = opendir(directoryName);

    if (directory == NULL)
    {
        printf("\n\nAlgo deu errado ao abrir o diretório %s!", directoryName);
        return 0;
    }

    while ((entry = readdir(directory)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            totalFiles++;
        }
    }

    closedir(directory);
    return totalFiles;
}

void sanitizeString(char string[CONF_QUESTION])
{
    memset(string, '\0', CONF_QUESTION);
}

