//Reuben T. Chavez
// April 18, 2022,
// ECE 13E Spring 2022

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <math.h>
//CMPE13 Support Library
#include "BOARD.h"


// User libraries
#include "stack.h"

int main() {
    BOARD_Init();

    printf("\n###### Beginning rtchavez's stack test harness: ####\n\n");

    //What follows is starter code.  You will need to modify it!

    printf("Does StackInit() set the currentItemIndex appropriately?\n");
    struct Stack stack = {};
    StackInit(&stack);
    if (stack.currentItemIndex == -1) {
        printf("\tpassed\n");
    } else {
        printf("\tfailed\n");
    }

    // Testing when stack is empty
    printf("Testing if StackIsFull() & StackIsEmpty() work appropriately when empty:\n");

    StackIsEmpty(&stack) && !StackIsFull(&stack) ? printf("\tpassed\n") : printf("\tfailed\n");

    // Testing if stack pushes properly, and  it conditions
    printf("Testing if Stack work appropriately when Pushing:\n");

    int test1 = 0;
    int test2 = 0;
    int test3 = 0;

    for (double i = 0; i <= STACK_SIZE; i++) {

        //Store function return
        int push = StackPush(&stack, i);

        // Case when StackPush works accordingly 
        if (push == SUCCESS) {

            // Test 1: Current Index is inputed value
            // formated like this to avoid round off error

            double result = fabsf(stack.stackItems[stack.currentItemIndex] - i);
            result < 1e-4 ? test1++ : printf("at i : %f failed\n", i);

            // Test 2: Stack Size is equal to current i
            StackGetSize(&stack) == (int) i + 1 ? test2++ : printf("failed\n");

        } else if (push == STANDARD_ERROR && i == 21) {
            // Should increment once indicating the stack return Standard Error
            test3++;
            break;
        } else {
            printf("StackPush() Does not return specified values");
        }
    }

    // Expected outcome for test that stack has been iterated
    if (test1 + test2 + test3 == 41) {
        printf("\tStackPush() and StackGetSize() works through out stack\n");
    } else {
        printf("\tFailed All tests\n");
    }


    // Testing StackPop() works correctly
    printf("Testing is Stack works appropriately when Popping\n");

    test1 = 0;
    test2 = 0;
    test3 = 0;

    double store;
    for (double i = STACK_SIZE - 1; i >= -1; i--) {

        // Store function result
        int pop = StackPop(&stack, &store);

        // Current Index is inputed value
        if (pop == SUCCESS) {
            //Test 1: popped value should be equal to current i
            store == i ? test1++ : printf("at i : %f failed\n", i);
            //Test 2: current index in stack should be decrement
            stack.currentItemIndex == i - 1 ? test2++ : printf("at i : %f failed\n", i);
        } else if (pop == STANDARD_ERROR) {
            // Should increment if StackPop() returns Error
            test3++;
            break;
        }

    }
    // Expected outcome for test that stack has been iterated
    if (test1 + test2 + test3 == 41) {
        printf("\tStackPop() works through out stack\n");
    } else {
        printf("\tFailed All tests\n");
    }



    BOARD_End();
    //test stackInit:
    while (1);
    return 0;
}


