
/** Descriptive File Name
 * File: part0.c
 * Author: Reuben Chavez (rtchavez@ucsc.edu)
 * 
 * Created: March 29, 2022
 */

#include <stdio.h>
#include <stdlib.h>

#include "BOARD.h"

/*
 * This function prints Hello World
 */
int main(void) {
    BOARD_Init();

    printf("Hello World!\n");

    BOARD_End();
    while (1);
}