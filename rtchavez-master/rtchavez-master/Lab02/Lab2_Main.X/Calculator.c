// Standard libraries
#include <stdio.h>
#include <math.h>


//User libraries:
#include "BOARD.h"

#ifdef PIC32
// Microchip libraries
#include <xc.h>
#endif

// **** Declare function prototypes ****
double Add(double operand1, double operand2);
double Multiply(double operand, double operand2);
double AbsoluteValue(double operand);
double FahrenheitToCelsius(double operand);
double Tangent(double operand);
//add more prototypes here
double Subtract(double operand1, double operand2);
double Divide(double operand1, double operand2);
double CelsiusToFahrenheit(double operand);
double Average(double operand1, double operand2);
double Round(double operand);

// CalculatorRun : 
//  A simple calculator progrram that asks for user input, and can do the following operations:
//  Multiplication, Division, Addtion, Subtraction, Average, Absloute Value, 
//  Fahrenheit to Celsius, Celsius to Fahernheit, and Tangent
//
// Parameter: void
// Return: void

void CalculatorRun(void) {
    printf("\n\nWelcome to Reuben's calculator program! Compiled at %s %s\n", __DATE__, __TIME__);

    char op; //initializing empty
    char arthmic_chars[] = "*/+-macftr"; // list of acceptable characters

    // Your code here

    // code will run until q is given as user input
    while (op != 'q') {
        // initialized doubles for operands 
        double num1 = 0, num2 = 0, result = 0;
        int acceptable_op = 0; // whether its an acceptable calculator operation
        int unary_op = 0;

        printf("\nEnter a mathematical operator: (*,/,+,-,m,a,c,f,t,r):");

        //get operator
        scanf(" %c", &op);
        // while ( getchar() != '\n');

        // Iterate through list to see that input is unary and /or acceptable
        // input
        // Reference: 
        //  - https://www.tutorialkart.com/c-programming/
        //                  c-check-if-array-contains-specified-element/


        for (int i = 0; i < 10; i++) {
            if (arthmic_chars[i] == op && i < 4) {
                acceptable_op = 1;
                unary_op = 1;
                break;
            } else if (arthmic_chars[i] == op) {
                acceptable_op = 1;
                break;
            }
        }
        // checks if operator is in list
        if (acceptable_op) {

            // Asks for first operand
            printf("\tEnter the first Operand:");
            scanf(" %lf", &num1);
            while (getchar() != '\n');
            // Asks for second operand if given operator in unary
            if (unary_op) {
                printf("\tEnter the second Operand:");
                scanf(" %lf", &num2);
                while (getchar() != '\n');

            }


            // Depending on the given operator it will calculate specified function 
            switch (op) {
                case '*':
                    result = Multiply(num1, num2);
                    printf("\tResult of (%lf * %lf): %lf\n", num1, num2, result);
                    break;
                case '/':
                    if (num2) {
                        result = Divide(num1, num2);
                        printf("\tResult of (%f / %f): %f\n", num1, num2, result);
                        break;
                    }
                    printf("\tDivisible by zero error\n");
                    break;
                case '+':
                    result = Add(num1, num2);
                    printf("\tResult of (%f + %f): %f\n", num1, num2, result);
                    break;
                case '-':
                    printf("\tResult of (%f - %f): %f\n", num1, num2, Subtract(num1, num2));
                    break;
                case 'm':
                    printf("\tResult of Average(%f, %f): %f\n", num1, num2, Average(num1, num2));
                    break;
                case 'a':
                    printf("\tResult of |%f|: %f\n", num1, AbsoluteValue(num1));
                    break;
                case 'c':
                    printf("\tResult of %f ->C: %f\n", num1, FahrenheitToCelsius(num1));
                    break;
                case 'f':
                    printf("\tResult of %f -> F: %f\n", num1, CelsiusToFahrenheit(num1));
                    break;
                case 't':
                    printf("\tResult of tan(%f): %.4f\n", num1, Tangent(num1));
                    break;
                case 'r':
                    printf("\tResult of Round(%f): %f\n", num1, Round(num1));
                    break;
                case 'q':
                    break;
            }
        } else {
            printf("Operator is invalid\n");
        }
    }
    BOARD_End();
    while (1);
}

/********************************************************************************
 * Define the Add function here.
 ********************************************************************************/
double Add(double operand1, double operand2) {
    return operand1 + operand2;
}

/********************************************************************************
 * Define the Subtract function here.
 ********************************************************************************/
double Subtract(double operand1, double operand2) {
    return operand1 - operand2;
}

/********************************************************************************
 * Define the Multiply function here.
 ********************************************************************************/
double Multiply(double operand1, double operand2) {
    return operand1 * operand2;
}

/********************************************************************************
 * Define the Divide function here.
 ********************************************************************************/
double Divide(double operand1, double operand2) {

    return operand1 / operand2;
}

/********************************************************************************
 * Define the Absolute Value function here.
 ********************************************************************************/
double AbsoluteValue(double operand) {
    return operand > 0 ? operand : -operand;
}

/*********************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ********************************************************************************/
double FahrenheitToCelsius(double operand) {
    return (operand - 32) * (5.0 / 9.0);
}

/*********************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ********************************************************************************/
double CelsiusToFahrenheit(double operand) {
    double result = (operand * 9.0 / 5.0) + 32;
    return result;
}

/********************************************************************************
 * Define the Average function here.
 *******************************************************************************/
double Average(double operand1, double operand2) {
    return (operand1 + operand2) / 2;
}

/*********************************************************************************
 * Define the Tangent function that takes input in degrees.
 ********************************************************************************/
double Tangent(double operand) {
    return tan(operand * (M_PI / 180)); // returns tangent in radians
}

/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/
double Round(double operand) {
    return round(operand);
}


