#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/**
 * GENERAL CONFIGURATIONS
 */
#define CONF_DEFAULT_CODEPAGE 1252
#define CONF_FILE_NAME_CHARACTERS 20

/**
 * QUESTION CONFIGURATIONS
 */
#define CONF_QUESTION 100
#define CONF_SCORE_FILE_NAME "score.bin"
#define CONF_QUESTION_FOLDER "questions"

/**
 * COLORS CONFIGURATIONS
 */
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

/**
 * STRUCTS
 */
typedef struct
{
    char question[CONF_QUESTION];
    char alternativeA[CONF_QUESTION];
    char alternativeB[CONF_QUESTION];
    char alternativeC[CONF_QUESTION];
    char alternativeD[CONF_QUESTION];
    char correctAnswer;
    char explanation[CONF_QUESTION];
} Question;

typedef struct
{
    int correctAnswers;
    int incorrectAnswers;
    int finalScore;
} GameScore;

/**
 * Initialize functions
 */
void showMenuInformation();
void startGame();
void readQuestions(int totalNumberOfQuestions);
int getTotalNumberOfQuestions(char directoryName[CONF_FILE_NAME_CHARACTERS]);
int askQuestion(int questionIndex, Question *questionToShow);
void getScore(char scoreFileName[CONF_FILE_NAME_CHARACTERS]);
void saveScore(char scoreFileName[CONF_FILE_NAME_CHARACTERS], GameScore *gameToSave);
int calculateTotalScore(GameScore gameScoreToCalculate);
void finishGame(GameScore *gameScore);
bool nextQuestion();

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

    system("cls");
    printf(YEL "\nPEPPY - O QUIZ GAME" RESET);
    printf("\n_________");
    printf("\n\nSeja bem vindo!");
    printf("\n_________\n");
    getScore(CONF_SCORE_FILE_NAME);
    printf("\n" CYN " > " RESET "Digite S para começar o jogo");
    printf("\n" CYN " > " RESET "Digite Q para sair do jogo");

    printf("\n\nOpção desejada: ");
    fflush(stdin);
    scanf("%c", &choosedOption);

    switch(choosedOption)
    {
        case 's': case 'S':
            startGame();
            break;
        case 'r': case 'R':
            resetScore();
            break;
        case 'q': case 'Q':
            exitGame();
            break;
        default:
            showMenuInformation();
            break;
    }
}

void startGame()
{
    readQuestions(getTotalNumberOfQuestions(CONF_QUESTION_FOLDER));
    exit(0);
}

void readQuestions(int totalNumberOfQuestions)
{
    GameScore gameScore;

    for (int questionNumer = 1; questionNumer <= totalNumberOfQuestions; questionNumer++)
    {
        char questionFileName[CONF_FILE_NAME_CHARACTERS];
        snprintf(questionFileName, CONF_FILE_NAME_CHARACTERS, "question%d.txt", questionNumer);

        FILE *fileQuestion;
        fileQuestion = fopen(questionFileName, "r");

        if (fileQuestion == NULL)
        {
            printf(RED "\n\nOcorreu um erro ao abrir a pergunta %s!\n\n" RESET, questionFileName);
            return;
        }

        Question mountQuestion;
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
            printf(GRN "\nAcertou :)" RESET);
            gameScore.correctAnswers++;
        }
        else
        {
            printf(RED "\nResposta errada!\n%s" RESET, mountQuestion.explanation);
            gameScore.incorrectAnswers++;
        }

        if(fclose(fileQuestion) != 0)
        {
            printf(RED "\n\nOcorreu um erro ao fechar o arquivo %s!" RESET, questionFileName);
        }

        if(nextQuestion())
            continue;
    }

    finishGame(&gameScore);
}

int askQuestion(int questionIndex, Question *questionToShow)
{
    char userResponse;

    system("cls");
    printf(CYN "\n\nQUESTÃO %d: " RESET "%s \n", questionIndex, questionToShow->question);
    printf(CYN "A) " RESET "%s \n", questionToShow->alternativeA);
    printf(CYN "B) " RESET "%s \n", questionToShow->alternativeB);
    printf(CYN "C) " RESET "%s \n", questionToShow->alternativeC);
    printf(CYN "D) " RESET "%s \n", questionToShow->alternativeD);

    printf("\nDigite a sua resposta: ");
    fflush(stdin);
    scanf("%c", &userResponse);

    if (userResponse == toupper(questionToShow->correctAnswer)
        || userResponse == tolower(questionToShow->correctAnswer))
    {
        return 1;
    }

    return 0;
}


