// Reuben Chavez
// May 25, 2022
// Spring 2022
#include "Field.h"
#include "BOARD.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>


#define two 2

/**
 * This function is optional, but recommended.   It prints a representation of both
 * fields, similar to the OLED display.
 * @param f The field to initialize.
 * @param p The data to initialize the entire field to, should be a member of enum
 *                     SquareStatus.
 */
void FieldPrint_UART(Field *own_field, Field *opp_field)
{
    printf("own feild\n");
    for (int r = 0; r < FIELD_ROWS; r++) {
        for (int c = 0; c < FIELD_COLS; c++) {
            printf("%u", own_field->grid[r][c]);
        }

        printf("\n");
        // make a new line in here
    }
    // make a new line to separate the matrix
    printf("opp feild\n");
    for (int r = 0; r < FIELD_ROWS; r++) {
        for (int c = 0; c < FIELD_COLS; c++) {
            printf("%u", opp_field->grid[r][c]);
        }
        // make a new line in here
        printf("\n");
    }

    return;
}

/**
 * FieldInit() will initialize two passed field structs for the beginning of play.
 * Each field's grid should be filled with the appropriate SquareStatus (
 * FIELD_SQUARE_EMPTY for your own field, FIELD_SQUARE_UNKNOWN for opponent's).
 * Additionally, your opponent's field's boatLives parameters should be filled
 *  (your own field's boatLives will be filled when boats are added)
 *
 * FieldAI_PlaceAllBoats() should NOT be called in this function.
 *
 * @param own_field     //A field representing the agents own ships
 * @param opp_field     //A field representing the opponent's ships
 */
void FieldInit(Field *own_field, Field *opp_field)
{
    // initlizes size for
    // own_field = (Field *)malloc(sizeof(Field));

    // iterate through grid in own_feild struct
    // and set to  FIELD_SQUARE_EMPTY
    for (int i = 0; i < FIELD_ROWS; i++) {
        for (int j = 0; j < FIELD_COLS; j++) {
            own_field->grid[i][j] = FIELD_SQUARE_EMPTY;
            opp_field->grid[i][j] = FIELD_SQUARE_UNKNOWN;
        }
    }

    // initializing opponent boat lives
    opp_field->smallBoatLives = FIELD_BOAT_SIZE_SMALL;
    opp_field->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
    opp_field->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
    opp_field->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;

    own_field->smallBoatLives = 0;
    own_field->mediumBoatLives = 0;
    own_field->largeBoatLives = 0;
    own_field->largeBoatLives = 0;

    return;
}

/**
 * Retrieves the value at the specified field position.
 * @param f     //The Field being referenced
 * @param row   //The row-component of the location to retrieve
 * @param col   //The column-component of the location to retrieve
 * @return  FIELD_SQUARE_INVALID if row and col are not valid field locations
 *          Otherwise, return the status of the referenced square
 */
SquareStatus FieldGetSquareStatus(const Field *f, uint8_t row, uint8_t col)
{
    if (row >= FIELD_ROWS || col >= FIELD_COLS) // should it still be correct when it's equal to row || column? like should (6,10) be valid?
    {
        return FIELD_SQUARE_INVALID;
    }

    return (SquareStatus) f->grid[row][col];
}

/**
 * This function provides an interface for setting individual locations within a Field struct. This
 * is useful when FieldAddBoat() doesn't do exactly what you need. For example, if you'd like to use
 * FIELD_SQUARE_CURSOR, this is the function to use.
 *
 * @param f The Field to modify.
 * @param row The row-component of the location to modify
 * @param col The column-component of the location to modify
 * @param p The new value of the field location
 * @return The old value at that field location
 */
SquareStatus FieldSetSquareStatus(Field *f, uint8_t row, uint8_t col, SquareStatus p)
{
    if (row >= FIELD_ROWS || col >= FIELD_COLS) // should it still be correct when it's equal to row || column? like should (6,10) be valid?
    {
        return FIELD_SQUARE_INVALID;
    }

    // save old value
    SquareStatus temp = (SquareStatus) f->grid[row][col];
    // store new value
    f->grid[row][col] = (uint8_t) p;
    return temp;
}

