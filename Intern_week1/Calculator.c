#include <stdio.h>

int main() {
    char operator;
    double num1, num2, result;

    // Ask the user for the operation they want to perform
    printf("Enter an operator (+, -, *, /): ");
    scanf("%c", &operator);

    // Ask the user for the two numbers
    printf("Enter two numbers: ");
    scanf("%lf %lf", &num1, &num2);

    // Perform the calculation based on the chosen operator
    switch (operator) {
        case '+':
            result = num1 + num2;
            printf("%.2lf + %.2lf = %.2lf\n", num1, num2, result);
            break;
            
        case '-':
            result = num1 - num2;
            printf("%.2lf - %.2lf = %.2lf\n", num1, num2, result);
            break;
            
        case '*':
            result = num1 * num2;
            printf("%.2lf * %.2lf = %.2lf\n", num1, num2, result);
            break;
            
        case '/':
            // Prevent the program from crashing if the user tries to divide by zero
            if (num2 != 0.0) {
                result = num1 / num2;
                printf("%.2lf / %.2lf = %.2lf\n", num1, num2, result);
            } else {
                printf("Error! Division by zero is not allowed.\n");
            }
            break;
            
        default:
            // Handle cases where the user types a symbol other than +, -, *, /
            printf("Error! Invalid operator.\n");
    }

    return 0;
}