#include <stdio.h>
#include <stdlib.h>
#define ID_LENGTH 10
#define POZNAMKA_LENGTH 500

int myStrcmp(const char* str1, const char* str2) {
     while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

char *myStrstr(const char *str, const char *substring) {
  const char *a, *b = substring;

  if ( !*b ) return (char *) str;
  for ( ; *str ; str++) {
    if (*str != *b) continue;
    a = str;
    for (;;) {
      if ( !*b ) return (char *) str;
      if (*a++ != *b++) break;
    }
    b = substring;
  }
  return NULL;
}

void v(FILE** data, FILE** parse, FILE** string, char*** dataArray, char*** parseArray, char*** stringArray, int* countOfLines) {
    int input, hodnota1;
    float hodnota2;
    char poznamka[POZNAMKA_LENGTH];
    char id_string[ID_LENGTH];
    int i;
    
    scanf("%d", &input);
    switch (input) {
    case 1:
        if (*data == NULL) *data = fopen("data.txt", "r");
        if (*parse == NULL) *parse = fopen("parse.txt", "r");
        if (*string == NULL) *string = fopen("string.txt", "r");

        rewind(*string);
        rewind(*data);
        rewind(*parse);

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

        if (*dataArray == NULL || *parseArray == NULL || *stringArray == NULL) {
            printf("V2: Nenaplnene polia.\n");
            return;
        }

        for (i = 0; i < *countOfLines; i++) {
            sscanf((*stringArray)[i], "%s", id_string);
            sscanf((*dataArray)[i], "%*d %*d %d %f", &hodnota1, &hodnota2);
            sscanf((*parseArray)[i], "%[^\n]", poznamka);

            printf("ID. mer. modulu: %s\n", id_string);
            printf("Hodnota 1: %d\n", hodnota1);
            printf("Hodnota 2: %g\n", hodnota2);
            printf("Poznamka: %s\n", poznamka);

            printf("\n");
        }
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

void q(char*** dataArray, char*** parseArray, char*** stringArray, int* countOfLines) {
    int Y, i, hodnota1, hodnota2, hodnota3;
    float hodnota4;
    char poznamka[POZNAMKA_LENGTH];
    char id_string[ID_LENGTH];

    if (*dataArray == NULL || *parseArray == NULL || *stringArray == NULL) {
        printf("Q: Polia nie su vytvorene.\n");
        return;
    }

    scanf("%d", &Y);
    scanf("%s", id_string);
    scanf("%d %d %d %f", &hodnota1, &hodnota2, &hodnota3, &hodnota4);

    scanf(" %[^\n]", poznamka);


    if (Y > *countOfLines) {
        Y = *countOfLines;
    } else {
        Y--;
    }


    *dataArray = realloc(*dataArray, (*countOfLines + 1) * sizeof(char*));
    *parseArray = realloc(*parseArray, (*countOfLines + 1) * sizeof(char*));
    *stringArray = realloc(*stringArray, (*countOfLines + 1) * sizeof(char*));

    for (i = *countOfLines; i >= Y; i--) {
        (*dataArray)[i] = (*dataArray)[i - 1];
        (*parseArray)[i] = (*parseArray)[i - 1];
        (*stringArray)[i] = (*stringArray)[i - 1];
    }

    (*dataArray)[Y] = malloc(POZNAMKA_LENGTH * sizeof(char));
    (*parseArray)[Y] = malloc(POZNAMKA_LENGTH * sizeof(char));
    (*stringArray)[Y] = malloc(ID_LENGTH * sizeof(char));

    sprintf((*stringArray)[Y], "%s", id_string);
    sprintf((*dataArray)[Y], "%d %d %d %f", hodnota1, hodnota2, hodnota3, hodnota4);
    sprintf((*parseArray)[Y], "%s", poznamka);

    (*countOfLines)++;
}

void w(char*** dataArray, char*** parseArray, char*** stringArray, int* countOfLines) {
    char idForDelete[ID_LENGTH];
    int i, j, deleteCount = 0;

    if (*dataArray == NULL || *parseArray == NULL || *stringArray == NULL) {
        printf("W: Polia nie su vytvorene.\n");
        return;
    }
    scanf("%s", idForDelete);
    
    /* Odstránenie znaku nového riadku z `idForDelete`, ak existuje, aby sa zabránilo problémom pri porovnávaní */
    for (i = 0; idForDelete[i] != '\0'; i++) {
        if (idForDelete[i] == '\n') {
            idForDelete[i] = '\0';
            break;
        }
    }

    for (i = 0; i < *countOfLines;) {
        
        /* Odstránenie znaku nového riadku z `stringArray[i]`, ak existuje, aby sa zabránilo problémom pri porovnávaní */
        for (j = 0; (*stringArray)[i][j] != '\0'; j++) {
            if ((*stringArray)[i][j] == '\n') {
                (*stringArray)[i][j] = '\0';
                break;
            }
        }

        if (myStrcmp((*stringArray)[i], idForDelete) == 0) {
            free((*dataArray)[i]);
            free((*parseArray)[i]);
            free((*stringArray)[i]);
            deleteCount++;

            for (j = i; j < *countOfLines - 1; j++) {
                (*dataArray)[j] = (*dataArray)[j + 1];
                (*parseArray)[j] = (*parseArray)[j + 1];
                (*stringArray)[j] = (*stringArray)[j + 1];
            }

            (*countOfLines)--;
        } else {
            i++;
        }
    }

    *dataArray = realloc(*dataArray, (*countOfLines) * sizeof(char*));
    *parseArray = realloc(*parseArray, (*countOfLines) * sizeof(char*));
    *stringArray = realloc(*stringArray, (*countOfLines) * sizeof(char*));

    printf("W: Vymazalo sa : %d zaznamov !\n", deleteCount);
}

void e(char ***dataArray, char ***parseArray, char ***stringArray, int* countOfLines) {
    char *line, *p;
    int i;
    char temp[POZNAMKA_LENGTH];
    if (*dataArray == NULL || *parseArray == NULL || *stringArray == NULL) {
        printf("E: Polia nie su vytvorene.\n");
        return;
    }

    scanf("%s", temp);
    for (i = 0; i < *countOfLines; i++) {
        if (myStrstr((*parseArray)[i], temp) != NULL) {
            line = (*parseArray)[i];
            p = line;

            while (*p != '\0') {
                p++;
            }
            
            if (p != line && *(p - 1) == '\n') {
                printf("%s", line);
            } else {
                printf("%s\n", line);
            }
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
            v(&data, &parse, &string, &dataArray, &parseArray, &stringArray, &countOfLines);
            break;
        case 'k':
            k(data, parse, string, &dataArray, &parseArray, &stringArray, &countOfLines);
            return 0;
        case 'n':
            n(&data, &parse, &string, &dataArray, &parseArray, &stringArray, &countOfLines);
            break;
        case 'q':
            q(&dataArray, &parseArray, &stringArray, &countOfLines);
            break;
        case 'w':
            w(&dataArray, &parseArray, &stringArray, &countOfLines);
            break;
        case 'e':
            e(&dataArray, &parseArray, &stringArray, &countOfLines);
            break; 
        default:
            break;
        }
    }
    return 0;
}