/**
 * FieldAddBoat() places a single ship on the player's field based on arguments 2-5. Arguments 2, 3
 * represent the x, y coordinates of the pivot point of the ship.  Argument 4 represents the
 * direction of the ship, and argument 5 is the length of the ship being placed.
 *
 * All spaces that
 * the boat would occupy are checked to be clear before the field is modified so that if the boat
 * can fit in the desired position, the field is modified as SUCCESS is returned. Otherwise the
 * field is unmodified and STANDARD_ERROR is returned. There is no hard-coded limit to how many
 * times a boat can be added to a field within this function.
 *
 * In addition, this function should update the appropriate boatLives parameter of the field.
 *
 * So this is valid test code:
 * {
 *   Field myField;
 *   FieldInit(&myField,FIELD_SQUARE_EMPTY);
 *   FieldAddBoat(&myField, 0, 0, FIELD_BOAT_DIRECTION_EAST, FIELD_BOAT_TYPE_SMALL);
 *   FieldAddBoat(&myField, 1, 0, FIELD_BOAT_DIRECTION_EAST, FIELD_BOAT_TYPE_MEDIUM);
 *   FieldAddBoat(&myField, 1, 0, FIELD_BOAT_DIRECTION_EAST, FIELD_BOAT_TYPE_HUGE);
 *   FieldAddBoat(&myField, 0, 6, FIELD_BOAT_DIRECTION_SOUTH, FIELD_BOAT_TYPE_SMALL);
 * }
 *
 * should result in a field like:
 *      0 1 2 3 4 5 6 7 8 9
 *     ---------------------
 *  0 [ 3 3 3 . . . 3 . . . ]
 *  1 [ 4 4 4 4 . . 3 . . . ]
 *  2 [ . . . . . . 3 . . . ]
 *  3 [ . . . . . . . . . . ]
 *  4 [ . . . . . . . . . . ]
 *  5 [ . . . . . . . . . . ]
 *
 * @param f The field to grab data from.
 * @param row The row that the boat will start from, valid range is from 0 and to FIELD_ROWS - 1.
 * @param col The column that the boat will start from, valid range is from 0 and to FIELD_COLS - 1.
 * @param dir The direction that the boat will face once places, from the BoatDirection enum.
 * @param boatType The type of boat to place. Relies on the FIELD_SQUARE_*_BOAT values from the
 * SquareStatus enum.
 * @return SUCCESS for success, STANDARD_ERROR for failure
 */
uint8_t FieldAddBoat(Field *own_field, uint8_t row, uint8_t col, BoatDirection dir, BoatType boat_type)
{

    BoatSize size; // to determine how mant times to iterate
    SquareStatus sqStatus; // to set status in feild
    SquareStatus exit; // to determine if the FeildSqaure staus runned succefully or not

    // depending on boat types
    switch (boat_type) {
    case FIELD_BOAT_TYPE_SMALL:
        // save boat size
        size = FIELD_BOAT_SIZE_SMALL;
        // save sqare status
        sqStatus = FIELD_SQUARE_SMALL_BOAT;
        // initilize status for boat to be alive
        break;
    case FIELD_BOAT_TYPE_MEDIUM:
        size = FIELD_BOAT_SIZE_MEDIUM;
        sqStatus = FIELD_SQUARE_MEDIUM_BOAT;
        break;
    case FIELD_BOAT_TYPE_LARGE:
        size = FIELD_BOAT_SIZE_LARGE;
        sqStatus = FIELD_SQUARE_LARGE_BOAT;
        break;
    case FIELD_BOAT_TYPE_HUGE:
        size = FIELD_BOAT_SIZE_HUGE;
        sqStatus = FIELD_SQUARE_HUGE_BOAT;
        break;
    }
    // check before hand
    for (uint8_t i = 0; i < size; i++) {
        if (FieldGetSquareStatus(own_field, row + i, col) != FIELD_SQUARE_EMPTY  && dir == FIELD_DIR_SOUTH) {
            return STANDARD_ERROR;
        } else if (FieldGetSquareStatus(own_field, row, col + i) != FIELD_SQUARE_EMPTY && dir == FIELD_DIR_EAST) {
            return STANDARD_ERROR;
        }
    }

    // for  i from 0 to boat size
    for (uint8_t bs = 0; bs < size; bs++) {

        // if the space is empty and dir is south
        if (FieldGetSquareStatus(own_field, row + bs, col) == FIELD_SQUARE_EMPTY && dir == FIELD_DIR_SOUTH) {
            //  add onto field[row][col] = SquareStatus of Boat
            FieldSetSquareStatus(own_field, row + bs, col, sqStatus);
        }

        // if space is empty and dir is south
        if (FieldGetSquareStatus(own_field, row, col + bs) == FIELD_SQUARE_EMPTY && dir == FIELD_DIR_EAST) {
            FieldSetSquareStatus(own_field, row, col + bs, sqStatus);
        }

    }

    // depending on boat types
    switch (boat_type) {
    case FIELD_BOAT_TYPE_SMALL:

        // initilize status for boat to be alive
        own_field->smallBoatLives = FIELD_BOAT_SIZE_SMALL;

        // sva boat status
        break;
    case FIELD_BOAT_TYPE_MEDIUM:

        own_field->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
        break;
    case FIELD_BOAT_TYPE_LARGE:

        own_field->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
        break;
    case FIELD_BOAT_TYPE_HUGE:

        own_field->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;
        break;
    }
    // return once completed
    return SUCCESS;
}

