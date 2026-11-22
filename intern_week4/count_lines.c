#include <stdio.h>

int main() {
    FILE *fp;
    int ch;
    int lines = 0;
    int last = '\n';

    fp = fopen("sample.txt", "r");

    if (fp == NULL) {
        printf("File not found.\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            lines++;
        }

        last = ch;
    }

    if (last != '\n') {
        lines++;
    }

    fclose(fp);

    printf("Total number of lines: %d\n", lines);

    return 0;