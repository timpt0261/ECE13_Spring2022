// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "Buttons.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****

// **** Define global, module-level, or external variables here ****

// **** Declare function prototypes ****

int main(void) {
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 2; // 1:64 prescaler
    PR1 = 0xFFFF; // interrupt at max interval
    T1CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T1IF = 0; //clear the interrupt flag before configuring
    IPC1bits.T1IP = 4; // priority of  4
    IPC1bits.T1IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T1IE = 1; // turn the interrupt on

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Welcome to rtchavez's lab6 part4 (ButtonsTest).  Compiled on %s %s.\n", __TIME__, __DATE__);


    printf("Please press some buttons!\n");


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/
    ButtonsInit();
    //    char *bt1 = "----";
    //    char *bt2 = "----";
    //    char *bt3 = "----";
    //    char *bt4 = "----";


    printf("A test\n");
    while (1) {
        char *bt1 = "----";
        char *bt2 = "----";
        char *bt3 = "----";
        char *bt4 = "----";

        uint8_t buttonCheckEvent = ButtonsCheckEvents();
        if (buttonCheckEvent) {
            printf("Button Check Events: 0x%x\n", buttonCheckEvent);


            if (buttonCheckEvent & BUTTON_EVENT_4UP && (buttonCheckEvent & BUTTON_EVENT_4DOWN) == 0x00) {
                bt4 = "UP";
            } else if ((buttonCheckEvent & BUTTON_EVENT_4UP) == 0x00 && buttonCheckEvent & BUTTON_EVENT_4DOWN) {
                bt4 = "DOWN";
            }

            if (buttonCheckEvent & BUTTON_EVENT_3UP && (buttonCheckEvent & BUTTON_EVENT_3DOWN) == 0x00) {
                bt3 = "UP";
            } else if ((buttonCheckEvent & BUTTON_EVENT_3UP) == 0x00 && buttonCheckEvent & BUTTON_EVENT_3DOWN) {
                bt3 = "DOWN";
            }

            if (buttonCheckEvent & BUTTON_EVENT_2UP && (buttonCheckEvent & BUTTON_EVENT_2DOWN) == 0x00) {
                bt2 = "UP";
            } else if ((buttonCheckEvent & BUTTON_EVENT_2UP) == 0x00 && buttonCheckEvent & BUTTON_EVENT_2DOWN) {
                bt2 = "DOWN";
            }

            if (buttonCheckEvent & BUTTON_EVENT_1UP && (buttonCheckEvent & BUTTON_EVENT_1DOWN) == 0x00) {
                bt1 = "UP";
            } else if ((buttonCheckEvent & BUTTON_EVENT_1UP) == 0x00 && buttonCheckEvent & BUTTON_EVENT_1DOWN) {
                bt1 = "DOWN";
            }

            printf("EVENT:  4:%s 3:%s 2:%s 1:%s\n", bt4, bt3, bt2, bt1);


        }



    }
}

/**
 * This is the interrupt for the Timer1 peripheral. It should check for button events and stores them in a
 * module-level variable.
 * 
 * You should not modify this function for ButtonsTest.c or bounce_buttons.c!
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void) {
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}