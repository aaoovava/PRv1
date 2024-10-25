#include <stdio.h>
#include <stdlib.h>
#define ID_LENGTH 10
#define POZNAMKA_LENGTH 500

void v(FILE** data, FILE** parse, FILE** string) {
    int input, hodnota1;
    float hodnota2;
    char poznamka[POZNAMKA_LENGTH];
    char id_string[ID_LENGTH];
    
    scanf("%d", &input);
    switch (input) {
    case 1:
        if (*data == NULL) *data = fopen("data.txt", "r");
        if (*parse == NULL) *parse = fopen("parse.txt", "r");
        if (*string == NULL) *string = fopen("string.txt", "r");

        if (*data == NULL || *parse == NULL || *string == NULL) {
            printf("V1: Neotvorene txt subory.\n");
            return;
        }

        while (fscanf(*string, "%s", id_string) == 1) {
            fscanf(*data, "%*d %*d %d %f", &hodnota1, &hodnota2);
            fgets(poznamka, sizeof(poznamka), *parse);

            printf("ID. mer. modulu: %s\n", id_string);
            printf("Hodnota 1: %d\n", hodnota1);
            printf("Hodnota 2: %g\n", hodnota2);
            printf("Poznamka: %s\n", poznamka);
        }
        break;

    case 2:
    /* TODO: V2 */
        break;

    case 3:
    /* TODO: V3 */
        break;
    
    default:
        printf("V: Nespravna volba vypisu.\n");
        break;
    }
}

void h(FILE** string) {
    int fildOfCounts[256] = { 0 };
    char c;
    
    if (*string == NULL) {
        printf("H: Neotvoreny subor.\n");
        return;
    }
    rewind(*string);
    
    while ((c = fgetc(*string)) != EOF) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            fildOfCounts[(unsigned char)c]++;
        }
    }

    for (c = 'A'; c <= 'Z'; c++) {
        if (fildOfCounts[(unsigned char)c] > 0) {
            printf("%c : %d\n", c, fildOfCounts[(unsigned char)c]);
        }
    }

    for (c = 'a'; c <= 'z'; c++) {
        if (fildOfCounts[(unsigned char)c] > 0) {
            printf("%c : %d\n", c, fildOfCounts[(unsigned char)c]);
        }
    }

    for (c = '0'; c <= '9'; c++) {
        if (fildOfCounts[(unsigned char)c] > 0) {
            printf("%c : %d\n", c, fildOfCounts[(unsigned char)c]);
        }
    }
}

void freeArray(char** array, int countOfLines) {
    int i;
    if (array != NULL) {
        for ( i = 0; i < countOfLines; i++) {
            free(array[i]);
        }
        free(array);
    }
}

void n(FILE** data, FILE** parse, FILE** string, char*** dataArray, char*** parseArray, char*** stringArray, int* countOfLines) {
    char temp[POZNAMKA_LENGTH];
    int i;
    
    if (*string == NULL || *data == NULL || *parse == NULL) {
        printf("N: Neotvoreny subor.\n");
        return;
    }
   
    if (*dataArray != NULL) freeArray(*dataArray, *countOfLines);
    if (*parseArray != NULL) freeArray(*parseArray, *countOfLines);
    if (*stringArray != NULL) freeArray(*stringArray, *countOfLines);

    *countOfLines = 0;
    rewind(*data);
    while (fgets(temp, POZNAMKA_LENGTH, *data)) {
        (*countOfLines)++;
    }

    
    *dataArray = (char**)malloc(*countOfLines * sizeof(char*));
    *parseArray = (char**)malloc(*countOfLines * sizeof(char*));
    *stringArray = (char**)malloc(*countOfLines * sizeof(char*));

    for (i = 0; i < *countOfLines; i++) {
        (*dataArray)[i] = (char*)malloc(POZNAMKA_LENGTH * sizeof(char));
        (*parseArray)[i] = (char*)malloc(POZNAMKA_LENGTH * sizeof(char));
        (*stringArray)[i] = (char*)malloc(POZNAMKA_LENGTH * sizeof(char));
    }

    
    rewind(*data);
    rewind(*parse);
    rewind(*string);

    for (i = 0; i < *countOfLines; i++) {
        fgets((*dataArray)[i], POZNAMKA_LENGTH, *data);
        fgets((*parseArray)[i], POZNAMKA_LENGTH, *parse);
        fgets((*stringArray)[i], POZNAMKA_LENGTH, *string);
    }

}

void k(FILE* data, FILE* parse, FILE* string, char*** dataArray, char*** parseArray, char*** stringArray, int* countOfLines) {
    if (data != NULL) fclose(data); 
    if (parse != NULL) fclose(parse);
    if (string != NULL) fclose(string);

    if (*dataArray != NULL) freeArray(*dataArray, *countOfLines);
    if (*parseArray != NULL) freeArray(*parseArray, *countOfLines);
    if (*stringArray != NULL) freeArray(*stringArray, *countOfLines);
}

int main() {
    FILE* data = NULL, * parse = NULL, * string = NULL;
    char commandInput;
    int countOfLines = 0;  

    char** dataArray = NULL;
    char** parseArray = NULL;
    char** stringArray = NULL;

    while (1) {
        scanf("%c", &commandInput); 

        switch (commandInput) {
        case 'h':
            h(&string);
            break;
        case 'v':
            v(&data, &parse, &string);
            break;
        case 'k':
            k(data, parse, string, &dataArray, &parseArray, &stringArray, &countOfLines);
            return 0;
        case 'n':
            n(&data, &parse, &string, &dataArray, &parseArray, &stringArray, &countOfLines);
            break;
        default:
            break;
        }
    }
    return 0;
}