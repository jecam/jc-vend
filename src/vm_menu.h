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

#include "vm_options.h"

#ifndef VM_MENU
#define VM_MENU

#define NUM_MENU_ITEMS 8
#define ITEM_NAME_LEN 40
#define EXIT_OPTION 8
#define CHOICE_OFFSET 49

/* The data structure to hold information about each menu option, the 
 * name of the function to display and a pointer to the function that 
 * will implement that option. */
struct menu_item
{
    char name[ITEM_NAME_LEN+1];
    BOOLEAN (*func)(struct vm*);
};

/* Builds the menu for the vending machine. */
void menu_init(struct menu_item *);
void display_menu(struct menu_item *);
int get_item_choice(void);

#endif
