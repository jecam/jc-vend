#include "vm_stock.h"

/* Loads items from a file */
BOOLEAN load_items(struct vm * vm, const char * items_fname) {
    FILE * fh;
    char line[LINELEN];
    
    fh = fopen(items_fname, "r");
    
    if (!fh) {
        fprintf(stderr, "Could not open file: %s\n", items_fname);
        return FALSE;
    }

    while (fgets(line, LINELEN, fh) != NULL) {
        char * tok;
        char * pricetok;
        char id[IDLEN+1];
        char name[NAMELEN+1];
        char description[DESCLEN+1];
        unsigned dollars, cents, on_hand;

        struct stock_item* item;
        
        tok = strtok(line, "|");
        strcpy(id, tok);
        tok = strtok(NULL, "|");
        strcpy(name, tok);
        tok = strtok(NULL, "|");
        strcpy(description, tok);
        pricetok = strtok(NULL, "|");
        tok = strtok(NULL, "\n");
        on_hand = strtol(tok, NULL, 10);
        
        tok = strtok(pricetok, ".");
        dollars = strtol(tok, NULL, 10);
        tok = strtok(NULL, "\0");
        cents = strtol(tok, NULL, 10);

        item = new_stock_item(id, name, description, dollars, cents, on_hand);
        stock_insert(vm, item);        
    }

    fclose(fh);
    return TRUE;
}

/* Generates a node including data, from a line in the correct format
   TODO: validate data entry (bad data causes segfaults)
*/
struct vm_node* new_vm_node(struct stock_item * item) {
    struct vm_node* node;

    node = safe_malloc(sizeof *node);
    node->data = item;    
    node->next = NULL;

    return node;
}

struct stock_item* new_stock_item(char* id, char* name, char* description,
                               unsigned dollars, unsigned cents, unsigned on_hand) {
    struct stock_item* item;

    item = safe_malloc(sizeof *item);
    strcpy(item->id, id);
    strcpy(item->name, name);
    strcpy(item->description, description);
    item->price.dollars = dollars;
    item->price.cents = cents;
    item->on_hand = on_hand;
    
    return item;
}


/* Adds a node in alphabetical order by name */
BOOLEAN stock_insert(struct vm * vm, struct stock_item * item) {
    struct vm_node * node = new_vm_node(item);
    struct vm_node * current, *previous;
    
    if(vm->item_list->head == NULL) {
        vm->item_list->head = node;
        vm->item_list->length++;
        return TRUE;
    }
    previous = NULL;
    current = vm->item_list->head;

    while (current && strcmp(node->data->name, current->data->name) > 0 ) {
        previous = current;
        current = current->next;

    }
    
    node->next = current;
    if(!previous) {
        vm->item_list->head = node;
    } else {
        previous->next = node;
    }
    vm->item_list->length++;
    return TRUE;
}

struct stock_item* retrieve_item(struct vm_list* list, char* id){
    struct vm_node* curr = list->head;

    while(curr && strcmp(curr->data->id, id) != 0) {
        curr = curr->next;
    }
    if (!curr) {
        return NULL;
    } else {
        return curr->data;
    }
}

/* The r stands for recursive */
void r_free_item_list(struct vm_node * node) {
    if(node->next != NULL) {
        r_free_item_list(node->next);
    }
    free(node->data);
    free(node);
}
