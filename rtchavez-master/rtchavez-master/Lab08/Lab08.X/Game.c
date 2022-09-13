// Reuben Chavez
// ECE 13E Spring

#include "Game.h"
#include "UNIXBOARD.h"
#include "Player.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct
{
    FILE *room_file;

    char title[GAME_MAX_ROOM_TITLE_LENGTH];
    char desc[GAME_MAX_ROOM_DESC_LENGTH];

    uint8_t title_size;
    uint8_t desc_size;

    uint8_t north;
    uint8_t east;
    uint8_t south;
    uint8_t west;

} GameRoom;

// determinses where fseek should start after function

// helper function
int ParseFile(int room_num)
{
    char path[100];
    sprintf(path, "RoomFiles/room%u.txt", room_num);

    // open file
    GameRoom.room_file = fopen(path, "rb");

    // if fille is null
    if (GameRoom.room_file == NULL)
    {
        // then return Standard error
        return STANDARD_ERROR;
    }

    /*
     *   Parses through file where the title of the room
     */

    // skips over RPG
    fseek(GameRoom.room_file, 3, SEEK_SET);
    // set title_size to get next integer
    GameRoom.title_size = (uint8_t)fgetc(GameRoom.room_file);
    // copy contents to title
    fread(GameRoom.title, sizeof(char), GameRoom.title_size, GameRoom.room_file);
    GameRoom.title[GameRoom.title_size] = '\0';

    /* Parse in file where the items
     *  and item required length are
     */

    // num with item req length
    uint8_t item_size = (uint8_t)fgetc(GameRoom.room_file);

    uint8_t count = 0; // used to dwtermine if all item_req were found
    // for item_req_lenthh determine if item in player inventory
    for (uint8_t i = 0; i < item_size; i++)
    {
        if (FindInInventory((uint8_t)fgetc(GameRoom.room_file)) == SUCCESS)
        {
            count++;
        }
    }

    /* Determine which Description to go to depending
     * on the item requried
     */

    // if items required go to specified description
    if (count == item_size)
    {
        // desc_size stored
        GameRoom.desc_size = (uint8_t)fgetc(GameRoom.room_file);
    }
    else
    {
        // else set offset to second version
        GameRoom.desc_size = (uint8_t)fgetc(GameRoom.room_file);
        // offset skip first description
        fseek(GameRoom.room_file, GameRoom.desc_size + 6, SEEK_CUR);

        // should be offseted to get second desc length
        GameRoom.desc_size = (uint8_t)fgetc(GameRoom.room_file);
    }

    // // copy description into desc
    fread(GameRoom.desc, sizeof(char), GameRoom.desc_size, GameRoom.room_file);
    GameRoom.desc[GameRoom.desc_size] = '\0';

    uint8_t contained_length = (uint8_t)fgetc(GameRoom.room_file);

    // for contained items in list go forward add to inventory
    for (uint8_t i = 0; i < contained_length; i++)
    {
        uint8_t item = fgetc(GameRoom.room_file);
        if (item)
        {
            AddToInventory(item);
        }
    }

    // offset = rpg + (title_size + title) + (item_size + items_req) +
    //           (desc_length + desc) + (num_of items_contained + item_contained)

    // store N,E,S,W game room num in struct

    GameRoom.north = (uint8_t)fgetc(GameRoom.room_file);
    GameRoom.east = (uint8_t)fgetc(GameRoom.room_file);
    GameRoom.south = (uint8_t)fgetc(GameRoom.room_file);
    GameRoom.west = (uint8_t)fgetc(GameRoom.room_file);

    fclose(GameRoom.room_file);
    return SUCCESS;
}

/**
 * These function transitions between rooms. Each call should return SUCCESS if the current room has
 * an exit in the correct direction and the new room was able to be loaded, and STANDARD_ERROR
 * otherwise.
 * @return SUCCESS if the room CAN be navigated to and changing the current room to that new room
 *         succeeded.
 */
int GameGoNorth(void)
{
    uint8_t getCurrentExit = GameGetCurrentRoomExits();

    if (getCurrentExit & GAME_ROOM_EXIT_NORTH_EXISTS)
    {
        GameRoom.title_size = 0;
        GameRoom.desc_size = 0;
        strcpy(GameRoom.title, "");
        strcpy(GameRoom.desc, "");  
        
        ParseFile(GameRoom.north);
        return GameRoom.room_file == NULL ? STANDARD_ERROR : SUCCESS;
    }

    return STANDARD_ERROR;
}

