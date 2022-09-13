// Leo Lin
// 05/26/2022
// Spring 2022

#include "Field.h"
#include "BOARD.h"
#include <stdlib.h>
#include <stdio.h>

static Field ownmap;
static Field oppmap;
static GuessData guess;
static uint8_t row1;
static uint8_t column1;
static SquareStatus p;

int main(void) {
    //FieldPrint_UART(&ownmap, &oppmap); // not sure how to test this one
    //Field Init Test------------------------------------------------------------------------------------------------------------------------
    FieldInit(&ownmap, &oppmap);

    int opprow, oppcol, ownrow, owncol;
    opprow = rand() % FIELD_ROWS;
    ownrow = rand() % FIELD_ROWS;
    oppcol = rand() % FIELD_COLS;
    owncol = rand() % FIELD_COLS;
    for (int i = 0; i < 2; i++) {
        switch (i) {
            case 0:
                if (ownmap.grid[ownrow][owncol] == FIELD_SQUARE_EMPTY && ownmap.grid[1][2] == FIELD_SQUARE_EMPTY) {
                    printf("Own Init() test passed\n");
                } else {
                    printf("Own Init() test didn't pass\n");
                }
                break;
            case 1:
                oppmap.grid[3][5] = FIELD_SQUARE_SMALL_BOAT;
                FieldInit(&ownmap, &oppmap);
                if (oppmap.grid[opprow][oppcol] == FIELD_SQUARE_UNKNOWN && oppmap.grid[3][5] == FIELD_SQUARE_UNKNOWN) {
                    printf("Opp Init() test passed\n");
                } else {
                    printf("Opp Init() test didn't pass\n");
                }
                printf("\n");
                break;
        }
    }
    // FieldGetSquareStatus Test------------------------------------------------------------------------------------------------------------------
    for (int i = 0; i < 7; i++) {
        switch (i) {
            case 0:
                row1 = rand() % FIELD_ROWS;
                column1 = rand() % FIELD_COLS;
                if (FieldGetSquareStatus(&ownmap, row1, column1) == FIELD_SQUARE_EMPTY) {
                    printf("1st FieldGetSquareStatus Test passed\n");
                } else {
                    printf("The status is %d\n", (FieldGetSquareStatus(&ownmap, row1, column1)));
                }
                break;
            case 1:
                row1 = rand() % FIELD_ROWS;
                column1 = rand() % FIELD_COLS;
                if (FieldGetSquareStatus(&oppmap, row1, column1) == FIELD_SQUARE_UNKNOWN) {
                    printf("2nd FieldGetSquareStatus Test passed\n");
                } else {
                    printf("The status is %d\n", (FieldGetSquareStatus(&oppmap, row1, column1)));
                }
                break;
            case 2:
                row1 = 7;
                column1 = 11;
                if (FieldGetSquareStatus(&ownmap, row1, column1) == FIELD_SQUARE_INVALID) {
                    printf("3rd FieldGetSquareStatus Test passed\n");
                } else {
                    printf("The status is %d\n", (FieldGetSquareStatus(&ownmap, row1, column1)));
                }
                break;
            case 3:
                row1 = 1;
                column1 = 1;
                if (FieldGetSquareStatus(&oppmap, row1, column1) == FIELD_SQUARE_UNKNOWN) {
                    printf("4th FieldGetSquareStatus Test passed\n");
                } else {
                    printf("The status is %d\n", (FieldGetSquareStatus(&oppmap, row1, column1)));
                }
                break;
            case 4:
                row1 = 7;
                column1 = 11;
                if (FieldGetSquareStatus(&ownmap, row1, column1) == FIELD_SQUARE_INVALID) {
                    printf("5th FieldGetSquareStatus Test passed\n");
                } else {
                    printf("The status is %d\n", (FieldGetSquareStatus(&ownmap, row1, column1)));
                }
                break;
            case 5:
                row1 = rand() % FIELD_ROWS;
                column1 = rand() % FIELD_COLS;
                if (FieldGetSquareStatus(&oppmap, row1, column1) == FIELD_SQUARE_UNKNOWN) {
                    printf("6th FieldGetSquareStatus Test passed\n");
                } else {
                    printf("The status is %d\n", (FieldGetSquareStatus(&oppmap, row1, column1)));
                }
                break;
            case 6:
                row1 = 7;
                column1 = 11;
                if (FieldGetSquareStatus(&ownmap, row1, column1) == FIELD_SQUARE_INVALID) {
                    printf("7th FieldGetSquareStatus Test passed\n");
                } else {
                    printf("The status is %d\n", (FieldGetSquareStatus(&ownmap, row1, column1)));
                }
                printf("\n");
                break;
        }
    }
    // FieldSetSquareStatus Test------------------------------------------------------------------------------------------------------------------
    for (int i = 0; i < 7; i++) {
        switch (i) {
            case 0:
                row1 = 4;
                column1 = 2;
                p = FIELD_SQUARE_LARGE_BOAT;
                if (FieldSetSquareStatus(&ownmap, row1, column1, p) == FIELD_SQUARE_EMPTY && ownmap.grid[row1][column1] == p) {
                    printf("1st FieldSetSquareStatus Test passed, current status is %d\n", p);
                } else {
                    printf("The status is %d\n", (FieldGetSquareStatus(&ownmap, row1, column1)));
                }
                ownmap.grid[row1][column1] = FIELD_SQUARE_EMPTY;
                break;

            case 1:
                row1 = 5;
                column1 = 0;
                p = FIELD_SQUARE_HUGE_BOAT;
                if (FieldSetSquareStatus(&oppmap, row1, column1, p) == FIELD_SQUARE_UNKNOWN && oppmap.grid[row1][column1] == p) {
                    printf("2nd FieldSetSquareStatus Test passed, current status is %d\n", p);
                } else {
                    printf("The status is %d\n", (FieldGetSquareStatus(&ownmap, row1, column1)));
                }
                oppmap.grid[row1][column1] = FIELD_SQUARE_UNKNOWN;
                break;

            case 2:
                row1 = 1;
                column1 = 9;
                p = FIELD_SQUARE_INVALID;
                if (FieldSetSquareStatus(&ownmap, row1, column1, p) == FIELD_SQUARE_EMPTY && ownmap.grid[row1][column1] == 9) {
                    printf("3rd FieldSetSquareStatus Test passed, current status is %d\n", p);
                } else {
                    printf("The status is %d\n", (FieldGetSquareStatus(&ownmap, row1, column1)));
                }
                ownmap.grid[row1][column1] = FIELD_SQUARE_EMPTY;
                break;
            case 3:
                row1 = 5;
                column1 = 8;
                p = FIELD_SQUARE_UNKNOWN;
                if (FieldSetSquareStatus(&oppmap, row1, column1, p) == FIELD_SQUARE_UNKNOWN && oppmap.grid[row1][column1] == 5) {
                    printf("4th FieldSetSquareStatus Test passed, current status is %d\n", p);
                } else {
                    printf("The status is %d\n", (FieldGetSquareStatus(&oppmap, row1, column1)));
                }
                oppmap.grid[row1][column1] = FIELD_SQUARE_UNKNOWN;
                printf("\n");
                break;
        }
    }
    // FieldAddBoat Test------------------------------------------------------------------------------------------------------------------
    FieldAddBoat(&ownmap, 0, 0, FIELD_DIR_EAST, FIELD_BOAT_TYPE_SMALL);
    FieldAddBoat(&ownmap, 1, 0, FIELD_DIR_EAST, FIELD_BOAT_TYPE_HUGE);
    FieldAddBoat(&ownmap, 0, 6, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_LARGE);
    FieldAddBoat(&ownmap, 2, 3, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_MEDIUM);

    if (ownmap.grid[0][0] == FIELD_SQUARE_SMALL_BOAT && ownmap.grid[0][1] == FIELD_SQUARE_SMALL_BOAT
            && ownmap.grid[0][2] == FIELD_SQUARE_SMALL_BOAT) {
        printf("Passed the 1st FieldAddBoat test\n");
    } else {
        printf("Didn't pass the 1st FieldAddBoat test\n");
    }

    if (ownmap.grid[1][0] == FIELD_SQUARE_HUGE_BOAT && ownmap.grid[1][1] == FIELD_SQUARE_HUGE_BOAT
            && ownmap.grid[1][2] == FIELD_SQUARE_HUGE_BOAT && ownmap.grid[1][3] == FIELD_SQUARE_HUGE_BOAT
            && ownmap.grid[1][4] == FIELD_SQUARE_HUGE_BOAT && ownmap.grid[1][5] == FIELD_SQUARE_HUGE_BOAT) {
        printf("Passed the 2nd FieldAddBoat test\n");
    } else {
        printf("Didn't pass the 2nd FieldAddBoat test\n");
    }

    if (ownmap.grid[0][6] == FIELD_SQUARE_LARGE_BOAT && ownmap.grid[1][6] == FIELD_SQUARE_LARGE_BOAT
            && ownmap.grid[2][6] == FIELD_SQUARE_LARGE_BOAT && ownmap.grid[3][6] == FIELD_SQUARE_LARGE_BOAT
            && ownmap.grid[4][6] == FIELD_SQUARE_LARGE_BOAT) {// && ownmap.grid[4][6] == 5){
        printf("Passed the 3rd FieldAddBoat test\n");
    } else {
        printf("Didn't pass the 3rd FieldAddBoat test\n");
    }

    if (ownmap.grid[2][3] == FIELD_SQUARE_MEDIUM_BOAT && ownmap.grid[3][3] == FIELD_SQUARE_MEDIUM_BOAT
            && ownmap.grid[4][3] == FIELD_SQUARE_MEDIUM_BOAT && ownmap.grid[5][3] == FIELD_SQUARE_MEDIUM_BOAT) {
        printf("Passed the 4th FieldAddBoat test\n");
    } else {
        printf("Didn't pass the 4th FieldAddBoat test\n");
    }

    if (FieldAddBoat(&ownmap, 5, 3, FIELD_DIR_EAST, FIELD_BOAT_TYPE_SMALL) == STANDARD_ERROR) {
        printf("Passed the 5th FieldAddBoat test\n");
    } else {
        printf("Didn't pass the 5th FieldAddBoat test\n");
    }

    printf("\n");

    // FieldRegisterEnemyAttack Test------------------------------------------------------------------------------------------------------------------
    // right now the thing looks like this
    //  *      0 1 2 3 4 5 6 7 8 9
    //  *     ---------------------
    //  *  0 [ 3 3 3 . . . 5 . . . ]
    //  *  1 [ 6 6 6 6 6 6 5 . . . ]
    //  *  2 [ . . . 4 . . 5 . . . ]
    //  *  3 [ . . . 4 . . 5 . . . ]
    //  *  4 [ . . . 4 . . 5 . . . ]
    //  *  5 [ . . . 4 . . . . . . ]
    for (int i = 0; i < 10; i++) {
        switch (i) {
            case 0:
                guess.row = 0;
                guess.col = 2;
                FieldRegisterEnemyAttack(&ownmap, &guess);
                if (ownmap.smallBoatLives == 2 && guess.result == RESULT_HIT) {
                    printf("Passed 1st FieldRegisterEnemyAttack test\n");
                } else {
                    printf("Failed 1st FieldRegisterEnemyAttack test\n");
                }

                FieldUpdateKnowledge(&ownmap, &guess);

                if (guess.result == RESULT_HIT && FieldGetSquareStatus(&ownmap, 0, 2) == FIELD_SQUARE_HIT)
                {
                    printf("Passed 1st FieldUpdateKnowledge Test\n");
                }
                else
                {
                    printf("Didn't pass 1st FieldUpdateKnowledge Test\n");
                }
                printf("\n");
                break;

            case 1:
                guess.row = 0;
                guess.col = 1;
                FieldRegisterEnemyAttack(&ownmap, &guess);
                if (ownmap.smallBoatLives == 1 && guess.result == RESULT_HIT) {
                    printf("Passed 2nd FieldRegisterEnemyAttack test\n");
                } else {
                    printf("Failed 2nd FieldRegisterEnemyAttack test\n");
                }

                FieldUpdateKnowledge(&ownmap, &guess);

                if (guess.result == RESULT_HIT && FieldGetSquareStatus(&ownmap, 0, 1) == FIELD_SQUARE_HIT)
                {
                    printf("Passed 2nd FieldUpdateKnowledge Test\n");
                }
                else
                {
                    printf("Didn't pass 2nd FieldUpdateKnowledge Test\n");
                }
                printf("\n");
                break;

            case 2:
                guess.row = 0;
                guess.col = 0;
                FieldRegisterEnemyAttack(&ownmap, &guess);
                if (ownmap.smallBoatLives == 0 && guess.result == RESULT_SMALL_BOAT_SUNK) {
                    printf("Passed 3rd FieldRegisterEnemyAttack test\n");
                } else {
                    printf("Failed 3rd FieldRegisterEnemyAttack test\n");
                }

                FieldUpdateKnowledge(&ownmap, &guess);
                if (guess.result == RESULT_SMALL_BOAT_SUNK && FieldGetSquareStatus(&ownmap, 0, 0) == FIELD_SQUARE_HIT)
                {
                    printf("Passed 3rd FieldUpdateKnowledge Test\n");
                }
                else
                {
                    printf("Didn't pass 3rd FieldUpdateKnowledge Test\n");
                }
                printf("\n");
                break;

            case 3:
                guess.row = 5;
                guess.col = 3;
                FieldRegisterEnemyAttack(&ownmap, &guess);
                if (ownmap.mediumBoatLives == 3 && guess.result == RESULT_HIT) {
                    printf("Passed 4th FieldRegisterEnemyAttack test\n");
                } else {
                    printf("Failed 4th FieldRegisterEnemyAttack test\n");
                }

                FieldUpdateKnowledge(&ownmap, &guess);

                if (guess.result == RESULT_HIT && FieldGetSquareStatus(&ownmap, 5, 3) == FIELD_SQUARE_HIT)
                {
                    printf("Passed 4th FieldUpdateKnowledge Test\n");
                }
                else
                {
                    printf("Didn't pass 4th FieldUpdateKnowledge Test\n");
                }
                printf("\n");
                break;

            case 4:
                guess.row = 5;
                guess.col = 9;
                FieldRegisterEnemyAttack(&ownmap, &guess);
                if (guess.result == RESULT_MISS) {
                    printf("Passed 5th FieldRegisterEnemyAttack test\n");
                } else {
                    printf("Failed 5th FieldRegisterEnemyAttack test\n");
                }

                FieldUpdateKnowledge(&ownmap, &guess);
                if (guess.result == RESULT_MISS && FieldGetSquareStatus(&ownmap, 5, 9) == FIELD_SQUARE_MISS)
                {
                    printf("Passed 5th FieldUpdateKnowledge Test\n");
                }
                else
                {
                    printf("Didn't pass 5th FieldUpdateKnowledge Test\n");
                }
                printf("\n");
                break;

            case 5:
                guess.row = 1;
                guess.col = 3;
                FieldRegisterEnemyAttack(&ownmap, &guess);

                if (ownmap.hugeBoatLives == 5 && guess.result == RESULT_HIT) {
                    printf("Passed 6th FieldRegisterEnemyAttack test\n");
                } else {
                    printf("Failed 6th FieldRegisterEnemyAttack test\n");
                }

                FieldUpdateKnowledge(&ownmap, &guess);
                if (guess.result == RESULT_HIT && FieldGetSquareStatus(&ownmap, 1, 3) == FIELD_SQUARE_HIT)
                {
                    printf("Passed 6th FieldUpdateKnowledge Test\n");
                }
                else
                {
                    printf("Didn't pass 6th FieldUpdateKnowledge Test\n");
                }
                printf("\n");
                break;

                case 6:
                    guess.row = 1;
                    guess.col = 7;
                    FieldRegisterEnemyAttack(&ownmap, &guess);
                    if (guess.result == RESULT_MISS)
                    {
                        printf("Passed 7th FieldRegisterEnemyAttack test\n");
                    }
                    else
                    {
                        printf("Failed 7th FieldRegisterEnemyAttack test\n");
                    }


                    FieldUpdateKnowledge(&ownmap, &guess);
                    if (guess.result == RESULT_MISS && FieldGetSquareStatus(&ownmap, 1, 7) == FIELD_SQUARE_MISS)
                    {
                        printf("Passed 7th FieldUpdateKnowledge Test\n");
                    }   
                    else
                    {
                        printf("Didn't pass 7th FieldUpdateKnowledge Test\n");
                    }
                    printf("\n");
                    break;

                case 7:
                    guess.row = 1;
                    guess.col = 6;
                    FieldRegisterEnemyAttack(&ownmap, &guess);

                    if (ownmap.largeBoatLives == 4 && guess.result == RESULT_HIT)
                    {
                        printf("Passed 8th FieldRegisterEnemyAttack test\n");
                    }
                    else
                    {
                        printf("Failed 8th FieldRegisterEnemyAttack test\n");
                    }

                    FieldUpdateKnowledge(&ownmap, &guess);
                    if (guess.result == RESULT_HIT && FieldGetSquareStatus(&ownmap, 1, 6) == FIELD_SQUARE_HIT)
                    {
                        printf("Passed 8th FieldUpdateKnowledge Test\n");
                    }
                    else
                    {
                        printf("Didn't pass 8th FieldUpdateKnowledge Test\n");
                    }
                    printf("\n");
                    break;

                case 8:
                    guess.row = 2;
                    guess.col = 6;
                    FieldRegisterEnemyAttack(&ownmap, &guess);

                    if (ownmap.largeBoatLives == 3 && guess.result == RESULT_HIT)
                    {
                        printf("Passed 9th FieldRegisterEnemyAttack test\n");
                    }
                    else
                    {
                        printf("Failed 9th FieldRegisterEnemyAttack test\n");
                    }
                    FieldUpdateKnowledge(&ownmap, &guess);
                    if (guess.result == RESULT_HIT && FieldGetSquareStatus(&ownmap, 2, 6) == FIELD_SQUARE_HIT)
                    {
                        printf("Passed 9th FieldUpdateKnowledge Test\n");
                    }
                    else
                    {
                        printf("Didn't pass 9th FieldUpdateKnowledge Test\n");
                    }
                    printf("\n");
                    break;
                }
    }

    //FieldGetBoatStates------------------------------------------------------------------------------------------------------------------
    // FieldAddBoat(&ownmap, 3, 9, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_SMALL);
    if (FieldGetBoatStates(&ownmap) == 0b1110) { // there are boats added to the map earlier ( in Addboat test)
        printf("Passed the 1st FieldGetBoatStates test\n");
    } else {
        printf("Failed the 1st FieldGetBoatStates test\n");
    }
    guess.row = 2;
    guess.col = 3;
    FieldRegisterEnemyAttack(&ownmap, &guess);
    FieldUpdateKnowledge(&ownmap, &guess);
    guess.row = 3;
    guess.col = 3;
    FieldRegisterEnemyAttack(&ownmap, &guess);
    FieldUpdateKnowledge(&ownmap, &guess);
    guess.row = 4;
    guess.col = 3;
    FieldRegisterEnemyAttack(&ownmap, &guess);
    FieldUpdateKnowledge(&ownmap, &guess);

    if (FieldGetBoatStates(&ownmap) == 0b1100) {
        printf("Passed the 2nd FieldGetBoatStates test\n");
    } else {
        printf("Failed the 2nd FieldGetBoatStates test\n");
    }
    printf("\n");
    //FieldAIPlaceAllBoats------------------------------------------------------------------------------------------------------------------

    FieldInit(&ownmap, &oppmap);
    FieldAIPlaceAllBoats(&ownmap) == SUCCESS ? printf("Success at FieldAiPlaceAllBoats\n") : printf("Failure at FieldAiPlaceAllBoats\n");
    // printf("Failed the FieldGetBoatStates test\n"); // it's not printing anything if I call this function
    printf("\n");

    if (FieldGetBoatStates(&ownmap) == 0b1111) {
        printf("Passed the 1st FieldAIPlaceAllBoats test\n");
    } else {
        printf("Failed the 1st FieldGetBoatStates test\n");
    }
    printf("\n");
    //FieldAIDecideGuess------------------------------------------------------------------------------------------------------------------
    FieldAddBoat(&ownmap, 0, 0, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_SMALL);
    FieldInit(&ownmap, &oppmap);

    if (FieldGetSquareStatus(&oppmap, FieldAIDecideGuess(&oppmap).row, FieldAIDecideGuess(&oppmap).col) == oppmap.grid[0][0]) {
        printf("Passed 1st FieldAIDecideGuess test\n");
    } else {
        printf("Failed 1st FieldAIDecideGuess test\n");
    }

    if (FieldGetSquareStatus(&oppmap, FieldAIDecideGuess(&oppmap).row, FieldAIDecideGuess(&oppmap).col) == oppmap.grid[1][0]) {
        printf("Passed 2nd FieldAIDecideGuess test\n");
    } else {
        printf("Failed 2nd FieldAIDecideGuess test\n");
    }

    if (FieldGetSquareStatus(&oppmap, FieldAIDecideGuess(&oppmap).row, FieldAIDecideGuess(&oppmap).col) == oppmap.grid[2][0]) {
        printf("Passed 3rd FieldAIDecideGuess test\n");
    } else {
        printf("Failed 3rd FieldAIDecideGuess test\n");
    }
    return 0;
}