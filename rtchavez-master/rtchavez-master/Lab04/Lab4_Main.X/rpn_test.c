// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"

#define MAX_INPUT_LENGTH 60

int main() {
    BOARD_Init();
    int error;

    printf("\n###### Beginning rtchavez's rpn test harness: ####\n\n");

    //What follows is starter code.  You will need to modify it!

    char test0[] = "1 1 +";
    double result0;
    double expected0 = 2;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test0);
    error = RPN_Evaluate(test0, &result0);
    if (error) {
        printf("Failed, RPN_Evaluate produced an error\n");
    } else if (result0 != expected0) {
        printf("Failed, expected = %f , result = %f\n", expected0, result0);
    } else {
        printf("Success!\n");
    }

    //testing if it can do arthmitic properly
    printf("Testing RPN_NO_ERROR\n");
    char test1[MAX_INPUT_LENGTH] = "2 -4 * 2 +  3.2 / 1 -";
    double result1;
    double expected1 = -2.875;
    int error1 = RPN_Evaluate(test1, &result1);
    if (error1) {
        printf("Failed, RPN_Evaluate produced an error\n");
    } else if (result1 != expected1) {
        printf("Failed, expected = %f , result = %f\n", expected1, result1);
    } else {
        printf("Returned RPN_NO_ERROR\n");
    }


    //testing if returns stack overflow
    printf("\nTesting RPN_ERROR_STACK_OVERFLOW\n");
    char test2[MAX_INPUT_LENGTH] = " 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21";
    double result2;
    int error2 = RPN_Evaluate(test2, &result2);
    if (error2 == RPN_ERROR_STACK_OVERFLOW) {
        printf("\tPasses\n");
    } else {
        printf("\tFailed, didn't pass according test\n");
    }

    //testing if return stack underflow
    printf("\nTesting RPN_ERROR_STACK_UNDERFLOW:\n");
    char test3[MAX_INPUT_LENGTH] = "2 7 3 - ";
    char test4[MAX_INPUT_LENGTH] = "1 5 / 8 * 5";
    double result3, result4;
    int error3, error4;

    error3 = RPN_Evaluate(test3, &result3);
    error4 = RPN_Evaluate(test4, &result4);

    if (error3 == RPN_ERROR_STACK_UNDERFLOW && error4 == RPN_ERROR_STACK_UNDERFLOW) {
        printf("\t Passes\n");
    } else {
        printf("\tFailed, didn't pass according test\n");
    }

    // testing for invalid token;
    printf("\nRPN_ERROR_INVALID_TOKEN:\n");
    char test5[MAX_INPUT_LENGTH] = "a.0 + 1";
    char test6[MAX_INPUT_LENGTH] = "2.#  4.3 + 8.9 -91";
    double result5, result6;

    int error5, error6;

    error5 = RPN_Evaluate(test5, &result5);
    error6 = RPN_Evaluate(test6, &result6);

    if (error5 == RPN_ERROR_INVALID_TOKEN && error6 == RPN_ERROR_INVALID_TOKEN) {
        printf("\t Passes\n");
    } else {
        printf("Failed, didn't pass according test\n");
    }

    // testing for divided by zero
    printf("\nTesting RPN_ERROR_DIVIDE_BY_ZERO:\n");
    char test7[MAX_INPUT_LENGTH] = "1 0 /";
    char test8[MAX_INPUT_LENGTH] = " 9 8 + 4 / 15 * 0 /";
    double result7, result8;

    int error7, error8;

    error7 = RPN_Evaluate(test7, &result7);
    error8 = RPN_Evaluate(test8, &result8);

    if (error7 == RPN_ERROR_DIVIDE_BY_ZERO && error8 == RPN_ERROR_DIVIDE_BY_ZERO) {
        printf("\t Passes\n");
    } else {
        printf("Failed, didn't pass according test\n");
    }
    //testing to few item remain

    printf("\nTesting RPN_ERROR_TOO_FEW_ITEMS_REMAIN:\n");
    char test9[MAX_INPUT_LENGTH] = "";
    char test10[MAX_INPUT_LENGTH] = " 9 + ";
    double result9, result10;

    int error9, error10;

    error9 = RPN_Evaluate(test9, &result9);
    error10 = RPN_Evaluate(test10, &result10);

    if (error9 == RPN_ERROR_TOO_FEW_ITEMS_REMAIN && error10 == RPN_ERROR_TOO_FEW_ITEMS_REMAIN) {
        printf("\t Passes\n");
    } else {
        printf("\tFailed, didn't pass according test\n");
    }


    // testing for to many item remain
    printf("\nTesting RPN_ERROR_TOO_MANY_ITEMS_REMAIN:\n");
    char test11[MAX_INPUT_LENGTH] = "3 3 9 +";
    char test12[MAX_INPUT_LENGTH] = " 9 8 / 5 4 +";
    double result11, result12;

    int error11, error12;

    error11 = RPN_Evaluate(test11, &result11);
    error12 = RPN_Evaluate(test12, &result12);

    if (error11 == RPN_ERROR_TOO_MANY_ITEMS_REMAIN && error12 == RPN_ERROR_TOO_MANY_ITEMS_REMAIN) {
        printf("\t Passes\n");
    } else {
        printf("\tFailed, didn't pass according test\n");
    }


    printf("\nTesting ProcessBackspaces:\n");
    char test_pb1[] = "123\b34";
    ProcessBackspaces(test_pb1);
    printf("result    : %s\n", test_pb1);
    printf("should be : 1234\n");

    // testing backspace
    printf("Test 2 :");
    char test_pb2[] = "\bTesting Side to Side\b";
    char result_pb2[] = "Testing Side to Side";

    int bef_pb2 = strlen(test_pb2);
    int aft_pb2 = ProcessBackspaces(test_pb2);

    int dif_pb2 = bef_pb2 - aft_pb2;

    // Tests if test_pb2 is expected result and all '\b' are gone
    if (strcmp(test_pb2, result_pb2) == 0 && dif_pb2 == 2) {
        printf(" Passes \n");
    } else {
        printf(" Fails \n");
    }
    printf("Test 3 :");
    char test_pb3[] = "\bT\be\bs\bt\bi\bn\bg\b i\bn\b t\bh\be M\bi\bd\bd\bl\be\b o\bf\b Words";
    char result_pb3[] = "Testing in the Middle of Words";

    int bef_pb3 = strlen(test_pb3);
    int aft_pb3 = ProcessBackspaces(test_pb3);

    int dif_pb3 = bef_pb3 - aft_pb3;

    // Tests if test_pb3 is expected result and all '\b' are gone
    if (strcmp(test_pb3, result_pb3) == 0 && dif_pb3 == 20) {
        printf(" Passes \n");
    } else {
        printf(" Fails \n");
    }
    printf("Test 4 :");
    // testing with only '\b'
    char test_pb4[] = "\b\b\b";
    char result_pb4[10];
    memset(result_pb4, '\0', sizeof (result_pb4));

    int bef_pb4 = strlen(test_pb4);
    int aft_pb4 = ProcessBackspaces(test_pb4);

    int dif_pb4 = bef_pb4 - aft_pb4;

    // Tests if test_pb4 is expected result and all '\b' are gone
    if (strcmp(test_pb4, result_pb4) == 0 && dif_pb4 == 3) {
        printf(" Passes \n");
    } else {
        printf(" Fails \n");
    }

    BOARD_End();
    while (1);
}


