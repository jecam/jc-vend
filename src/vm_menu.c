/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #2
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller and Virginia King
 * Some codes are adopted here with permission by an anonymous author
 ***********************************************************************/
#include "vm_menu.h"

/* 
 * Initialises the menu array declared in main 
 * */
void menu_init(struct menu_item * menu)
{

    strcpy(menu[0].name, "Display Items");
    menu[0].func = display_items;
    strcpy(menu[1].name, "Display Coins");
    menu[1].func = display_coins;
    strcpy(menu[2].name, "Purchase Item");
    menu[2].func = purchase_item;
    strcpy(menu[3].name, "Add Item");
    menu[3].func = add_item;
    strcpy(menu[4].name, "Delete Item");
    menu[4].func = delete_item;
    strcpy(menu[5].name, "Reset Coin Count");
    menu[5].func = reset_coin_count;
    strcpy(menu[6].name, "Reset Stock Count");
    menu[6].func = reset_stock_count;
    strcpy(menu[7].name, "Save");
    menu[7].func = save;

}

void display_menu(struct menu_item * menu) {
    int i;

    printf("\nJuJu's Vending Machine Interface Main Menu\n");
    printf("------------------------------------------\n");
    
    for(i = 0; i < NUM_MENU_ITEMS; i++) {
        printf("%d) %s\n", i + 1, menu[i].name);
    }
    printf("9) Exit Program\n");
    printf("------------------------------------------\n");
    printf("Please make a selection: ");

}

int get_item_choice(void) {
    unsigned charchoice;
    
    do {
        charchoice = fgetc(stdin);
        if(fgetc(stdin) != '\n') {
            read_rest_of_line();
        }
        charchoice -= CHOICE_OFFSET;
        if (charchoice <= NUM_MENU_ITEMS) {
            break;
        }
        printf("Invalid selection, try again: ");
    } while (charchoice > NUM_MENU_ITEMS);

    return charchoice;

}
