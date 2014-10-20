/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #2
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/

#include "vm_menu.h"
#include "tests.h"
#define NUMARGS 3


int main(int argc, char * argv[])
{
    struct vm vm;
    struct menu_item menu_items[NUM_MENU_ITEMS];
    int choice;
    UNUSED(choice);
    /* check command line arguments */
    if(argc != NUMARGS) {
        printf("Usage: %s [stock file] [coin file]\n", argv[0]);
        return EXIT_FAILURE;
    }
    /* initialise data structures */
    vm_init(&vm);
    vm.foodfile = argv[1];
    vm.coinsfile = argv[2];

    menu_init(menu_items);

    /* load data */

    if(!load_data(&vm, vm.foodfile, vm.coinsfile)) {
        fprintf(stderr, "Unable to load data.\n");
        return EXIT_FAILURE;
    }

    run_tests(&vm);
    
    /* if the data is valid and has loaded correctly then
     * display menu and allow interaction */
    /*
    do {
        display_menu(menu_items);
    
        choice = get_item_choice();
        if(choice != EXIT_OPTION) {
            menu_items[choice].func(&vm);
        }
    } while (choice != EXIT_OPTION);
    */
    system_free(&vm);
    return EXIT_SUCCESS;
}