/**
 * This function registers an attack at the gData coordinates on the provided field. This means that
 * 'f' is updated with a FIELD_SQUARE_HIT or FIELD_SQUARE_MISS depending on what was at the
 * coordinates indicated in 'gData'. 'gData' is also updated with the proper HitStatus value
 * depending on what happened AND the value of that field position BEFORE it was attacked. Finally
 * this function also reduces the lives for any boat that was hit from this attack.
 * @param f The field to check against and update.
 * @param gData The coordinates that were guessed. The result is stored in gData->result as an
 *               output.  The result can be a RESULT_HIT, RESULT_MISS, or RESULT_***_SUNK.
 * @return The data that was stored at the field position indicated by gData before this attack.
 */

SquareStatus FieldRegisterEnemyAttack(Field *own_field, GuessData *opp_guess)
{
    SquareStatus space = own_field->grid[opp_guess->row][opp_guess->col];
    switch (space) {
    case FIELD_SQUARE_EMPTY:
        opp_guess->result = RESULT_MISS;
        FieldSetSquareStatus(own_field, opp_guess->row, opp_guess->col, RESULT_MISS);
        break;
    case FIELD_SQUARE_SMALL_BOAT:
        // if boat alive
        if (own_field->smallBoatLives > 1) {
            // decrement life
            own_field->smallBoatLives--;
            // set opp_guess to result hit
            opp_guess->result = RESULT_HIT;
            break;
        }
        own_field->smallBoatLives--;
        opp_guess->result = RESULT_SMALL_BOAT_SUNK;
        break;
        
        FieldSetSquareStatus(own_field, opp_guess->row, opp_guess->col, RESULT_HIT);

        break;
    case FIELD_SQUARE_MEDIUM_BOAT:
        if (own_field->mediumBoatLives > 1) {
            own_field->mediumBoatLives--;
            opp_guess->result = RESULT_HIT;
            break;
        }
        own_field->mediumBoatLives--;
        opp_guess->result = RESULT_MEDIUM_BOAT_SUNK;
        break;
    case FIELD_SQUARE_LARGE_BOAT:
        if (own_field->largeBoatLives > 1) {
            own_field->largeBoatLives--;
            opp_guess->result = RESULT_HIT;
            break;
        }
        own_field->largeBoatLives--;
        opp_guess->result = RESULT_LARGE_BOAT_SUNK;
        break;
    case FIELD_SQUARE_HUGE_BOAT:
        if (own_field->hugeBoatLives > 1) {
            own_field->hugeBoatLives--;
            opp_guess->result = RESULT_HIT;
            break;
        }
        own_field->hugeBoatLives--;
        opp_guess->result = RESULT_HUGE_BOAT_SUNK;
        break;
    }
    return space;
}

/**
 * This function updates the FieldState representing the opponent's game board with whether the
 * guess indicated within gData was a hit or not. If it was a hit, then the field is updated with a
 * FIELD_SQUARE_HIT at that position. If it was a miss, display a FIELD_SQUARE_EMPTY instead, as
 * it is now known that there was no boat there. The FieldState struct also contains data on how
 * many lives each ship has. Each hit only reports if it was a hit on any boat or if a specific boat
 * was sunk, this function also clears a boats lives if it detects that the hit was a
 * RESULT_*_BOAT_SUNK.
 * @param f The field to grab data from.
 * @param gData The coordinates that were guessed along with their HitStatus.
 * @return The previous value of that coordinate position in the field before the hit/miss was
 * registered.
 */
