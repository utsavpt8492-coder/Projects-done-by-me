#include <stdio.h>
#include <string.h>

int main() {
    char str[100], temp;
    char *start, *end;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    str[strcspn(str, "\n")] = '\0';

    start = str;
    end = str + strlen(str);

    if (start < end) {
        end--;
    }

    while (start < end) {
        temp = *start;
        *start = *end;
        *end = temp;

        start++;
        end--;
    }

    printf("Reversed string: %s\n", str);

    return 0;
}