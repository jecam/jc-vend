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
#include "vm_type.h"
#include "vm_stock.h"

#ifndef VM_OPTIONS
#define VM_OPTIONS

BOOLEAN display_items(struct vm*);
BOOLEAN display_coins(struct vm*);
BOOLEAN purchase_item(struct vm*);
BOOLEAN add_item(struct vm*);
BOOLEAN delete_item(struct vm*);
BOOLEAN reset_coin_count(struct vm*);
BOOLEAN reset_stock_count(struct vm*);
BOOLEAN save(struct vm * vm);

#endif
