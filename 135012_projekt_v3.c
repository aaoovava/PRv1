#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ID_LENGTH 10
#define POZNAMKA_LENGTH 500

typedef struct {
    int Hodnota_ID;
    int Hodnota_zn;
    int Hodnota_1;
    float Hodnota_2;
    
}Datarecord;

typedef struct {
    char Poznamka_ID[ID_LENGTH];
    float Poznamka_N1;
    int Poznamka_Hodina;
    int Poznamka_Minuta;
    char Poznamka_T[POZNAMKA_LENGTH];
}Parserecord;

typedef struct {
    char ID[ID_LENGTH];
    Datarecord data;
    Parserecord pars;
    struct Node* next;
}Node;


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

void v(FILE** data, FILE** parse, FILE** string, char*** dataArray, char*** parseArray, char*** stringArray, int* countOfLines, Node **head) {
    int input, hodnota1;
    float hodnota2;
    char poznamka[POZNAMKA_LENGTH];
    char id_string[ID_LENGTH];
    int i;
    Node *current;
    
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
        if (*head == NULL) {
            printf("V3: Nenaplneny spajany zoznam.\n");
            return;
        }
         current = *head;
        while (current != NULL) {
            printf("ID. mer. modulu: %s\n", current->ID);
            printf("Hodnota 1: %d\n", current->data.Hodnota_1);
            printf("Hodnota 2: %g\n", current->data.Hodnota_2);
            printf("Poznamka ID: %s\n", current->pars.Poznamka_ID);
            printf("Poznamka C: %d : %d => %g\n",
                current->pars.
                Poznamka_Hodina,
                current->pars.Poznamka_Minuta,
                current->pars.Poznamka_N1);
            printf("Poznamka T: %s\n", current->pars.Poznamka_T);
            printf("\n");

            current = (Node*)current->next;
    }
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
void freeNode(Node **head) {
    Node *curentNode = *head;
    Node *nextNode;
    if (head != NULL) {
        while (curentNode != NULL)
        {
            nextNode = (Node*)curentNode->next;
            free(curentNode);
            curentNode = nextNode;
        }
        *head = NULL;
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

void m(FILE** data, FILE** parse, FILE** string, Node **head, int* countForNodes) {
    Node *newNode;
    char tempID[ID_LENGTH];
    Datarecord tempData;
    Parserecord tempParse;
    char parseLine[POZNAMKA_LENGTH];
    char *token;

    if (*data == NULL || *parse == NULL || *string == NULL) {
        printf("M: Neotvoreny subor.\n");
        return;
    }

    rewind(*data);
    rewind(*parse);
    rewind(*string);


    if (*head != NULL) freeNode(head);
    
    *countForNodes = 0;
    while (fscanf(*string, "%s", tempID) == 1) {
        fscanf(*data, "%d %d %d %f", &tempData.Hodnota_ID, &tempData.Hodnota_zn, &tempData.Hodnota_1, &tempData.Hodnota_2);

        if (!fgets(parseLine, POZNAMKA_LENGTH, *parse)) {
            break;
        }

        parseLine[strcspn(parseLine, "\n")] = 0;

        token = strtok(parseLine, "#");
        if (token && strlen(token) > 0) {
            strcpy(tempParse.Poznamka_ID, token);
        } else {
            strcpy(tempParse.Poznamka_ID, "NaN");
        }

        token = strtok(NULL, "#");
        if (token && strlen(token) > 0) {
            tempParse.Poznamka_N1 = atof(token);
        } else {
            tempParse.Poznamka_N1 = -1;
        }

        token = strtok(NULL, "#");
        if (token && strlen(token) > 0) {
            tempParse.Poznamka_Hodina = atoi(strndup(token, 2));
            tempParse.Poznamka_Minuta = atoi(token + 2);
        } else {
            tempParse.Poznamka_Hodina = -1;
            tempParse.Poznamka_Minuta = -1;
        }

        token = strtok(NULL, "#");
        if (token && strlen(token) > 0) {
            strcpy(tempParse.Poznamka_T, token);
        } else {
            strcpy(tempParse.Poznamka_T, "NaN");
        }

        newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL) {
            printf("M: Chyba alokácie pamäte.\n");
            return;
        }
        
        strcpy(newNode->ID, tempID);
        newNode->data = tempData;
        newNode->pars = tempParse;
        newNode->next = NULL;

        if (*head == NULL) {
            *head = newNode;
        } else {
            Node* current = *head;
            while (current->next != NULL) {
                current = (Node*)current->next;
            }
            current->next = (struct Node*)newNode;
        }

        (*countForNodes)++;
    }
    printf("M: Nacitalo sa %d zaznamov.\n", *countForNodes);
}

void a(Node **head, int *countForNodes) {
    int position;
    char tempID[ID_LENGTH];
    Datarecord tempData;
    Parserecord tempParse;
    char parseLine[POZNAMKA_LENGTH];
    char *token;
    Node *newNode, *currentNode;

    scanf("%d", &position);

    scanf("%s", tempID); 
    scanf("%d %d %d %f", &tempData.Hodnota_ID, &tempData.Hodnota_zn, &tempData.Hodnota_1, &tempData.Hodnota_2); 
    scanf(" %[^\n]", parseLine);

    parseLine[strcspn(parseLine, "\n")] = 0;
    token = strtok(parseLine, "#");
    if (token && strlen(token) > 0) {
        strcpy(tempParse.Poznamka_ID, token);
    } else {
        strcpy(tempParse.Poznamka_ID, "NaN");
    }

    token = strtok(NULL, "#");
    if (token && strlen(token) > 0) {
        tempParse.Poznamka_N1 = atof(token);
    } else {
        tempParse.Poznamka_N1 = -1;
    }

    token = strtok(NULL, "#");
    if (token && strlen(token) > 0) {
        tempParse.Poznamka_Hodina = atoi(strndup(token, 2));
        tempParse.Poznamka_Minuta = atoi(token + 2);
    } else {
        tempParse.Poznamka_Hodina = -1;
        tempParse.Poznamka_Minuta = -1;
    }

    token = strtok(NULL, "#");
    if (token && strlen(token) > 0) {
        strcpy(tempParse.Poznamka_T, token);
    } else {
        strcpy(tempParse.Poznamka_T, "NaN");
    }

    newNode = (Node *)malloc(sizeof(Node));

    strcpy(newNode->ID, tempID);
    newNode->data = tempData;
    newNode->pars = tempParse;
    newNode->next = NULL;


    if (*head == NULL || position <= 1) {
        newNode->next = (struct Node*)*head;
        *head = newNode;
    } else if (position > *countForNodes) {
        currentNode = *head;
        while (currentNode->next != NULL) {
            currentNode = (Node*)currentNode->next;
        }
        currentNode->next = (struct Node*)newNode;
    } else {
        int index = 1;
        currentNode = *head;
        while (currentNode->next != NULL && index < position - 1) {
            currentNode = (Node*)currentNode->next;
            index++;
        }
        newNode->next = currentNode->next;
        currentNode->next = (struct Node*)newNode;
    }
    (*countForNodes)++;
}

void s (Node **head, int *countForNodes) {
    char idToDelete[ID_LENGTH];
    int deleteCount = 0;
    Node *currentNode = *head, *prevNode = NULL, *tempNode;
    if (*head == NULL) {
        printf("S: Spajany zoznam nie je vytvorený.\n");
        return;
    }

    scanf("%s", idToDelete);

    while (currentNode != NULL && strcmp(currentNode->ID, idToDelete) == 0) {
        tempNode = currentNode;
        currentNode = (Node*)currentNode->next;
        free(tempNode);
        deleteCount++;
    }

    *head = currentNode;

    while (currentNode != NULL) {
        while (currentNode != NULL && strcmp(currentNode->ID, idToDelete) != 0) {
            prevNode = currentNode;
            currentNode = (Node*)currentNode->next;
        }

        if (currentNode == NULL) break;

        prevNode->next = currentNode->next;
        free(currentNode);
        currentNode = (Node*)prevNode->next;
        deleteCount++;
    }

    (*countForNodes) -= deleteCount;

    printf("S: Vymazalo sa : %d zaznamov !\n", deleteCount);
} 

void d(Node **head, int *countForNodes) {
    int c1, c2, i, temp;
    Node *prevNodeC1 = NULL, *prevNodeC2 = NULL;
    Node *currentNodeC1 = *head, *currentNodeC2 = *head;
    Node *tempNode;

    scanf("%d %d", &c1, &c2);

    if (c1 <= 0 || c2 <= 0 || c1 > *countForNodes || c2 > *countForNodes || c1 == c2) {
        return;
    }

    if (c1 > c2) {
        temp = c1;
        c1 = c2;
        c2 = temp;
    }

    for (i = 1; i < c1; i++) {
        prevNodeC1 = currentNodeC1;
        currentNodeC1 = (Node*)currentNodeC1->next;
    }

    for (i = 1; i < c2; i++) {
        prevNodeC2 = currentNodeC2;
        currentNodeC2 = (Node*)currentNodeC2->next;
    }

    if (prevNodeC1 != NULL) {
        prevNodeC1->next = (struct Node*)currentNodeC2;
    } else {
        *head = currentNodeC2;
    }

    if (prevNodeC2 != NULL) {
        prevNodeC2->next = (struct Node*)currentNodeC1;
    } else {
        *head = currentNodeC1;
    }

    tempNode = (Node*)currentNodeC1->next;
    currentNodeC1->next = currentNodeC2->next;
    currentNodeC2->next = (struct Node*)tempNode;
}
void k(FILE* data, FILE* parse, FILE* string, char*** dataArray, char*** parseArray, char*** stringArray, int* countOfLines, Node **head) {
    if (data != NULL) fclose(data); 
    if (parse != NULL) fclose(parse);
    if (string != NULL) fclose(string);

    if (*dataArray != NULL) freeArray(*dataArray, *countOfLines);
    if (*parseArray != NULL) freeArray(*parseArray, *countOfLines);
    if (*stringArray != NULL) freeArray(*stringArray, *countOfLines);

    if (*head != NULL) freeNode(head);
}

int main(void) {
    FILE* data = NULL, * parse = NULL, * string = NULL;
    char commandInput;
    int countOfLines = 0;
    int countForNodes = 0;  

    char** dataArray = NULL;
    char** parseArray = NULL;
    char** stringArray = NULL;
    Node *head = NULL;

    while (1) {
        scanf("%c", &commandInput); 

        switch (commandInput) {
        case 'h':
            h(&string);
            break;
        case 'v':
            v(&data, &parse, &string, &dataArray, &parseArray, &stringArray, &countOfLines, &head);
            break;
        case 'k':
            k(data, parse, string, &dataArray, &parseArray, &stringArray, &countOfLines, &head);
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
        case 'm':
            m(&data, &parse, &string, &head, &countForNodes);
            break;
        case 'a':
            a(&head, &countForNodes);
            break;    
        case 's':
            s(&head, &countForNodes);
            break;
        case 'd':
            d(&head, &countForNodes);
            break;    
        default:
            break;
        }
    }
    return 0;
}
