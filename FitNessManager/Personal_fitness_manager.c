#include <stdio.h>

#define MAX_DAYS 30

// Structure for storing daily fitness data
struct FitnessRecord {
    int steps;
    int exerciseMinutes;
    float calories;
};

// Function to enter fitness records
void enterRecords(struct FitnessRecord f[], int n) {

    for (int i = 0; i < n; i++) {

        printf("\nEnter details for Day %d\n", i + 1);

        printf("Enter steps: ");
        scanf("%d", &f[i].steps);

        printf("Enter exercise minutes: ");
        scanf("%d", &f[i].exerciseMinutes);

        printf("Enter calories burned: ");
        scanf("%f", &f[i].calories);
    }
}

// Function to display fitness records
void displayRecords(struct FitnessRecord f[], int n) {

    printf("\n----- DAILY FITNESS RECORDS -----\n");

    printf("Day\tSteps\tExercise\tCalories\n");

    for (int i = 0; i < n; i++) {

        printf("%d\t%d\t%d\t\t%.2f\n",
               i + 1,
               f[i].steps,
               f[i].exerciseMinutes,
               f[i].calories);
    }
}

// Function to calculate averages
void calculateAverages(struct FitnessRecord f[], int n) {

    int totalSteps = 0;
    int totalExercise = 0;
    float totalCalories = 0;

    for (int i = 0; i < n; i++) {

        totalSteps += f[i].steps;

        totalExercise += f[i].exerciseMinutes;

        totalCalories += f[i].calories;
    }

    printf("\n----- FITNESS ANALYSIS -----\n");

    printf("Average Steps: %.2f\n",
           (float)totalSteps / n);

    printf("Average Exercise Minutes: %.2f\n",
           (float)totalExercise / n);

    printf("Average Calories Burned: %.2f\n",
           totalCalories / n);
}

// Function to find most active day
void mostActiveDay(struct FitnessRecord f[], int n) {

    int maxIndex = 0;

    for (int i = 1; i < n; i++) {

        if (f[i].steps > f[maxIndex].steps ||
            (f[i].steps == f[maxIndex].steps &&
             f[i].exerciseMinutes >
             f[maxIndex].exerciseMinutes) ||
            (f[i].steps == f[maxIndex].steps &&
             f[i].exerciseMinutes ==
             f[maxIndex].exerciseMinutes &&
             f[i].calories > f[maxIndex].calories)) {

            maxIndex = i;
        }
    }

    printf("\n----- MOST ACTIVE DAY -----\n");

    printf("Day: %d\n", maxIndex + 1);

    printf("Steps: %d\n", f[maxIndex].steps);

    printf("Exercise Minutes: %d\n",
           f[maxIndex].exerciseMinutes);

    printf("Calories Burned: %.2f\n",
           f[maxIndex].calories);
}

// Function to update a record
void updateRecord(struct FitnessRecord f[], int n) {

    int day;

    printf("Enter day number to update: ");
    scanf("%d", &day);

    if (day < 1 || day > n) {

        printf("Invalid day number!\n");
        return;
    }

    printf("Enter new steps: ");
    scanf("%d", &f[day - 1].steps);

    printf("Enter new exercise minutes: ");
    scanf("%d", &f[day - 1].exerciseMinutes);

    printf("Enter new calories burned: ");
    scanf("%f", &f[day - 1].calories);

    printf("Record updated successfully!\n");
}

// Main function
int main() {

    struct FitnessRecord fitness[MAX_DAYS];

    int n, choice;

    printf("====================================\n");
    printf("   PERSONAL FITNESS RECORD MANAGER\n");
    printf("====================================\n");

    printf("\nEnter number of days (1-30): ");
    scanf("%d", &n);

    if (n < 1 || n > MAX_DAYS) {

        printf("Invalid number of days!\n");
        return 1;
    }

    enterRecords(fitness, n);

    do {

        printf("\n========== MAIN MENU ==========\n");

        printf("1. Display Fitness Records\n");
        printf("2. Calculate Fitness Averages\n");
        printf("3. Find Most Active Day\n");
        printf("4. Update Fitness Record\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                displayRecords(fitness, n);
                break;

            case 2:
                calculateAverages(fitness, n);
                break;

            case 3:
                mostActiveDay(fitness, n);
                break;

            case 4:
                updateRecord(fitness, n);
                break;

            case 5:
                printf("\nThank you for using "
                       "Fitness Record Manager!\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}