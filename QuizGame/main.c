#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

#define CONF_DEFAULT_CODEPAGE 1252
#define CONF_FILE_NAME_CHARACTERS 20

/**
 * QUESTION
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
void readQuestions(int totalNumberOfQuestions);
int getTotalNumberOfQuestions(char directoryName[CONF_FILE_NAME_CHARACTERS]);
int askQuestion(int questionIndex, question *questionToShow);

int main()
{
    SetConsoleOutputCP(CONF_DEFAULT_CODEPAGE);
    SetConsoleCP(CONF_DEFAULT_CODEPAGE);
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
    for (int questionNumer = 1; questionNumer <= totalNumberOfQuestions; questionNumer++)
    {
        char questionFileName[CONF_FILE_NAME_CHARACTERS];
        snprintf(questionFileName, CONF_FILE_NAME_CHARACTERS, "question%d.txt", questionNumer);

        FILE *fileQuestion;
        fileQuestion = fopen(questionFileName, "r");

        if (fileQuestion == NULL)
        {
            printf("\n\nOcorreu um erro ao abrir a pergunta %s!\n\n", questionFileName);
            return;
        }

        question mountQuestion;
        char chainOfCharacters[CONF_QUESTION];
        int currentLine = 0;

        while(!feof(fileQuestion))
        {
            fgets(chainOfCharacters, CONF_QUESTION, fileQuestion);
            currentLine++;

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
                mountQuestion.correctAnswer = fgetc(fileQuestion);
            }

            /* if (currentLine == 6)
            {
                mountQuestion.correctAnswer = fgetc(fileQuestion);
            } */

            if (currentLine == 7)
            {
                strcpy(mountQuestion.explanation, chainOfCharacters);
            }
        }

        if (askQuestion(questionNumer, &mountQuestion) == 1)
        {
            printf("\nAcertou!!!");
        }
        else
        {
            printf("\nResposta errada!\n%s", mountQuestion.explanation);
        }


        if(fclose(fileQuestion) != 0)
        {
            printf("\n\nOcorreu um erro ao fechar o arquivo %s!", questionFileName);
        }

        printf("\n\nPara ir para a próxima pergunta pressione qualquer tecla\n");
        fflush(stdin);
        getchar();
    }
}

int askQuestion(int questionIndex, question *questionToShow)
{
    char userResponse;

    system("cls");
    printf("\n\nQUESTÃO %d: %s \n", questionIndex, questionToShow->question);
    printf("A) %s \n", questionToShow->alternativeA);
    printf("B) %s \n", questionToShow->alternativeB);
    printf("C) %s \n", questionToShow->alternativeC);
    printf("D) %s \n", questionToShow->alternativeD);

    printf("\nDigite a sua resposta: ");
    fflush(stdin);
    scanf("%c", &userResponse);

    if (userResponse == questionToShow->correctAnswer)
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

