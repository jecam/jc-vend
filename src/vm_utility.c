/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #2
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#include "vm_utility.h"
#include "vm_stock.h"
#include "vm_coins.h"

/* 
 * Clears the input buffer.
 * */
void read_rest_of_line(void)
{
    int ch;
    while(ch = getc(stdin), ch!='\n' && ch != EOF) 
        ;
    clearerr(stdin);
}

/* 
 * Initialises the vm data structure declared in main to safe initial
 * values.
 * */
BOOLEAN vm_init(struct vm * vm)
{

    vm->item_list = safe_malloc(sizeof( *(vm->item_list) ));

    vm->item_list->length = 0;
    vm->item_list->head = NULL;
    
    return TRUE;

}

/* 
 * Loads data from the .dat files into memory. 
 * */
BOOLEAN load_data(struct vm * vm, const char * item_fname, 
    const char * coins_fname)
{
     
    if (!load_items(vm, item_fname)) {
        return FALSE;
    }

    if (!load_coins(vm, coins_fname)) {
        return FALSE;
    }
    
    return TRUE;

}

/* 
 * Frees all dynamically allocated data.
 * */
void system_free(struct vm * vm)
{
    if ( vm->item_list->head != NULL ) {
        r_free_item_list(vm->item_list->head);
    }
    free(vm->item_list);
}

/* Allocate memory to a pointer, ensuring that it worked */
void *safe_malloc(size_t size)
{
	void *mem = NULL;
	if ((mem = calloc(1, size)) == NULL) {
		fprintf(stderr, "Error: safe_malloc() cannot allocate "
			"memory of size %lu.\n", size);
		exit(EXIT_FAILURE);
	}
	return mem;
}



