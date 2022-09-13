/** Descriptive File Name
 * File: part0.c
 * Author: Reuben Chavez (rtchavez@ucsc.edu)
 * 
 * Created: March 29, 2022
 */

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//Class specific libraries
#include "BOARD.h"


// User libraries
#include <stdio.h>
#include <stdlib.h>


/*
 * Function: Creates  Two  2x2 Tables containing the conversions of
 *           Fahrenheit to Celsius and Kelvin to Fahrenheit 
 * Parameters: void
 * Return: 0 when successfully completed 
 */

int main(void) {
    BOARD_Init();
    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/

    //Declare Variables
    float fahr, celsius;
    int lower, upper, step;

    //Initialize Variables
    lower = 0; //lower limit of temperature
    upper = 300; // upper limit
    step = 20; // step size
    fahr = lower;

    //Print Column Header for Farh to Cel
    printf("      F   C\n");

    //Print out Scale
    while (fahr <= upper) {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%7.1f\t%04.0f\n", (double) fahr, (double) celsius);
        fahr = fahr + step;
    }

    printf("\n");

    //      Creating Kelvin to Fahrenheit Table      //

    //Declare Variables
    float kelvin;

    //Re-Initialize Variables
    kelvin = lower;

    //Print Column Header for Kel to Fahr
    printf("    K      F\n");
    //Print out Scale
    while (kelvin <= upper) {
        fahr = (kelvin - 273.15)*1.8 + 32.0;
        printf("%3.3f  %5f\n", (double) kelvin, (double) fahr);
        kelvin = kelvin + step;
    }



    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks.
     **************************************************************************************************/

    // Returning from main() is bad form in embedded environments. So we sit and spin.
    while (1);
}
