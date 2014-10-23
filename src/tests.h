#include "vm_menu.h"

#define TEST_PASS "\x1b[32mSuccess\x1b[39m\n"
#define TEST_FAIL "\x1b[31mFailure\x1b[39m\n"

#define PASS_FAIL(message) printf("%-60s%s", message, TEST_PASS);    \
    stats[1]++;                                    \
    } else {                                    \
    printf("%-60s%s", message, TEST_FAIL);        \
    stats[2]++;

void get_missing_item(int stats[3], struct vm* vm) {
    char* message = "Testing item retrieval (item not present)...";
    stats[0]++;
    if(retrieve_item(vm->item_list, "I0099") == NULL) {
        PASS_FAIL(message);
    }
}

void get_present_item(int stats[3], struct vm* vm) {
    struct stock_item* item;
    char* search_string = "I0001";
    char* message ="Testing item retrieval (item present)...";
    stats[0]++;
    item = retrieve_item(vm->item_list, search_string);
    if(item == NULL) {
        printf(TEST_FAIL);
        stats[2]++;
        return;
    }
    if(strcmp(item->id, search_string) == 0) {
        PASS_FAIL(message);
    }
}
/**/

void meta_validate_coin(int stats[3], int coin, const char* coinname, BOOLEAN expected) {
    char message[80];
    strcpy(message, "Testing validate coin on ");
    strcat(message, coinname);
    strcat(message, "...");
    
    stats[0]++;
    if(validate_coin(coin) == expected) {
        PASS_FAIL(message);
    }
    
}

void validate_coin_zero(int stats[3]) {
    meta_validate_coin(stats, 0, "zero", FALSE);
}

void validate_coin_three(int stats[3]) {
    meta_validate_coin(stats, 3, "three", FALSE);
}

void validate_coin_two_fifty(int stats[3]) {
    meta_validate_coin(stats, 250, "two hundred and fifty", FALSE);
}

void validate_coin_five_thousand(int stats[3]) {
    meta_validate_coin(stats, 5000, "five thousand", FALSE);
}

void validate_coin_five(int stats[3]) {
    meta_validate_coin(stats, 5, "five", TRUE);
}

void validate_coin_ten(int stats[3]) {
    meta_validate_coin(stats, 10, "ten", TRUE);
}

void validate_coin_twenty(int stats[3]) {
    meta_validate_coin(stats, 20, "twenty", TRUE);
}

void validate_coin_one_hundred(int stats[3]) {
    meta_validate_coin(stats, 100, "one hundred", TRUE);
}

void validate_coin_two_hundred(int stats[3]) {
    meta_validate_coin(stats, 200, "two hundred", TRUE);
}

void validate_coin_five_hundred(int stats[3]) {
    meta_validate_coin(stats, 500, "five hundred", TRUE);
}

void validate_coin_one_thousand(int stats[3]) {
    meta_validate_coin(stats, 1000, "one thousand", TRUE);
}
/**/

void take_coin_10_returns_10(int stats[3]) {
    int* coin_buffer;
    int coinval;
    char* message;
    coin_buffer = safe_malloc(sizeof(*coin_buffer) * NUMDENOMS);

    message = "Testing taking a ten cent coin...";
    stats[0]++;
    coinval = take_coin(coin_buffer, "10");
    free(coin_buffer);

    if(coinval == 10) {
        PASS_FAIL(message);
    }
}

void take_coin_15_returns_0(int stats[3]) {
    int* coin_buffer;
    int coinval;
    char* message;
    coin_buffer = safe_malloc(sizeof(*coin_buffer) * NUMDENOMS);

    message = "Testing taking a fifteen cent coin...";
    stats[0]++;
    coinval = take_coin(coin_buffer, "15");
    free(coin_buffer);

    if(coinval == 0) {
        PASS_FAIL(message);
    }
}

void take_coin_empty_returns_neg1(int stats[3]) {
    int* coin_buffer;
    int coinval;
    char* message;
    coin_buffer = safe_malloc(sizeof(*coin_buffer) * NUMDENOMS);

    message = "Testing taking an empty string coin(abort signal)...";
    stats[0]++;
    coinval = take_coin(coin_buffer, "");
    free(coin_buffer);

    if(coinval == -1) {
        PASS_FAIL(message);
    }
}

void meta_accept_payment(int stats[3], int* cb, int expected, const char* message) {

    stats[0]++;
    printf("%s\n", message);
    if(accept_payment(cb, 5) == expected) {
        stats[1]++;
        printf("%78s", TEST_PASS);
    } else {
        stats[2]++;
        printf("%78s", TEST_FAIL);
    }
}

void accept_payment_exact_change_returns_0(int stats[3]) {
    int* cb;
    cb = safe_malloc(sizeof(*cb) * NUMDENOMS);

    meta_accept_payment(stats, cb, 0,
                        "Testing accept payment on exact change\n (please enter 5 at the prompt)...");

    free(cb);    
}

void accept_payment_too_much_returns_5(int stats[3]) {
    int* cb;
    cb = safe_malloc(sizeof(*cb) * NUMDENOMS);

    meta_accept_payment(stats, cb, 5, "Testing accept payment on overpay\n (please enter 10 at the prompt)...");

    free(cb);
}

void accept_payment_abort_returns_neg1(int stats[3]){
    int* cb;
    cb = safe_malloc(sizeof(*cb) * NUMDENOMS);
    
    meta_accept_payment(stats, cb, -1, "Testing accept payment abort\n (please press enter or ctrl-d at the prompt)...");

    free(cb);
}



void run_tests(struct vm* vm) {
    int stats[3] = {0, 0, 0};
    
    printf("\n\nRunning test suite.\n\n");

    get_missing_item(stats, vm);
    get_present_item(stats, vm);
    printf("\n");
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
    printf("\n");
    take_coin_10_returns_10(stats);
    take_coin_15_returns_0(stats);
    take_coin_empty_returns_neg1(stats);
    printf("\n");
    accept_payment_exact_change_returns_0(stats);
    accept_payment_too_much_returns_5(stats);
    accept_payment_abort_returns_neg1(stats);
    printf("\n");
    
    printf("\n\n%d tests run, %d passed, %d failed\n", stats[0], stats[1], stats[2]);
}
