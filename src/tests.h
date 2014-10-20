/*
#include <string.h>
#include <stdlib.h>

*/
#include "vm_menu.h"

#define TEST_PASS "\x1b[32mSuccess\x1b[39m"
#define TEST_FAIL "\x1b[31mFailure\x1b[39m"

#define PASS_FAIL printf(TEST_PASS);            \
    (*pc)++;                                    \
    } else {                                    \
    printf(TEST_FAIL);                          \
    (*fc)++;                                    \
    return;

void get_missing_item(struct vm* vm, int* tc, int* pc, int* fc) {
    printf("\tTesting item retrieval (item not present)...");
    (*tc)++;
    if(retrieve_item(vm->item_list, "I0099") == NULL) {
        PASS_FAIL;
    }
}

void get_present_item(struct vm* vm, int* tc, int* pc, int* fc) {
    struct stock_item* item;
    char* search_string = "I0001";
    printf("\n\tTesting item retrieval (item present)...");
    (*tc)++;
    item = retrieve_item(vm->item_list, search_string);
    if(item == NULL) {
        printf(TEST_FAIL);
        (*fc)++;
        return;
    }
    if(strcmp(item->id, search_string) == 0) {
        PASS_FAIL;
    }
}

void purchase_item_test(struct vm* vm) {
    int tc = 0;
    int pc = 0;
    int fc = 0;
    printf("Testing purchasing item...\n");
    get_missing_item(vm, &tc, &pc, &fc);
    get_present_item(vm, &tc, &pc, &fc);
    printf("\n\n%d tests run, %d passed, %d failed\n", tc, pc, fc);
}


void run_tests(struct vm* vm) {
    printf("\n\nRunning test suite.\n\n");
    purchase_item_test(vm);
}
