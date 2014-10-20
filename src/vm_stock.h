#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vm_utility.h"

#include "vm_coins.h"

#ifndef VM_STOCK
#define VM_STOCK

#define IDLEN 5
#define NAMELEN 40
#define DESCLEN 255

/* Each price will have a dollars and a cents component */
struct price
{
    unsigned dollars,cents;
};

/* The data structure that holds the data for each item of stock
 */
struct stock_item
{
    char id[IDLEN+1];
    char name[NAMELEN+1];
    char description[DESCLEN+1];
    struct price price;
    unsigned on_hand;
};

/* The data structure that holds a pointer to the stock_item data and a
 * pointer to the next node in the list
 */
struct vm_node
{
    struct stock_item * data;
    struct vm_node * next;
};

/* The head of the list - has a pointer to the rest of the list and a 
 * stores the length of the list 
 */
struct vm_list
{
    struct vm_node * head;
    unsigned length;
};


BOOLEAN load_items(struct vm * vm, const char * items_fname);
struct vm_node* new_vm_node(struct stock_item* item);
struct stock_item* new_stock_item(char* id, char* name, char* description,
                               unsigned dollars, unsigned cents, unsigned on_hand);
BOOLEAN stock_insert(struct vm * vm, struct stock_item * item);
struct stock_item* retrieve_item(struct vm_list* list, char* id);
void r_free_item_list(struct vm_node * node);

#endif
