// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "Buttons.h"
#include "Leds_Lab06.h"

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****
struct Timer {
    uint8_t event;
    uint16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****
#define B_LED4 0b11000000
#define B_LED3 0b00110000
#define B_LED2 0b00001100
#define B_LED1 0b00000011

#define COMPLIMENT(x) (0xFFFFF - x) + 1

static struct Timer timer1;

// **** Declare function prototypes ****

int main(void) {
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 1; // 1:8 prescaler
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
    printf("Welcome to CRUZID's lab6 part5 (bounce_buttons).  Compiled on %s %s.\n", __TIME__, __DATE__);


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/
    LEDS_INIT();
    ButtonsInit();
    printf("A test\n");
    while (1) {
        uint8_t led_on = 0x00;
        uint8_t buttonCheckEvent = ButtonsCheckEvents();
        if (buttonCheckEvent) {

            if ((buttonCheckEvent & BUTTON_EVENT_4UP) == 0x00 && buttonCheckEvent & BUTTON_EVENT_4DOWN) {
                led_on |= B_LED4;
                //                LEDS_SET(B_LED4);
//            } else if (!(buttonCheckEvent & BUTTON_EVENT_4UP) && buttonCheckEvent & BUTTON_EVENT_4DOWN) {
//                led_on |= COMPLIMENT(B_LED4);
//            }

            if ((buttonCheckEvent & BUTTON_EVENT_3UP) == 0x00 && buttonCheckEvent & BUTTON_EVENT_3DOWN) {

                led_on |= B_LED3;
//            } else if (!(buttonCheckEvent & BUTTON_EVENT_3UP) && buttonCheckEvent & BUTTON_EVENT_3DOWN) {
//                led_on |= COMPLIMENT(B_LED3);
//            }

            if ((buttonCheckEvent & BUTTON_EVENT_2UP) == 0x00 && buttonCheckEvent & BUTTON_EVENT_2DOWN) {

                led_on |= B_LED2;
            } /

            if ((buttonCheckEvent & BUTTON_EVENT_1UP) == 0x00 && buttonCheckEvent & BUTTON_EVENT_1DOWN) {

                led_on |= B_LED1;
//            } else if (!(buttonCheckEvent & BUTTON_EVENT_1UP) && buttonCheckEvent & BUTTON_EVENT_1DOWN) {
//                led_on |= COMPLIMENT(B_LED1);
//            }

        }

        printf("led_on: 0x%x\n", led_on);
        LEDS_SET(led_on);

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
    timer1.timeRemaining--;
    
    if(timer1.timeRemaining == 0){
        timer1.event = TRUE;
        timer1.timeRemaining =  38 * 10;
    }

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}