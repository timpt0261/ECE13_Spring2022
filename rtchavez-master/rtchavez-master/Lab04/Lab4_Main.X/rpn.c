// Libraries

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// User Libraries
#include "rpn.h"
#include "stack.h"

enum num {
    NOT_A_NUMBER = 0,
    NUMBER
};
// Function : Return whether the inputed string is a number or not 
//            Does this through iterating string to see if it has only
//            digits and one or no decimal points
//
// @parm : input is a single char 
// @return: if input is following op it return 1, otherwise return 0

int IsOperator(char *input) {
    if (strlen(input) == 1 && !isdigit(input[0])) {
        if (strcmp(input, "*") == 0) {
            return '*';
        } else if (strcmp(input, "+") == 0) {
            return '+';

        } else if (strcmp(input, "-") == 0) {
            return '-';

        } else if (strcmp(input, "/") == 0) {
            return '/';
        }

    }
    return 0;
}

// Function : Return whether the inputed string is a number or not 
//            Does this through iterating string to see if it has only
//            digits and one or no decimal points
//
// @parm : input, the inputed string
// @return: returns NOT_A_NUMBER if statement if false , NUMBER if it passes 
// References:
//    - https://www.cs.cmu.edu/~pattis/15-1XX/common/handouts/ascii.html

int IsNumber(char *input) {
    int decimal = 0;
    
    //if input is negative
    if(atof(input) < 0){
        return NUMBER;
    }

    // check 
    for (int i = 0; i < strlen(input); i++) {
        if (!isdigit(input[i]) && input[i] == '.') {
            decimal++;
        } else if (!isdigit(input[i])) {
            return NOT_A_NUMBER;
        }
    }
    
   

    return decimal <= 1 ? NUMBER : NOT_A_NUMBER;

}

/* RPN_Evaluate() parses and evaluates a string that contains 
 * a valid Reverse Polish Notation string (no newlines!)  
 * @param:  rpn_string - a string in polish notation.  Tokens must be either 
 *          arithmetic operators or numbers.
 * @param:  result - a pointer to a double that will be modified to contain
 *          the return value of the rpn expression.
 * @return: error - if the rpn expression is invalid, 
 *          an appropriate rpn_error value is returned.
 * 
 * RPN_Evaluate supports the following basic arithmetic operations:
 *   + : addition
 *   - : subtraction
 *   * : multiplication
 *   / : division
 * Numeric tokens can be positive or negative, and can be integers or 
 * decimal floats.  RPN_Evaluate should be able to handle strings of 
 * at least 255 length.
 * */
int RPN_Evaluate(char * rpn_string, double * result) {
    // Used example from 4.3 in K & R
    double op;
    double op2;
    struct Stack stack = {};
    StackInit(&stack);
    ProcessBackspaces(rpn_string);


    char *token = strtok(rpn_string, " ");

    // When after doing all the math/operations there are more than 1 items in the stack

    // while next op
    while (token != NULL) {
        // if the token is an operator
        if (IsOperator(token)) {
            int operator = IsOperator(token);
            // check when stack has less than two 
            if (StackGetSize(&stack) < 2) {
                return RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
            }

            // check if operation has sufficient operator if stack 
            if (StackPop(&stack, &op) == STANDARD_ERROR || StackPop(&stack, &op2) == STANDARD_ERROR) {
                return RPN_ERROR_STACK_UNDERFLOW;
            }

            // do corresponding operation depending what IsOperator returns
            switch (operator) {
                case '+':
                    StackPush(&stack, op + op2);
                    break;
                case '*':
                    StackPush(&stack, op * op2);
                    break;
                case '-':
                    StackPush(&stack, op - op2);
                    break;
                case '/':
                    if (op2 < 0.0) {
                        StackPush(&stack, op / op2);
                        break;
                    }
                    return RPN_ERROR_DIVIDE_BY_ZERO;


            }
            // else the token is a number   
        } else if (IsNumber(token)) {
            if (StackIsFull(&stack)) {
                return RPN_ERROR_STACK_OVERFLOW;
            }

            StackPush(&stack, atof(token));
            // else a the token is invalid
        } else {
            return RPN_ERROR_INVALID_TOKEN;

        }
        token = strtok(NULL, " ");
    }

    if (StackGetSize(&stack) > 1) {
        return RPN_ERROR_TOO_MANY_ITEMS_REMAIN;
    }

    StackPop(&stack, result);
    return RPN_NO_ERROR;
}


/**
 * This function should read through an array of characters, checking for backspace characters. 
 * When it encounters a backspace character, it eliminates the backspace, the preceeding character
 * (if such a character exists), and shifts all subsequent characters as appropriate.
 * @param string_to_modify The string that will be processed for backspaces. 
 *        This string is modified "in place", so it is both an input and an output to the function.
 * @return Returns the size of the resulting string in "string_to_modify".
 *
 * ProcessBackspaces() should be able to handle multiple repeated backspaces and also
 * strings with more backspaces than characters. It should be able to handle strings of at least 255 length.
 * 
 * */

// References:
//  -  https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
//  - Attended Navid's Section on Tuesday  April 19, 2022

int ProcessBackspaces(char *rpn_sentence) {
    // char copy is set to size of rpn_sentence
    char copy[strlen(rpn_sentence)];
    // sets copy to empty string
    memset(copy, '\0', sizeof (copy));

    // token is set to first token in rpn_sentence w/o '\b'
    char* token = strtok(rpn_sentence, "\b");
    // set t_size to zero
    int t_size = 0;

    while (token != NULL) {
        // copy token to char copy 
        memcpy(copy + t_size, token, strlen(token) + 1);
        // increment size to next index
        t_size += strlen(token);
        // set token to next token in rpn_sentence
        token = strtok(NULL, "\b");
    }
    // copy results 
    strcpy(rpn_sentence, copy);
    return strlen(rpn_sentence);
}