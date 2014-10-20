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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vm_type.h"


#ifndef VM_UTILITY
#define VM_UTILITY

void read_rest_of_line(void);
BOOLEAN vm_init(struct vm * vm);
BOOLEAN load_data(struct vm * vm, const char * item_fname, 
    const char * coins_fname);
void system_free(struct vm * vm); 

void *safe_malloc(size_t size);

#endif

