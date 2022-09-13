// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>
#include <GenericTypeDefs.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "Leds_Lab06.h"


// **** Declare any datatypes here ****

struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****
#define A_SEC 2*38
#define B_SEC 3*38
#define C_SEC 5*38

// **** Declare function prototypes ****

static struct Timer timerA;
static struct Timer timerB;
static struct Timer timerC;

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
    printf("Welcome to rthavez's lab6 part1 (timers).  Compiled on %s %s.\n", __TIME__, __DATE__);

    timerA.timeRemaining = A_SEC;
    timerA.event = FALSE;
    
    timerB.timeRemaining = B_SEC;
    timerB.event = FALSE;
    
    timerC.timeRemaining = C_SEC;
    timerC.event = FALSE;

    LEDS_INIT();

    while (1) {

        //poll timer A
        
     
        if (timerA.event) {
            //react to timer A events
            timerA.event = FALSE;
            printf("A");
            //clear timer A event flag
            LEDS_SET(0x01);
        }

        if (timerB.event) {
            timerB.event = FALSE;
            printf("B");
            LEDS_SET(0x02);
        }
        if (timerC.event) {
            timerC.event = FALSE;
            printf("C");
            LEDS_SET(0x04);
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
    //update timerA
    timerA.timeRemaining--;
    timerB.timeRemaining--;
    timerC.timeRemaining--;

    //if timerA has counted down,
    if (timerA.timeRemaining == 0) {
        //generate timerA event
        timerA.event = TRUE;
        //reset timerA
        timerA.timeRemaining = A_SEC;

    }

    //if timerB has counted down,
    if (timerB.timeRemaining == 0) {
        //generate timerB event
        timerB.event = TRUE;
        //reset timerB
        timerB.timeRemaining = B_SEC;

    }

    //if timerC has counted down,
    if (timerC.timeRemaining == 0) {
        //generate timerC event
        timerC.event = TRUE;
        //reset timerC
        timerC.timeRemaining = C_SEC;

    }




    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}