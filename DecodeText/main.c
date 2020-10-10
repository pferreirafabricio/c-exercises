#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#define DEFAULT_CHAR_ARRAY_SIZE 5
#define MAX_FILE_NAME_CHARACTERS 50
#define MAX_NUMBER_OF_CHARACTERS 100

void codifyCharacter(char *character)
{
    switch (*character)
    {
        case 'a':
            *character = 'Z';
            break;
        case 'e':
            *character = 'Y';
            break;
        case 'i':
            *character = 'X';
            break;
        case 'o':
            character = 'W';
            break;
        case 'u':
            *character = '*';
            break;
        default:
            break;
    }
}

void createNewFile(char fileNameToRead[MAX_FILE_NAME_CHARACTERS], char fileNameToCreate[MAX_FILE_NAME_CHARACTERS])
{
    // Read
    FILE *fileToBeRead;
    FILE *fileToWrite;
    char characterReaded;

    fileToBeRead = fopen(fileNameToRead, "r");
    fileToWrite = fopen(fileNameToCreate, "w");

    if (fileToBeRead == NULL)
    {
        printf("\n\nAn error occurs opening the file %s!", fileNameToRead);
        return;
    }

    if (fileToWrite == NULL)
    {
        printf("\n\nAn error occurs opening the file %s!", fileNameToCreate);
        return;
    }

    characterReaded = fgetc(fileToBeRead);
    while(characterReaded != EOF)
    {
        codifyCharacter(&characterReaded);
        fputc(characterReaded, fileToWrite);
        characterReaded = fgetc(fileToBeRead);
    }

    if(fclose(fileToBeRead) != 0)
    {
        printf("\n\nSomething was wrong on closing the file %s!", fileNameToRead);
    }

    if(fclose(fileToWrite) != 0)
    {
        printf("\n\nSomething was wrong on closing the file %s!", fileNameToCreate);
    }
}

void readFile(char fileName[MAX_FILE_NAME_CHARACTERS])
{
    FILE *fileToBeRead;
    char characterReaded;

    // char chainOfCharacters[MAX_NUMBER_OF_CHARACTERS];

    fileToBeRead = fopen(fileName, "r");

    if (fileToBeRead == NULL)
    {
        printf("\n\nAn error occurs opening the file %s!", fileName);
        return;
    }

    characterReaded = fgetc(fileToBeRead);
    while (characterReaded != EOF)
    {
        printf("%c", characterReaded);
        characterReaded = fgetc(fileToBeRead);
    }

    if(fclose(fileToBeRead) != 0)
    {
        printf("\n\nSomething was wrong on closing the file %s!", fileName);
    }
}

int main()
{
    createNewFile("text.txt", "decoded.txt");

    printf("\n\nAll operations are finished with success!\n\n");
    return 0;
}
