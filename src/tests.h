#include "vm_menu.h"

#define TEST_PASS "\x1b[32mSuccess\x1b[39m"
#define TEST_FAIL "\x1b[31mFailure\x1b[39m"

#define PASS_FAIL printf(TEST_PASS);            \
    stats[1]++;                                    \
    } else {                                    \
    printf(TEST_FAIL);                          \
    stats[2]++;                                    

void get_missing_item(struct vm* vm, int stats[3]) {
    printf("\tTesting item retrieval (item not present)...");
    stats[0]++;
    if(retrieve_item(vm->item_list, "I0099") == NULL) {
        PASS_FAIL;
    }
}

void get_present_item(struct vm* vm, int stats[3]) {
    struct stock_item* item;
    char* search_string = "I0001";
    printf("\n\tTesting item retrieval (item present)...");
    stats[0]++;
    item = retrieve_item(vm->item_list, search_string);
    if(item == NULL) {
        printf(TEST_FAIL);
        stats[2]++;
        return;
    }
    if(strcmp(item->id, search_string) == 0) {
        PASS_FAIL;
    }
}


void validate_bad_coin(int coin, const char* coinname, int stats[3]) {
    printf("\nTesting validate coin on %s...", coinname);
    stats[0]++;
    if(!validate_coin(coin)) {
        PASS_FAIL;
    }
    
}

void validate_good_coin(int coin, const char* coinname, int stats[3]) {
    printf("\nTesting validate coin on %s...", coinname);
    stats[0]++;
    if(validate_coin(coin)) {
        PASS_FAIL;
    }
    
}

void validate_coin_zero(int stats[3]) {
    validate_bad_coin(0, "zero", stats);
}

void validate_coin_three(int stats[3]) {
    validate_bad_coin(3, "three", stats);
}

void validate_coin_two_fifty(int stats[3]) {
    validate_bad_coin(250, "two hundred and fifty", stats);
}

void validate_coin_five_thousand(int stats[3]) {
    validate_bad_coin(5000, "five thousand", stats);
}

void validate_coin_five(int stats[3]) {
    validate_good_coin(5, "five", stats);
}

void validate_coin_ten(int stats[3]) {
    validate_good_coin(10, "ten", stats);
}

void validate_coin_twenty(int stats[3]) {
    validate_good_coin(20, "twenty", stats);
}

void validate_coin_one_hundred(int stats[3]) {
    validate_good_coin(100, "one hundred", stats);
}

void validate_coin_two_hundred(int stats[3]) {
    validate_good_coin(200, "two hundred", stats);
}

void validate_coin_five_hundred(int stats[3]) {
    validate_good_coin(500, "five hundred", stats);
}

void validate_coin_one_thousand(int stats[3]) {
    validate_good_coin(1000, "one thousand", stats);
}



void run_tests(struct vm* vm) {
    int stats[3] = {0, 0, 0};

    printf("\n\nRunning test suite.\n\n");

    printf("Testing purchasing item...\n");
    get_missing_item(vm, stats);
    get_present_item(vm, stats);
    validate_coin_zero(stats);
    validate_coin_three(stats);
    validate_coin_two_fifty(stats);
    validate_coin_five_thousand(stats);
    validate_coin_five(stats);
    validate_coin_ten(stats);
    validate_coin_twenty(stats);
    validate_coin_one_hundred(stats);
    validate_coin_two_hundred(stats);
    validate_coin_five_hundred(stats);
    validate_coin_one_thousand(stats);
    printf("\n\n%d tests run, %d passed, %d failed\n", stats[0], stats[1], stats[2]);
    display_coins(vm);

    accept_payment(500);

}