SquareStatus FieldUpdateKnowledge(Field *opp_field, const GuessData *own_guess)
{
    SquareStatus space = FieldGetSquareStatus(opp_field, own_guess->row, own_guess->col);
    // if the result is a miss then
    
    if (own_guess->result == RESULT_MISS) { 
        // set feild status to miss
        FieldSetSquareStatus(opp_field, own_guess->row, own_guess->col, FIELD_SQUARE_MISS); // this should be FIELD_SQUARE_EMPTY
        // return space
        return space;
    }

    // else set stauts to hit
    FieldSetSquareStatus(opp_field, own_guess->row, own_guess->col, FIELD_SQUARE_HIT);

    // Depending on result
    // set small boat live to zero if sunk
    switch (own_guess->result) {
    case RESULT_SMALL_BOAT_SUNK:
        opp_field->smallBoatLives = 0;
        break;

    case RESULT_MEDIUM_BOAT_SUNK:
        opp_field->mediumBoatLives = 0;
        break;

    case RESULT_LARGE_BOAT_SUNK:
        opp_field->largeBoatLives = 0;
        break;

    case RESULT_HUGE_BOAT_SUNK:
        opp_field->hugeBoatLives = 0;
        break;
    }
    return space;
}

/**
 * This function returns the alive states of all 4 boats as a 4-bit bitfield (stored as a uint8).
 * The boats are ordered from smallest to largest starting at the least-significant bit. So that:
 * 0b00001010 indicates that the small boat and large boat are sunk, while the medium and huge boat
 * are still alive. See the BoatStatus enum for the bit arrangement.
 * @param f The field to grab data from.
 * @return A 4-bit value with each bit corresponding to whether each ship is alive or not.
 */
uint8_t FieldGetBoatStates(const Field *f)
{
    uint8_t alive = 0;

    if (f->smallBoatLives) {
        alive |= FIELD_BOAT_STATUS_SMALL;
    }

    if (f->mediumBoatLives) {
        alive |= FIELD_BOAT_STATUS_MEDIUM;
    }

    if (f->largeBoatLives) {
        alive |= FIELD_BOAT_STATUS_LARGE;
    }

    if (f->hugeBoatLives) {
        alive |= FIELD_BOAT_STATUS_HUGE;
    }

    return alive;
}

/**
 * This function is responsible for placing all four of the boats on a field.
 *
 * @param f         //agent's own field, to be modified in place.
 * @return SUCCESS if all boats could be placed, STANDARD_ERROR otherwise.
 *
 * This function should never fail when passed a properly initialized field!
 */
uint8_t FieldAIPlaceAllBoats(Field *own_field)
{
    // initialze varible to starter boat type
    BoatType bt = FIELD_BOAT_TYPE_SMALL;
    BoatDirection dir;

    uint8_t row;
    uint8_t col;

    uint8_t small_plcaed;

    uint8_t check;
    while (1) {

        // create random direction
        dir = rand() % two;
        // choose random Feild Row
        row = rand() % FIELD_ROWS;
        // choose random Feild cos
        col = rand() % FIELD_COLS;

        switch (bt) {
        case FIELD_BOAT_TYPE_SMALL:
            check = FieldAddBoat(own_field, row, col, dir, bt);

            // until boat is succefully addd to grid
            if (check == SUCCESS) {
                // switch to next boat type
                bt = FIELD_BOAT_TYPE_MEDIUM;
            }
            // repeat for other boats

            break;
        case FIELD_BOAT_TYPE_MEDIUM:

            check = FieldAddBoat(own_field, row, col, dir, bt);

            if (check == SUCCESS) {
                bt = FIELD_BOAT_TYPE_LARGE;
            }

            break;
        case FIELD_BOAT_TYPE_LARGE:
            check = FieldAddBoat(own_field, row, col, dir, bt);

            if (check == SUCCESS) {
                bt = FIELD_BOAT_TYPE_HUGE;
            }

            break;
        case FIELD_BOAT_TYPE_HUGE:
            check = FieldAddBoat(own_field, row, col, dir, bt);
            if (check == SUCCESS) {
                // return success
                return SUCCESS;
            }
            break;
        }
    }
}

/**
 * Given a field, decide the next guess.
 *
 * This function should not attempt to shoot a square which has already been guessed.
 *
 * You may wish to give this function static variables.  If so, that data should be
 * reset when FieldInit() is called.
 *
 * @param f an opponent's field.
 * @return a GuessData struct whose row and col parameters are the coordinates of the guess.  The
 *           result parameter is irrelevant.
 */
GuessData FieldAIDecideGuess(const Field *opp_field)
{
    while (1) {
        // create radndom row and col
        uint8_t row = rand() % FIELD_ROWS;
        uint8_t col = rand() % FIELD_COLS;

        // if the status on the feild coordinate is unknown
        if (FieldGetSquareStatus(opp_field, row, col) == FIELD_SQUARE_UNKNOWN) {
            // creat guess data with stored coordinate
            GuessData guess = {row, col};
            // return guess data
            return guess;
        }
    }
}

/**
 * For Extra Credit:  Make the two "AI" functions above
 * smart enough to beat our AI in more than 55% of games.
 */
