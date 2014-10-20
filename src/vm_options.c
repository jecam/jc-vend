/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #2
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#include "vm_options.h"
#include "vm_coins.h"

/* 
 * Displays a formatted list of the items currently for sale in the 
 * machine. This will fulfill requirement 5 of the spec.
 * */
BOOLEAN display_items(struct vm * vm)
{
    struct vm_node * node = vm->item_list->head;

    printf("\nDisplaying items!\n");

    while(node) { 
        printf("%s, %s, %s, $%d.%.2d, %d\n", node->data->id, node->data->name, 
               node->data->description, node->data->price.dollars, 
               node->data->price.cents, node->data->on_hand);
        node = node->next;
    }

    return TRUE;
}

/* 
 * Displays a formatted list of the coins currently on hand in the 
 * vending machine. This fulills requirement 12 of the spec.
 * */
BOOLEAN display_coins(struct vm * vm)
{
    int i;
    printf("\nDisplay Coins selected\n");
    
    for(i = 0; i < NUMDENOMS; i++) {
        char * valstr = denom_to_str(vm->coins[i].denom);
        printf( "%s - %d\n", valstr, vm->coins[i].count);
    }
    
    return TRUE;
}

/* 
 * Allows a customer to purchase an item for the vending machine. This
 * fulfills requirement 6 of the spec.
 * */
BOOLEAN purchase_item(struct vm * vm)
{
  /* The UNUSED() function is designed to prevent warnings while your 
     * code is only partially complete. Delete this function call once 
     * you are using vm in your own code */
    UNUSED(vm);
    return FALSE;
}

/* 
 * Adds an item to the vending machine. This fulfills requirement 8 of
 * the spec.
 * */
BOOLEAN add_item(struct vm* vm)
{
  /* The UNUSED() function is designed to prevent warnings while your 
     * code is only partially complete. Delete this function call once 
     * you are using vm in your own code */
    UNUSED(vm);
    return FALSE;
}

/* 
 * Removes an item from the vending machine and frees all dynamically 
 * allocated memory as required. This fulfills requirement 9 of the 
 * spec.
 * */
BOOLEAN delete_item(struct vm* vm)
{
  /* The UNUSED() function is designed to prevent warnings while your 
     * code is only partially complete. Delete this function call once 
     * you are using vm in your own code */
    UNUSED(vm);
    return FALSE;
}

/* 
 * Sets the count of each coin to the default value. This fulfills 
 * requirement 11 of the spec.
 * */
BOOLEAN reset_coin_count(struct vm* vm)
{
  /* The UNUSED() function is designed to prevent warnings while your 
     * code is only partially complete. Delete this function call once 
     * you are using vm in your own code */
    UNUSED(vm);
    return FALSE;
}

/* 
 * Sets the count of each stock item to the default value. This fulfills 
 * requirement 10 of the spec.
 * */
BOOLEAN reset_stock_count(struct vm* vm)
{
  /* The UNUSED() function is designed to prevent warnings while your 
     * code is only partially complete. Delete this function call once 
     * you are using vm in your own code */
    UNUSED(vm);
    return FALSE;
}

/* 
 * Saves the updated stock count to the stock file specified on the 
 * command line. This partially fulfill requirement 7 of the spec.
 * */
BOOLEAN save(struct vm * vm)
{
  /* The UNUSED() function is designed to prevent warnings while your 
     * code is only partially complete. Delete this function call once 
     * you are using vm in your own code */
    UNUSED(vm);
    return FALSE;
}