int GameGoEast(void)
{
    uint8_t getCurrentExit = GameGetCurrentRoomExits();

    if (getCurrentExit & GAME_ROOM_EXIT_EAST_EXISTS)
    {
        GameRoom.title_size = 0;
        GameRoom.desc_size = 0;
        strcpy(GameRoom.title, "");
        strcpy(GameRoom.desc, "");

        ParseFile(GameRoom.east);
        return GameRoom.room_file == NULL ? STANDARD_ERROR : SUCCESS;
    }

    return STANDARD_ERROR;
}

int GameGoSouth(void)
{
    uint8_t getCurrentExit = GameGetCurrentRoomExits();

    if (getCurrentExit & GAME_ROOM_EXIT_SOUTH_EXISTS)
    {
        GameRoom.title_size = 0;
        GameRoom.desc_size = 0;
        strcpy(GameRoom.title, "");
        strcpy(GameRoom.desc, "");

        ParseFile(GameRoom.south);
        return GameRoom.room_file == NULL ? STANDARD_ERROR : SUCCESS;
    }

    return STANDARD_ERROR;
}

int GameGoWest(void)
{
    uint8_t getCurrentExit = GameGetCurrentRoomExits();

    if (getCurrentExit & GAME_ROOM_EXIT_WEST_EXISTS)
    {
        GameRoom.title_size = 0;
        GameRoom.desc_size = 0;
        strcpy(GameRoom.title, "");
        strcpy(GameRoom.desc, "");

        ParseFile(GameRoom.west);
        return GameRoom.room_file == NULL ? STANDARD_ERROR : SUCCESS;
    }

    return STANDARD_ERROR;
}

/**
 * This function sets up anything that needs to happen at the start of the game. This is just
 * setting the current room to STARTING_ROOM and loading it. It should return SUCCESS if it succeeds
 * and STANDARD_ERROR if it doesn't.
 * @return SUCCESS or STANDARD_ERROR
 */
int GameInit(void)
{
    // parse  the starting room file
    return ParseFile(STARTING_ROOM) == SUCCESS? SUCCESS : STANDARD_ERROR;
}

/**
 * Copies the current room title as a NULL-terminated string into the provided character array.
 * Only a NULL-character is copied if there was an error so that the resultant output string
 * length is 0.
 * @param title A character array to copy the room title into. Should be GAME_MAX_ROOM_TITLE_LENGTH+1
 *             in length in order to allow for all possible titles to be copied into it.
 * @return The length of the string stored into `title`. Note that the actual number of chars
 *         written into `title` will be this value + 1 to account for the NULL terminating
 *         character.
 */
int GameGetCurrentRoomTitle(char *title)
{
    strcpy(title,GameRoom.title);

    return GameRoom.title_size;
}

/**
 * GetCurrentRoomDescription() copies the description of the current room into the argument desc as
 * a C-style string with a NULL-terminating character. The room description is guaranteed to be less
 * -than-or-equal to GAME_MAX_ROOM_DESC_LENGTH characters, so the provided argument must be at least
 * GAME_MAX_ROOM_DESC_LENGTH + 1 characters long. Only a NULL-character is copied if there was an
 * error so that the resultant output string length is 0.
 * @param desc A character array to copy the room description into.
 * @return The length of the string stored into `desc`. Note that the actual number of chars
 *          written into `desc` will be this value + 1 to account for the NULL terminating
 *          character.
 */
int GameGetCurrentRoomDescription(char *desc)
{
    // look in string for GAME_MAX_ROOM_DESC_LENGTH long to get description
    strcpy(desc, GameRoom.desc);

    return GameRoom.desc_size;
}

/**
 * This function returns the exits from the current room in the lowest-four bits of the returned
 * uint8 in the order of NORTH, EAST, SOUTH, and WEST such that NORTH is in the MSB and WEST is in
 * the LSB. A bit value of 1 corresponds to there being a valid exit in that direction and a bit
 * value of 0 corresponds to there being no exit in that direction. The GameRoomExitFlags enum
 * provides bit-flags for checking the return value.
 *
 * @see GameRoomExitFlags
 *
 * @return a 4-bit bitfield signifying which exits are available to this room.
 */
uint8_t GameGetCurrentRoomExits(void)
{
    uint8_t exits = 0; // stores all exits

    // set postion near end of file

    // if north not zero
    if (GameRoom.north)
    {
        // bitsise OR that North exist
        exits |= GAME_ROOM_EXIT_NORTH_EXISTS;
    }

    if (GameRoom.east)
    {
        exits |= GAME_ROOM_EXIT_EAST_EXISTS;
    }

    if (GameRoom.south)
    {
        exits |= GAME_ROOM_EXIT_SOUTH_EXISTS;
    }

    if (GameRoom.west)
    {
        exits |= GAME_ROOM_EXIT_WEST_EXISTS;
    }

    return exits;
}