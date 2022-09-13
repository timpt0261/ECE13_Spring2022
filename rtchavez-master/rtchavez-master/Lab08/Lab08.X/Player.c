// Reuben Chavez
// ECE 13E Spring
#include "Player.h"
#include "Game.h"
#include "stdlib.h"

// create Inventory struct
typedef struct Inventory{
    uint8_t key[INVENTORY_SIZE];
    int size;
}Inventory;

// create static instance that already has item zero
static Inventory invt = {
    .key = {0,},
    .size = 1
};


/**
 * Adds the specified item to the player's inventory if the inventory isn't full.
 * @param item The item number to be stored: valid values are 0-255.
 * @return SUCCESS if the item was added, STANDARD_ERRROR if the item couldn't be added.
 */
int AddToInventory(uint8_t item){
    
    if( invt.size < INVENTORY_SIZE){
        
        invt.key[invt.size] = item;
        invt.size++;
        }
    
    return SUCCESS;
}

/**
 * Check if the given item exists in the player's inventory.
 * @param item The number of the item to be searched for: valid values are 0-255.
 * @return SUCCESS if it was found or STANDARD_ERROR if it wasn't.
 */
int FindInInventory(uint8_t item){

    for(int i = 0; i < INVENTORY_SIZE; i++){
        if(item == invt.key[i]){
            return SUCCESS;
        }
    }    
    return STANDARD_ERROR;
}