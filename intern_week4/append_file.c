#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp;
    char text[500];

    printf("Enter text to append: ");
    fgets(text, sizeof(text), stdin);

    text[strcspn(text, "\n")] = '\0';

    fp = fopen("sample.txt", "a");

    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    fprintf(fp, "%s\n", text);

    fclose(fp);

    printf("Data appended successfully.\n");

    return 0;
}