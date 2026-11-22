#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int id;
    char name[60];
    char department[40];
    float salary;
};

void addEmployee() {
    struct Employee e, old;
    FILE *fp;

    printf("Enter Employee ID: ");
    if (scanf("%d", &e.id) != 1)
        return;

    fp = fopen("employees.dat", "rb");

    if (fp != NULL) {
        while (fread(&old, sizeof(old), 1, fp) == 1) {
            if (old.id == e.id) {
                printf("Employee ID already exists!\n");
                fclose(fp);
                return;
            }
        }
        fclose(fp);
    }

    printf("Enter Name: ");
    scanf(" %59[^\n]", e.name);

    printf("Enter Department: ");
    scanf(" %39[^\n]", e.department);

    printf("Enter Salary: ");
    scanf("%f", &e.salary);

    fp = fopen("employees.dat", "ab");

    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fwrite(&e, sizeof(e), 1, fp);
    fclose(fp);

    printf("Employee added successfully!\n");
}

void displayEmployees() {
    struct Employee e;
    FILE *fp;

    fp = fopen("employees.dat", "rb");

    if (fp == NULL) {
        printf("No employee records found.\n");
        return;
    }

    printf("\n--- Employee Records ---\n");

    while (fread(&e, sizeof(e), 1, fp) == 1) {
        printf("\nEmployee ID: %d\n", e.id);
        printf("Name: %s\n", e.name);
        printf("Department: %s\n", e.department);
        printf("Salary: %.2f\n", e.salary);
    }

    fclose(fp);
}

void searchEmployee() {
    struct Employee e;
    FILE *fp;
    int id, found = 0;

    printf("Enter Employee ID to search: ");
    scanf("%d", &id);

    fp = fopen("employees.dat", "rb");

    if (fp == NULL) {
        printf("No employee records found.\n");
        return;
    }

    while (fread(&e, sizeof(e), 1, fp) == 1) {
        if (e.id == id) {
            printf("\nEmployee Found!\n");
            printf("ID: %d\n", e.id);
            printf("Name: %s\n", e.name);
            printf("Department: %s\n", e.department);
            printf("Salary: %.2f\n", e.salary);

            found = 1;
            break;
        }
    }

    if (found == 0) {
        printf("Employee not found.\n");
    }

    fclose(fp);
}

void updateEmployee() {
    struct Employee e;
    FILE *fp;
    int id, found = 0;

    printf("Enter Employee ID to update: ");
    scanf("%d", &id);

    fp = fopen("employees.dat", "rb+");

    if (fp == NULL) {
        printf("File not found.\n");
        return;
    }

    while (fread(&e, sizeof(e), 1, fp) == 1) {
        if (e.id == id) {
            printf("Enter New Name: ");
            scanf(" %59[^\n]", e.name);

            printf("Enter New Department: ");
            scanf(" %39[^\n]", e.department);

            printf("Enter New Salary: ");
            scanf("%f", &e.salary);

            fseek(fp, -(long)sizeof(e), SEEK_CUR);

            fwrite(&e, sizeof(e), 1, fp);

            found = 1;

            printf("Employee updated successfully!\n");
            break;
        }
    }

    if (found == 0) {
        printf("Employee not found.\n");
    }

    fclose(fp);
}

void deleteEmployee() {
    struct Employee e;
    FILE *fp, *temp;
    int id, found = 0;

    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);

    fp = fopen("employees.dat", "rb");

    if (fp == NULL) {
        printf("File not found.\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    if (temp == NULL) {
        fclose(fp);
        printf("Error creating temporary file.\n");
        return;
    }

    while (fread(&e, sizeof(e), 1, fp) == 1) {
        if (e.id == id) {
            found = 1;
        } else {
            fwrite(&e, sizeof(e), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (found == 0) {
        remove("temp.dat");
        printf("Employee not found.\n");
        return;
    }

    remove("employees.dat");
    rename("temp.dat", "employees.dat");

    printf("Employee deleted successfully!\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n===== EMPLOYEE MANAGEMENT SYSTEM =====\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee\n");
        printf("4. Update Employee\n");
        printf("5. Delete Employee\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            break;
        }

        switch (choice) {
            case 1:
                addEmployee();
                break;

            case 2:
                displayEmployees();
                break;

            case 3:
                searchEmployee();
                break;

            case 4:
                updateEmployee();
                break;

            case 5:
                deleteEmployee();
                break;

            case 6:
                printf("Thank you!\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;