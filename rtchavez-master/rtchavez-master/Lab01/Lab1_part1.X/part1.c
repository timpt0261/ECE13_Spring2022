/** Descriptive File Name
 * File: part0.c
 * Author: Reuben Chavez (rtchavez@ucsc.edu)
 * 
 * Created: March 29, 2022
 */

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <stdlib.h>

//Class specific libraries
#include "BOARD.h"


// User libraries
#include <math.h>

/*
 * Function: creates random numbers and organizes them with a sorting algorithm
 * Parameters: void
 * Return: 0 when successfully completed 
 */

int main(void) {
    BOARD_Init();
    unsigned char vals[] = {rand(), rand(), rand(), rand(), rand()};
    int valsToBeSorted[] = {vals[0], vals[1], vals[2], vals[3], vals[4]};

    // Sort the array in place.
    
    /*
      Trial 1:
        valsTobeStored[0]  value: 50
        valsTobeStored[1]  value: 152
        valsTobeStored[2]  value: 130
        valsTobeStored[3]  value: 148
        valsTobeStored[4]  value: 178

    Trial 2:
        valsTobeStored[0]  value: 50
        valsTobeStored[1]  value: 152
        valsTobeStored[2]  value: 130
        valsTobeStored[3]  value: 148
        valsTobeStored[4]  value: 178

    Trial 3:
        valsTobeStored[0]  value: 50
        valsTobeStored[1]  value: 152
        valsTobeStored[2]  value: 130
        valsTobeStored[3]  value: 148
        valsTobeStored[4]  value: 178
     
     Trial 4:
        valsTobeStored[0]  value: 50
        valsTobeStored[1]  value: 152
        valsTobeStored[2]  value: 130
        valsTobeStored[3]  value: 148
        valsTobeStored[4]  value: 178

    Trial 5:
        valsTobeStored[0]  value: 50
        valsTobeStored[1]  value: 130
        valsTobeStored[2]  value: 148
        valsTobeStored[3]  value: 152
        valsTobeStored[4]  value: 178
     */


    int i, j; //Initialize int i and j
    
    //for length of the list of vals
    for (i = 0; i < 5; i++) {
        //initialize temp value to current val
        int aTemp = valsToBeSorted[i];
        //for 
        for (j = i - 1; j >= 0; j--) {
            if (valsToBeSorted[j] <= aTemp)
                break;
            valsToBeSorted[j + 1] = valsToBeSorted[j];
        }
        valsToBeSorted [j + 1] = aTemp;
    }

    // Print out the array
    printf("[");
    for (i = 0; i < 4; i++) {
        printf("%d, ", valsToBeSorted[i]);
    }
    printf("%d]\n", valsToBeSorted[i]);

    /*
     * Returning from main() is bad form in embedded environments. So we
     * sit and spin.
     */
    while (1);
}