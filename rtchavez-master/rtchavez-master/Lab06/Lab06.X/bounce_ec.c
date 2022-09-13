// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries


// **** Set macros and preprocessor directives ****

struct AdcResult {
    uint8_t event;
    uint16_t voltage;
};

struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};

// **** Declare any datatypes here ****

#define WINDOW 5
#define MAX_VOLTAGE 1032.0
#define LOW_VOLTAGE 0.0

#define LEFT 0x80
#define RIGHT 0x01
#define ZERO 0x00
#define TIME_1 2



// **** Define global, module-level, or external variables here ****

static struct AdcResult adc;

static struct Timer timerA;
static struct Timer timerB;
static struct Timer timerC;

// **** Declare function prototypes ****

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


    // Enable interrupts for the ADC
    IPC6bits.AD1IP = 2;
    IPC6bits.AD1IS = 0;
    IEC1bits.AD1IE = 1;

    // Set B2 to an input so AN2 can be used by the ADC.
    TRISBbits.TRISB2 = 1;

    // Configure and start the ADC
    AD1CHSbits.CH0SA = 2; // add B2 to the mux
    AD1PCFGbits.PCFG2 = 0; // add b2 to the ADC
    AD1CSSLbits.CSSL2 = 1; // and add b2 to the scanner

    AD1CON1 = 0; // start with 0
    AD1CON1bits.SSRC = 0b111; // auto conversion
    AD1CON1bits.ASAM = 1; // auto sample

    AD1CON2 = 0; // start with 0
    AD1CON2bits.SMPI = 7; // one interrupt per 8 samples

    AD1CON3 = 0; // start with 0
    AD1CON3bits.SAMC = 29; // long sample time
    AD1CON3bits.ADCS = 50; // long conversion time

    AD1CON1bits.ADON = 1; // and finally turn it on

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
  printf("Welcome to RTCHAVEZ's lab6 part6 (Extra Credit).  Compiled on %s %s.\n",__TIME__,__DATE__);


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/
   
    LEDS_INIT();
    LEDS_SET(ZERO);
    OledInit();
    
    adc.event = TRUE;
    float percent;
    char result[100];
    
    timer1.event = TRUE;
    timer1.timeRemaining = TIME_1;
    char *direction = "right";
    
    
    while (1) {
        if (adc.event == TRUE) {
            percent = (adc.voltage / MAX_VOLTAGE) * 100.0;  
            OledClear(OLED_COLOR_BLACK);
            sprintf(result, "Potentiometer value:\nvoltage: %u\npercent: %.3f\n", adc.voltage, percent);
            OledDrawString(result);
            OledUpdate();
            adc.event = FALSE;
        }
        
        //poll timer events and react if any occur
        if (timer1.event == TRUE) {

         
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
}

/**
 * This is the interrupt for the Timer1 peripheral.
 */
void __ISR(_TIMER_1_VECTOR, IPL4AUTO) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;
    
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


}

/**
 * This is the ISR for the ADC1 peripheral.
 */
void __ISR(_ADC_VECTOR, IPL2AUTO) AdcHandler(void)
{
    // Clear the interrupt flag.
    IFS1bits.AD1IF = 0;

    // calculate average of buffers
    float average = (ADC1BUF0 + ADC1BUF1 + ADC1BUF2 + ADC1BUF3 + ADC1BUF4 + ADC1BUF5 + ADC1BUF6 + ADC1BUF7) / 8.0;

    // if |average of buffers - current voltage| >= WINDOW or 
    if(abs(average - adc.voltage) > WINDOW ||  MAX_VOLTAGE - average < WINDOW || average < WINDOW){
        // voltage = |average|
        adc.voltage = abs(average);
        // event is true
        adc.event = TRUE;
    }

}