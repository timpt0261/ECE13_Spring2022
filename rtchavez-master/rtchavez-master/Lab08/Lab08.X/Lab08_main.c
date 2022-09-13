// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>

// CSE013E Support Library
#include "UNIXBOARD.h"

// User libraries
#include "Game.h"

// **** Set any macros or preprocessor directives here ****

// **** Declare any data types here ****

// **** Define any global or external variables here ****
typedef struct Printing
{
    char title[GAME_MAX_ROOM_TITLE_LENGTH];
    char desc[GAME_MAX_ROOM_DESC_LENGTH];
} Printing;

static uint8_t exits;
char op;

static Printing save;

static int PassFlag;
int DeathFlag;

int main()
{

    // get title size
    // print title
    // get item size
    // find item(s) in inventory ? success -> offset first version : error -> ofsset to version two
    // get descrption length
    // get description
    // print description
    // get item contained length
    // get item contained
    // get exits
    // print exits

    /******************************** Your custom code goes below here ********************************/
    int firstCheck = GameInit();

    if (firstCheck == STANDARD_ERROR)
    {
        FATAL_ERROR();
    }

    GameGetCurrentRoomTitle(save.title);
    GameGetCurrentRoomDescription(save.desc);
    exits = GameGetCurrentRoomExits();

    printf("Room Title: %s\nRoom Description: %s\n\n", save.title, save.desc);

    printf("Possible Exits:\n");
    // prints possible exits

    if (exits & GAME_ROOM_EXIT_NORTH_EXISTS)
    {
        printf("North Exit Exist\n");
    }

    if (exits & GAME_ROOM_EXIT_EAST_EXISTS)
    {
        printf("East Exit Exist\n");
    }

    if (exits & GAME_ROOM_EXIT_SOUTH_EXISTS)
    {
        printf("South Exit Exist\n");
    }

    if (exits & GAME_ROOM_EXIT_WEST_EXISTS)
    {
        printf("West Exit Exist\n");
    }

    printf("\nPick A Direction!\n\tn = north\n\te = east\n\tw = west\n\ts = south\n\tq = quit\n");
    printf("Input:");

    PassFlag = TRUE;

    while (1)
    {
        if (PassFlag == FALSE)
        {

            GameGetCurrentRoomTitle(save.title);
            GameGetCurrentRoomDescription(save.desc);
            exits = GameGetCurrentRoomExits();
            PassFlag = TRUE;

            printf("Room Title: %s\nRoom Description: %s\n\n", save.title, save.desc);

            printf("Possible Exits:\n");
            // prints possible exxits
            DeathFlag = 0;
            if (exits & GAME_ROOM_EXIT_NORTH_EXISTS)
            {
                printf("North Exit Exist\n");
                DeathFlag++;
            }

            if (exits & GAME_ROOM_EXIT_EAST_EXISTS)
            {
                printf("East Exit Exist\n");
                DeathFlag++;
            }

            if (exits & GAME_ROOM_EXIT_SOUTH_EXISTS)
            {
                printf("South Exit Exist\n");
                DeathFlag++;
            }

            if (exits & GAME_ROOM_EXIT_WEST_EXISTS)
            {
                printf("West Exit Exist\n");
                DeathFlag++;
            }

            if (DeathFlag == 0)
            {
                printf("You Have Died\n");
                exit(SUCCESS);
            }

            // print possible directions
            printf("\nPick A Direction!\n\tn = north\n\te = east\n\tw = west\n\ts = south\n\tq = quit\n");
            printf("Input:");
        }
        op = getchar();

        if (op != '\n')
        {

            switch (op)
            {
            case 'n':
                PassFlag = FALSE;
                if (exits & GAME_ROOM_EXIT_NORTH_EXISTS)
                {
                    printf("You Decided to go North\n");
                    GameGoNorth();
                    break;
                }
                printf("Can't go that way\n\n");
                break;
            case 'e':
                PassFlag = FALSE;
                if (exits & GAME_ROOM_EXIT_EAST_EXISTS)
                {
                    printf("You Decided to go East\n");
                    GameGoEast();
                    break;
                }
                printf("Can't go that way\n\n");
                break;

            case 's':
                PassFlag = FALSE;
                if (exits & GAME_ROOM_EXIT_SOUTH_EXISTS)
                {
                    printf("You Decided to go South\n");
                    GameGoSouth();
                    break;
                }
                printf("Can't go that way\n\n");
                break;
            case 'w':
                PassFlag = FALSE;
                if (exits & GAME_ROOM_EXIT_WEST_EXISTS)
                {
                    printf("You Decided to go West\n");
                    GameGoWest();
                    break;
                }
                printf("Can't go that way\n\n");
                break;
            case 'q':
                PassFlag = FALSE;
                printf("Exiting Program\n");
                exit(SUCCESS);
            default:
                PassFlag = FALSE;
                printf("Invalid key(s) was inputed\nPlease Select one of the following { n , e , s , w , q}\n\n");
                break;
            }
        }
    }

    return 0;

    /**************************************************************************************************/
}
