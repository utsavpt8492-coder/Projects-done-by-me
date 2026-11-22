#include <stdio.h>
#include <string.h>

struct Student {
    char name[100];
    int age;
    float marks;
};

int main() {
    struct Student s1, s2;
    FILE *fp;

    printf("Enter student name: ");
    fgets(s1.name, sizeof(s1.name), stdin);

    s1.name[strcspn(s1.name, "\n")] = '\0';

    printf("Enter age: ");
    scanf("%d", &s1.age);

    printf("Enter marks: ");
    scanf("%f", &s1.marks);

    fp = fopen("student.dat", "wb");

    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    fwrite(&s1, sizeof(s1), 1, fp);
    fclose(fp);

    printf("\nStudent data saved successfully.\n");

    fp = fopen("student.dat", "rb");

    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    if (fread(&s2, sizeof(s2), 1, fp) != 1) {
        printf("Error reading file.\n");
        fclose(fp);
        return 1;
    }

    fclose(fp);

    printf("\n--- Data Read From File ---\n");

    printf("Name: %s\n", s2.name);
    printf("Age: %d\n", s2.age);
    printf("Marks: %.2f\n", s2.marks);

    return 0;
}