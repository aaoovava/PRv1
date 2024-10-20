#include <stdio.h>
#define ID_LENGTH 10
#define POZNAMKA_LENGTH 500

void v(FILE** data, FILE** parse, FILE** string) {
    int input, hodnota1;
    float hodnota2;
    char poznamka[POZNAMKA_LENGTH];
    char id_string[ID_LENGTH];
    
    scanf("%d", &input);
    while (getchar() != '\n');
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
            printf("Poznámka: %s\n", poznamka);
        }
        break;

    case 2:
    /* TODO: V2 */
        break;

    case 3:
    /* TODO: V3 */
        break;
    
    default:
        printf("V: Nesprávne volba vypisu.\n");
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


void k(FILE* data, FILE* parse, FILE* string) {
    if (data != NULL) fclose(data);
    if (parse != NULL) fclose(parse);
    if (string != NULL) fclose(string);
}

int main() {
    FILE* data = NULL, * parse = NULL, * string = NULL;
    char commandInput;

    while (1) {
        scanf("%c", &commandInput);
        while (getchar() != '\n');

        switch (commandInput) {
        case 'h' :
            h(&string);
            break;
        case 'v':
            v(&data, &parse, &string);
            break;
        case 'k':
            k(data, parse, string);
            return 0;
            break;
        default:
            break;
        }
    }
    return 0;
}