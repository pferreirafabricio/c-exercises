#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_ARRAY_SIZE 51
#define USABLE_ARRAY_SIZE 50
#define MAX_NUMBER_OF_CHARACTERS 100

void readFile(char fileNameToBeRead[DEFAULT_ARRAY_SIZE], char fileNameToWrite[DEFAULT_ARRAY_SIZE])
{
    // Read
    FILE *fileToBeRead;
    FILE *fileToWrite;
    fileToBeRead = fopen(fileNameToBeRead, "r");
    fileToWrite = fopen(fileNameToWrite, "w");

    char chainOfCharacters[MAX_NUMBER_OF_CHARACTERS];
    int currentLine = 0;

    if (fileToBeRead == NULL)
    {
        printf("\n\nAn error occurs opening the file %s!", fileNameToBeRead);
        return;
    }

    if (fileToWrite == NULL)
    {
        printf("\n\nAn error occurs opening the file %s!", fileNameToWrite);
        return;
    }

    while(!feof(fileToBeRead))
    {
        fgets(chainOfCharacters, MAX_NUMBER_OF_CHARACTERS, fileToBeRead);
        fputs(chainOfCharacters, fileToWrite);
        currentLine++;

        if (currentLine == 3)
        {
            printf("\n\nType a phrase to be inserted in line 3: ");
            fgets(chainOfCharacters, MAX_NUMBER_OF_CHARACTERS - 1, stdin);
            fputs(chainOfCharacters, fileToWrite);
        }
    }

    if(fclose(fileToBeRead) != 0)
    {
        printf("\n\nSomething was wrong on closing the file %s!", fileNameToBeRead);
    }

    if(fclose(fileToWrite) != 0)
    {
        printf("\n\nSomething was wrong on closing the file %s!", fileNameToWrite);
    }
}

void outputFiles(char fileNameText[DEFAULT_ARRAY_SIZE], char fileNameWrite[DEFAULT_ARRAY_SIZE])
{
    // Read
    FILE *fileOutputText;
    FILE *fileOutputWrite;
    fileOutputText = fopen(fileNameText, "r");
    fileOutputWrite = fopen(fileNameWrite, "r");

    char chainTextCharacters[MAX_NUMBER_OF_CHARACTERS];
    char chainWritedCharacters[MAX_NUMBER_OF_CHARACTERS];

    if (fileOutputText == NULL)
    {
        printf("\n\nAn error occurs opening the file %s!", fileNameText);
        return;
    }

    if (fileOutputWrite == NULL)
    {
        printf("\n\nAn error occurs opening the file %s!", fileNameWrite);
        return;
    }

    printf("\n\n=== Printing the previous file: ===\n");
    while(!feof(fileOutputText))
    {
        fgets(chainTextCharacters, MAX_NUMBER_OF_CHARACTERS, fileOutputText);
        printf("%s", chainTextCharacters);
    }

    printf("\n\n=== Printing the writed file: ===\n");
    while(!feof(fileOutputWrite))
    {
        fgets(chainWritedCharacters, MAX_NUMBER_OF_CHARACTERS, fileOutputWrite);
        printf("%s", chainWritedCharacters);
    }

    if(fclose(fileOutputText) != 0)
    {
        printf("\n\nSomething was wrong on closing the file %s!", fileNameText);
    }

    if(fclose(fileOutputWrite) != 0)
    {
        printf("\n\nSomething was wrong on closing the file %s!", fileNameWrite);
    }
}

int main()
{
    readFile("text.txt", "write.txt");
    outputFiles("text.txt", "write.txt");

    printf("\n\n\n------- All operations are finished with success! ------\n\n");

    return 0;
}
