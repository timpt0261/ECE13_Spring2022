// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

// CSE13E Support Library
#include "Adc.h"
#include "Ascii.h"
#include "BOARD.h"
#include "Buttons.h"
#include "Leds.h"
#include "Oled.h"
// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>
#include <stdint.h>

// **** Set any macros or preprocessor directives here ****
// Set a macro for resetting the timer, makes the code a little clearer.
#define TIMER_2HZ_RESET() (TMR1 = 0)

#define MIN_TIME 0
#define MAX_TIME 256

#define MIN_TEMP 300
#define MAX_TEMP 555

#define OVEN_TEMP 350
#define BROILER_TEMP 500

#define SECOND 5
#define LONG_PRESS SECOND

// **** Set any local typedefs here ****

typedef enum {
    SETUP,
    SELECTOR_CHANGE_PENDING,
    COOKING,
    RESET_PENDING
} OvenState;

typedef enum {
    BAKE = 0,
    TOAST,
    BROIL
} CookingMode;

typedef enum {
    TEMP = 0,
    TIME
} SelectorSetting;

typedef struct {
    // stores state of oven
    OvenState state;
    // stores mode of oven [Bake, Toast, Broil]
    CookingMode mode;
    // stores which selector
    SelectorSetting setter;
    // how much time is left cooking
    uint16_t cooking_time_left;
    // initial cooking time
    uint16_t init_cook_time;
    // initial temperature
    uint16_t temp;

} OvenData;

// **** Declare any datatypes here ****

// event flags for ISR
static uint16_t eventFlag;
static uint16_t TIMER_TICK;

static uint16_t interval; // since time * 8

static uint16_t button_press; // used to determine how long button is pressed(elapsed time)
static uint16_t startTime; // stores instance of free-running time when called
static uint16_t free_run_timer; // free running timer

static uint8_t buttonCheck; // initialize ButtonCheckEvents()
static uint8_t adcChange; // initialize AdcChange()

static OvenData o_data; // static instance of OvenData

// **** Define any module-level, global, or external variables here ****

// determines if the button is being pressed for a period of time

// **** Put any helper functions here ****

