#include <stdio.h>
#define ID_LENGTH 10
#define POZNAMKA_LENGTH 500

void v(FILE** data, FILE** parse, FILE** string) {
    int input, hodnota1;
    float hodnota2;
    char poznamka[POZNAMKA_LENGTH];
    char id_string[ID_LENGTH];
    
    scanf("%d", &input);
    switch (input)
    {
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
            printf("Hodnota 2: %.4f\n", hodnota2);
            printf("Poznámka: %s\n\n", poznamka);
        }
        break;
    
    default:
        break;
    }
}

void k(FILE* data, FILE* parse, FILE* string) {
    printf("close\n");
    if (data != NULL) fclose(data);
    if (parse != NULL) fclose(parse);
    if (string != NULL) fclose(string);
}

int main() {
    FILE* data = NULL, * parse = NULL, * string = NULL;
    char comandInput;

    while (1) {
        scanf("%c", &comandInput);
        while (getchar() != '\n');    

        switch (comandInput)
        {
        case 'v':
            v(&data, &parse, &string);
            break;
        case 'k':
            k(data, parse, string);
            return 0;
            break;
        default:
            printf("Nespravny vstup.\n");
            break;
        }
    }

    return 0;
}