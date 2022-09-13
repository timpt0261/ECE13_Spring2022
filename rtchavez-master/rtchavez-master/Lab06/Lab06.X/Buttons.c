/*
 * Author: Reuben Chavez
 * Date : 5/2/2022
 * Spring 2022
 */

// Libraries
#include <stdint.h>
#include <stdio.h>
#include <genericTypeDefs.h>
#include "BOARD.h" 

#include "Buttons.h"

// stores the previous state of the BUTTON_STATE
static uint8_t previous;
// stores the debounce
static uint8_t debounce;

/*
 * This function initializes the proper pins such that the buttons 1-4 may be used by modifying
 * the necessary bits in TRISD/TRISF. Only the bits necessary to enable the 1-4 buttons are
 * modified, so that this library does not interfere with other libraries.
 */
void ButtonsInit(void) {
    // Initlaize proper use of pins
    TRISD |= 0x00E0;
    TRISF |= 0x0002;

    debounce = 0; // initalizing previous to debounce
    previous = 0x00;


}

/**
 * ButtonsCheckEvents function checks the current button states and returns
 *  any events that have occured since its last
 * call.  This function should be called repeatedly in a Timer ISR, though it can
 * be called in main() during testing.
 *
 * In normal use, this function should only be used after ButtonsInit().
 * 
 * This function should assume that the buttons start in an off state with 
 * value 0. Therefore if no buttons are
 * pressed when ButtonsCheckEvents() is first called, 
 * BUTTONS_EVENT_NONE should be returned. 
 * 
 * @return  Each bit of the return value corresponds to one ButtonEvent flag,
 *          as described in Buttons.h.  If no events are detected, BUTTONS_EVENT_NONE is returned.
 * 
 * Note that more than one event can occur simultaneously, though this situation is rare.
 * To handle this, the output should be a bitwise OR of all applicable event flags. 
 * For example, if button 1 was released at the same time that button 2 was pressed,
 * this function should return (BUTTON_EVENT_1UP | BUTTON_EVENT_2DOWN) 
 * 
 */
uint8_t ButtonsCheckEvents(void) {
    // Attended Online Section on 5-6-22
    uint8_t buttonPress = BUTTON_EVENT_NONE;
    uint8_t buttonsState = BUTTON_STATES();

    if (debounce > 0) {
        debounce--;
        return buttonPress;
    }
    
    // case the previous state is the same 
    if (buttonsState == previous) {
        return BUTTON_EVENT_NONE;
    }
    
    // check fourth bit of the buttonState
    if ((buttonsState & BUTTON_STATE_4) && (BUTTON_STATE_4 & previous) == 0x00) {

        buttonPress |= BUTTON_EVENT_4DOWN;

    } else if (!(buttonsState & BUTTON_STATE_4) && previous & BUTTON_STATE_4) {

        buttonPress |= BUTTON_EVENT_4UP;
    }

    // check third bit of the buttonState
    if ((buttonsState & BUTTON_STATE_3) && (previous & BUTTON_STATE_3) == 0x00) {

        buttonPress |= BUTTON_EVENT_3DOWN;

    } else if (!(buttonsState & BUTTON_STATE_3) && previous & BUTTON_STATE_3) {

        buttonPress |= BUTTON_EVENT_3UP;
    }
    // check second bit of the buttonState
    if ((buttonsState & BUTTON_STATE_2) && (previous & BUTTON_STATE_2) == 0x00) {
        buttonPress |= BUTTON_EVENT_2DOWN;

    } else if (!(buttonsState & BUTTON_STATE_2) && previous & BUTTON_STATE_2) {

        buttonPress |= BUTTON_EVENT_2UP;
    }

    // check first bit of the buttonState
    if ((buttonsState & BUTTON_STATE_1) && (previous & BUTTON_STATE_1) == 0x00) {
        buttonPress |= BUTTON_EVENT_1DOWN;

    } else if (!(buttonsState & BUTTON_STATE_1) && previous & BUTTON_STATE_1) {

        buttonPress |= BUTTON_EVENT_1UP;
    }

    debounce = BUTTONS_DEBOUNCE_PERIOD;
    previous = buttonsState;

    return buttonPress;
}