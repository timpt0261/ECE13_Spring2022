
// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>



//CMPE13 Support Library
#include "BOARD.h"
#include "Leds_Lab06.h"
#include "string.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// **** Declare any datatypes here ****

struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};
// **** Define global, module-level, or external variables here ****
static struct Timer timer1;

// **** Declare function prototypes ****
#define LEFT 0x80
#define RIGHT 0x01
#define ZERO 0x00
#define TIME_1 2

int main(void)
{
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
    printf("Welcome to rtchavez's lab6 part2 (bounce_switch).  Compiled on %s %s.\n", __TIME__, __DATE__);

    LEDS_INIT();
    LEDS_SET(ZERO);
    timer1.event = FALSE;
    timer1.timeRemaining = TIME_1;
    char *direction = "right";
    //    unsigned char switchState = SWITCH_STATES();
    while (1) {
        //poll timer events and react if any occur
        if (timer1.event) {

         
          // get current led
            unsigned char curr = LEDS_GET();

            // if it the end
             if (curr == ZERO) {
                LEDS_SET(RIGHT);
                curr = LEDS_GET();
            }
            
            // check which direction
            if (curr == RIGHT) {
                direction = "right";
            }else if (curr == LEFT){
                direction = "left";
            } 

            if (strcmp(direction, "right") == 0) {
                curr <<= 1;
                LEDS_SET(curr);
            } else if (strcmp(direction, "left") == 0) {
                curr >>= 1;
                LEDS_SET(curr);
            }
            
            timer1.event = FALSE;
        }
    }


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}

/**
 * This is the interrupt for the Timer1 peripheral. It will trigger at the frequency of the peripheral
 * clock, divided by the timer 1 prescaler and the interrupt interval.
 * 
 * It should not be called, and should communicate with main code only by using module-level variables.
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/

    uint8_t switchState = SWITCH_STATES();
    uint8_t total = 2;
    timer1.timeRemaining--;
    // if timer1 has counted down,

    if (switchState & SWITCH_STATE_SW1) {
        total += TIME_1;
    }

    if (switchState & SWITCH_STATE_SW2) {
        total += TIME_1;
    }
    if (switchState & SWITCH_STATE_SW3) {
        total += TIME_1;
    }
    if (switchState & SWITCH_STATE_SW4) {
        total += TIME_1;
    }
    if (timer1.timeRemaining == 0) {
        //generate timer1 event
        timer1.event = TRUE;
        //reset timer1
        timer1.timeRemaining = total + 2;

    }


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}