/**
 * HELPERS
 */

void exitGame()
{
    printf("\nAdeus :) \n\n");
    exit(0);
}

bool nextQuestion()
{
    char response;

    printf("\n\nIr para a próxima pergunta: pressione ENTER");
    printf("\nVoltar a tela inicial: pressione H\n");
    fflush(stdin);
    scanf("%c", &response);

    if (response == 'h' || response == 'H')
    {
        showMenuInformation();
        return false;
    }

    return true;
}

int getTotalNumberOfQuestions(char directoryName[CONF_FILE_NAME_CHARACTERS])
{
    int totalFiles = 0;
    DIR *directory;
    struct dirent *entry;

    directory = opendir(directoryName);

    if (directory == NULL)
    {
        printf("\n\nAlgo deu errado ao abrir o diret?rio %s!", directoryName);
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

void saveScore(char scoreFileName[CONF_FILE_NAME_CHARACTERS], GameScore *gameToSave)
{
    FILE *scoreFile;
    scoreFile = fopen(scoreFileName, "wb+");

    if (scoreFile == NULL)
    {
        printf("\n\nOcorreu um erro ao abrir o arquivo %s, tente novamente mais tarde!\n\n", scoreFileName);
        return;
    }

    gameToSave->finalScore = calculateTotalScore(*gameToSave);
    fwrite(gameToSave, sizeof(GameScore), 1, scoreFile);

    if(ferror(scoreFile))
    {
        printf("\n\nOcorreu um erro ao salvar o seu score, tente novamente mais tarde!\n\n");
        return;
    }

    if(fclose(scoreFile) != 0)
    {
        printf("\n\nOcorreu um erro ao fechar o arquivo %s!", scoreFileName);
    }
}

int calculateTotalScore(GameScore gameScoreToCalculate)
{
    return gameScoreToCalculate.correctAnswers * 10;
}

void getScore(char scoreFileName[CONF_FILE_NAME_CHARACTERS])
{
    FILE *scoreFile;
    scoreFile = fopen(scoreFileName, "rb");
    GameScore currentGameScore;

    if (scoreFile == NULL)
    {
        return;
    }

    fread(&currentGameScore, sizeof(GameScore), 1, scoreFile);

    if(ferror(scoreFile))
    {
        printf("\n\nOcorreu um erro ao salvar o seu score, tente novamente mais tarde!\n\n");
        return;
    }

    printf("\n\nSeu score atual é de:"
           GRN "\n%d respostas certas" RESET
           RED "\n%d respostas incorretas" RESET
           MAG "\nTOTAL: %d pontos" RESET,
           currentGameScore.correctAnswers, currentGameScore.incorrectAnswers, currentGameScore.finalScore);

    if (currentGameScore.finalScore >= 90 )
    {
        printf(MAG " (você é fera!)" RESET);
    }

    printf("\n_________\n");
    printf("\n" CYN " > " RESET "Digite R para resetar o seu score");

    if(fclose(scoreFile) != 0)
    {
        printf("\n\nOcorreu um erro ao fechar o arquivo %s!", scoreFileName);
    }
}

void resetScore()
{
    char response;

    printf("Você quer mesmo resetar o seu score? (s/n)");
    fflush(stdin);
    scanf("%c", &response);

    if (response == 'S' || response == 's')
    {
        remove(CONF_SCORE_FILE_NAME);
    }

    showMenuInformation();
}

void finishGame(GameScore *gameScore)
{
    char response;

    system("cls");
    saveScore(CONF_SCORE_FILE_NAME, gameScore);
    printf("\nParabéns! Você finalizou o jogo!");
    printf("\n\nQuer jogar novamente? (s/n)");
    fflush(stdin);
    scanf("%c", &response);

    if (response == 'S' || response == 's')
    {
        startGame();
        return;
    }

    showMenuInformation();
}
