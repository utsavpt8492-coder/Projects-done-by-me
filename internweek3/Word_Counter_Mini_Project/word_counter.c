#include <stdio.h>
#include <ctype.h>

int main() {
    char str[1000];
    char *ptr;
    int words = 0;
    int inWord = 0;

    printf("Enter a sentence:\n");
    fgets(str, sizeof(str), stdin);

    ptr = str;

    while (*ptr != '\0') {

        if (isspace((unsigned char)*ptr)) {
            inWord = 0;
        }
        else {
            if (inWord == 0) {
                words++;
                inWord = 1;
            }
        }

        ptr++;
    }

    printf("\nTotal number of words: %d\n", words);

    return 0;
}