/*This function will update your OLED to reflect the state .*/
void updateOvenOLED(OvenData ovenData) {
    char ovenUI[100]; // Stores result

    char mode[10];
    char str1[100]; // stores first string
    char str2[100]; // stores second string
    char str3[100]; // stores third string
    char str4[100]; // stores fourth string

    // oven off
    uint16_t oven_off = ovenData.state == SETUP || ovenData.state == SELECTOR_CHANGE_PENDING;
    // oven on
    uint16_t oven_on = ovenData.state == COOKING || ovenData.state == RESET_PENDING;

    // calculates minutes
    uint16_t min = ovenData.init_cook_time / 60;
    // calculates second
    uint16_t sec = ovenData.init_cook_time % 60;

    // when OvenOn min, sec calculated by cooking time left
    if (oven_on) {
        min = ovenData.cooking_time_left / 60;
        sec = ovenData.cooking_time_left % 60;
    }

    // update OLED here
    OledClear(OLED_COLOR_BLACK);
    switch (ovenData.mode) {
        case BAKE:
            sprintf(mode, "BAKE");
            if (ovenData.setter == TIME) {

                sprintf(str2, "|    | >TIME: %02d:%02d", min, sec);
                sprintf(str3, "|----| TEMP: %d%s", ovenData.temp, DEGREE_SYMBOL);
            } else if (ovenData.setter == TEMP) {

                sprintf(str2, "|    | TIME: %02d:%02d", min, sec);
                sprintf(str3, "|----| >TEMP: %d%s", ovenData.temp, DEGREE_SYMBOL);
            }

            break;
        case TOAST:
            sprintf(mode, "TOAST");
            sprintf(str2, "|    | TIME: %02d:%02d", min, sec);
            sprintf(str3, "|----|", ovenData.temp, DEGREE_SYMBOL);

            break;
        case BROIL:
            sprintf(mode, "BROIL");
            sprintf(str2, "|    | TIME: %02d:%02d", min, sec);
            sprintf(str3, "|----| TEMP: %d%s", ovenData.temp, DEGREE_SYMBOL);
            break;
    }

    if (oven_on) {
        min = ovenData.cooking_time_left / 60;
        sec = ovenData.cooking_time_left % 60;

        sprintf(str1, "|%s%s%s%s| Mode: %s", OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, mode);

        sprintf(str4, "|%s%s%s%s|", OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON);
    } else if (oven_off) {

        sprintf(str1, "|%s%s%s%s| Mode: %s", OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, mode);

        sprintf(str4, "|%s%s%s%s|", OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
    }

    sprintf(ovenUI, "%s\n%s\n%s\n%s\n", str1, str2, str3, str4);
    OledDrawString(ovenUI);
    OledUpdate();
}

/*This function will execute your state machine.
 * It should ONLY run if an event flag has been set.*/
void runOvenSM(void) {
    switch (o_data.state) {
        case SETUP:
            // update OLED with adc
            if (adcChange) {
                // Get ADC from point-ometer
                uint16_t read_adc = AdcRead();
                if (o_data.setter == TIME) {

                    read_adc = (read_adc >> 2) + 1; //  Get top 8 bits
                    // change initial cooking time
                    o_data.init_cook_time = read_adc <= 256 ? read_adc : 256; // check it doesn't pass 4:16
                } else if (o_data.setter == TEMP) {
                    read_adc = (read_adc >> 2) + 300;

                    // checks in the case adc < 300 , set to 300
                    read_adc = read_adc < MIN_TEMP ? MIN_TEMP : read_adc;
                    // checks in the case adc > 555 , set to 500
                    read_adc = read_adc > MAX_TEMP ? MAX_TEMP : read_adc;

                    // sets OvenData temp to read_adc
                    o_data.temp = read_adc;

                    updateOvenOLED(o_data);
                }
            }
            // if btn event 3_DOWN
            if (buttonCheck & BUTTON_EVENT_3DOWN) {

                // store free running time
                startTime = free_run_timer;

                // od.state = Selector_Pending
                o_data.state = SELECTOR_CHANGE_PENDING;
            }
            // if btn event 4down
            if (buttonCheck & BUTTON_EVENT_4DOWN) {

                // store free running time
                startTime = free_run_timer;
                interval = o_data.init_cook_time << 3; // cook_time * 8
                o_data.cooking_time_left = o_data.init_cook_time;
                // update LED bar
                LEDS_SET(0xFF);
                // state = cooking
                o_data.state = COOKING;

                updateOvenOLED(o_data);
            }
            updateOvenOLED(o_data);
            break;
        case SELECTOR_CHANGE_PENDING:
            // if btn 3 event_up
            if (buttonCheck & BUTTON_EVENT_3UP) {

                button_press = free_run_timer - startTime;
                // if press < long pressed
                if (button_press < LONG_PRESS) {
                    // switch to next mode
                    if (o_data.mode == BAKE) {
                        o_data.mode = TOAST;
                        o_data.temp = MIN_TEMP;
                        ;
                        updateOvenOLED(o_data);
                        o_data.state = SETUP;
                    } else if (o_data.mode == TOAST) {
                        o_data.mode = BROIL;
                        o_data.temp = BROILER_TEMP; // doesn't really matter
                        o_data.setter = TIME;
                        updateOvenOLED(o_data);
                        o_data.state = SETUP;
                    } else if (o_data.mode == BROIL) {
                        o_data.mode = BAKE;
                        o_data.temp = OVEN_TEMP;
                        o_data.setter = TIME;
                        updateOvenOLED(o_data);
                        o_data.state = SETUP;
                    }

                    // update OLED
                } else if (button_press >= LONG_PRESS && o_data.mode == BAKE) {
                    if (o_data.mode == BAKE) {
                        // Change setting selector
                        if (o_data.setter == TIME) {

                            o_data.setter = TEMP;


                            updateOvenOLED(o_data);
                            o_data.state = SETUP;
                            break;
                        } else {
                            o_data.setter = TIME;


                            updateOvenOLED(o_data);
                            o_data.state = SETUP;
                        }
                    }
                } else {
                    o_data.state = SETUP;
                    updateOvenOLED(o_data);
                }
            }

            updateOvenOLED(o_data);
            break;
        case COOKING:
            // if btn4_even_4down
            if (buttonCheck & BUTTON_EVENT_4DOWN) {
                // store free running time
                startTime = free_run_timer;
                //  state = Reset pending
                o_data.state = RESET_PENDING;
            }

            // if TIMER_TICK
            if (TIMER_TICK) {
                // if time == 2
                if (o_data.cooking_time_left <= 2) {
                    // display inverted
                    OledSetDisplayInverted();
                }

                // if cook time > 0
                if (o_data.cooking_time_left > 0) {
                    // if sec passes
                    if (((free_run_timer - o_data.cooking_time_left) % SECOND) == 0) {
                        // update LED
                        // if 1/8 time passes
                        if ((interval % o_data.init_cook_time) == 0) {
                            // should decrement if 1/8 time
                            LEDS_SET(LEDS_GET() << 1);
                        }
                        o_data.cooking_time_left--;
                        interval -= 8;
                    }
                    // update OLED
                    updateOvenOLED(o_data);
                } else {
                    // reset setting
                    OledSetDisplayNormal();
                    // set timer to initial cooktime
                    o_data.cooking_time_left = o_data.init_cook_time;
                    // turn off leds
                    LEDS_SET(0x00);

                    // state = SETUP
                    o_data.state = SETUP;

                    // update OLED
                    updateOvenOLED(o_data);
                }
            }

            break;
        case RESET_PENDING:
            // if btn 4 event up
            if (buttonCheck & BUTTON_EVENT_4UP) {
                // state = Cooking
                o_data.state = COOKING;
            }

            // if TIMER_TICK
            if (TIMER_TICK) {
                button_press = free_run_timer - startTime;
                // if elapsed_time >= Long Press
                if (button_press >= LONG_PRESS) {
                    // end cooking
                    // reset settings
                    OledSetDisplayNormal();
                    // Update LED Bar
                    LEDS_SET(0x00);

                    // state  = setup
                    o_data.state = SETUP;

                    // update OLED
                    updateOvenOLED(o_data);
                } else {

                    // update LED bar
                    LEDS_SET(LEDS_GET());

                    // update OLED
                    updateOvenOLED(o_data);
                }
            }
            break;
    }
}

int main() {
    BOARD_Init();

    // initalize timers and timer ISRs:
    //  <editor-fold defaultstate="collapsed" desc="TIMER SETUP">

    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.

    T2CON = 0; // everything should be off
    T2CONbits.TCKPS = 0b100; // 1:16 prescaler
    PR2 = BOARD_GetPBClock() / 16 / 100; // interrupt at .5s intervals
    T2CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T2IF = 0; // clear the interrupt flag before configuring
    IPC2bits.T2IP = 4; // priority of  4
    IPC2bits.T2IS = 0; // subpriority of 0 arbitrarily
    IEC0bits.T2IE = 1; // turn the interrupt on

    // Configure Timer 3 using PBCLK as input. We configure it using a 1:256 prescaler, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR3 to F_PB / 256 / 5 yields a .2s timer.

    T3CON = 0; // everything should be off
    T3CONbits.TCKPS = 0b111; // 1:256 prescaler
    PR3 = BOARD_GetPBClock() / 256 / 5; // interrupt at .5s intervals
    T3CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T3IF = 0; // clear the interrupt flag before configuring
    IPC3bits.T3IP = 4; // priority of  4
    IPC3bits.T3IS = 0; // subpriority of 0 arbitrarily
    IEC0bits.T3IE = 1; // turn the interrupt on;

    // </editor-fold>

    printf("Welcome to rtchavez's Lab07 (Toaster Oven).  Compiled on %s %s.", __TIME__, __DATE__);

    // initialize state machine (and anything else you need to init) here
    OledInit();
    ButtonsInit();
    AdcInit();
    LEDS_INIT();

    o_data.state = SETUP;
    o_data.mode = BAKE;
    o_data.temp = OVEN_TEMP;
    o_data.setter = TIME;

    // Add main loop code here:
    while (1) {
        eventFlag = TRUE;
        // check for events
        if (eventFlag == TRUE) {
            // on event, run runOvenSM()
            runOvenSM();
        }
        // clear event flags
        eventFlag = FALSE;
    }
}

/*The 5hz timer is used to update the free-running timer and to generate TIMER_TICK events*/
void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void) {
    // Clear the interrupt flag.
    IFS0CLR = 1 << 12;

    TIMER_TICK = TRUE;
    free_run_timer++;
}

/*The 100hz timer is used to check for button and ADC events*/
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void) {
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;

    // add event-checking code here
    if (eventFlag == TRUE) {
        adcChange = AdcChanged();
        buttonCheck = ButtonsCheckEvents();
    }
}
