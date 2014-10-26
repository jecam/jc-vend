#include "vm_menu.h"

#define TEST_PASS "\x1b[32mSuccess\x1b[39m\n"
#define TEST_FAIL "\x1b[31mFailure\x1b[39m\n"

/* Macros are gross but I can't think of a better way to do this. Sorry. */
#define PASS_FAIL(message)                         \
    printf("%-35s%s", message, TEST_PASS);         \
    stats[1]++;                                    \
    } else {                                       \
    printf("%-35s%s", message, TEST_FAIL);         \
    stats[2]++;

/* Item retrieval tests */

void get_missing_item(int stats[3], struct vm* vm) {
    char* message = "  -Item not in list...";
    stats[0]++;
    if(retrieve_item(vm->item_list, "I0099") == NULL) {
        PASS_FAIL(message);
    }
}

void get_present_item(int stats[3], struct vm* vm) {
    struct stock_item* item;
    char* search_string = "I0001";
    char* message ="  -Item present in list...";
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
/* end item retrieval*/

/* Coin validation tests */

void meta_validate_coin(int stats[3], int coin, const char* coinname, BOOLEAN expected) {
    char message[80];
    strcpy(message, "  -");
    strcat(message, coinname);
    strcat(message, "...");
    
    stats[0]++;
    if(validate_coin(coin) == expected) {
        PASS_FAIL(message);
    }
    
}

void validate_coin_zero(int stats[3]) {
    meta_validate_coin(stats, 0, "0", FALSE);
}

void validate_coin_three(int stats[3]) {
    meta_validate_coin(stats, 3, "3", FALSE);
}

void validate_coin_two_fifty(int stats[3]) {
    meta_validate_coin(stats, 250, "250", FALSE);
}

void validate_coin_five_thousand(int stats[3]) {
    meta_validate_coin(stats, 5000, "5000", FALSE);
}

void validate_coin_five(int stats[3]) {
    meta_validate_coin(stats, 5, "5", TRUE);
}

void validate_coin_ten(int stats[3]) {
    meta_validate_coin(stats, 10, "10", TRUE);
}

void validate_coin_twenty(int stats[3]) {
    meta_validate_coin(stats, 20, "20", TRUE);
}

void validate_coin_one_hundred(int stats[3]) {
    meta_validate_coin(stats, 100, "100", TRUE);
}

void validate_coin_two_hundred(int stats[3]) {
    meta_validate_coin(stats, 200, "200", TRUE);
}

void validate_coin_five_hundred(int stats[3]) {
    meta_validate_coin(stats, 500, "500", TRUE);
}

void validate_coin_one_thousand(int stats[3]) {
    meta_validate_coin(stats, 1000, "1000", TRUE);
}
/* end coin validation tests */

/* Take coin tests */

void take_coin_10_returns_10(int stats[3]) {
    int* coin_buffer;
    int coinval;
    char* message;
    coin_buffer = safe_malloc(sizeof(*coin_buffer) * NUMDENOMS);

    message = "  -Ten cent coin...";
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

    message = "  -Fifteen cent coin...";
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

    message = "  -Empty string (abort signal)...";
    stats[0]++;
    coinval = take_coin(coin_buffer, "");
    free(coin_buffer);

    if(coinval == -1) {
        PASS_FAIL(message);
    }
}

/* end take coin tests */

/* accept payment tests ( requires user input ) */

void meta_accept_payment(int stats[3], int* cb, int expected, const char* message) {

    stats[0]++;
    printf("%s\n", message);
    if(accept_payment(cb, 5) == expected) {
        stats[1]++;
        printf("%53s", TEST_PASS);
    } else {
        stats[2]++;
        printf("%53s", TEST_FAIL);
    }
}

void accept_payment_exact_change_returns_0(int stats[3]) {
    int* cb;
    cb = safe_malloc(sizeof(*cb) * NUMDENOMS);

    meta_accept_payment(stats, cb, 0,
                        "  -Exact change (enter 5 at the prompt)...");

    free(cb);    
}

void accept_payment_too_much_returns_5(int stats[3]) {
    int* cb;
    cb = safe_malloc(sizeof(*cb) * NUMDENOMS);

    meta_accept_payment(stats, cb, 5, "  -Overpay (enter 10 at the prompt)...");

    free(cb);
}

void accept_payment_abort_returns_neg1(int stats[3]){
    int* cb;
    cb = safe_malloc(sizeof(*cb) * NUMDENOMS);
    
    meta_accept_payment(stats, cb, -1, "  -Abort (press enter or ctrl-d at the prompt)...");

    free(cb);
}
/* end accept payment tests */

/* Change calculator tests */
/* Note that the test metric used here may be inaccurate, 
   you can uncomment display_coins() lines to see contents of coins array before and after */
void meta_dispense_change(int stats[3], struct coin coins[NUMDENOMS],
                           int cents_required, int expected_diff, char* message) {
    unsigned initial_coins[NUMDENOMS], i, diff = 0;
    stats[0]++;

    for (i = 0; i < NUMDENOMS; i++) {
        initial_coins[i] = coins[i].count;
    }    
    
    dispense_change(coins, cents_required);

    for (i = 0; i < NUMDENOMS; i++) {
        diff += initial_coins[i] - coins[i].count;
    }

    if (diff == expected_diff) {
        PASS_FAIL(message);
    }   
}

void dispense_no_change(int stats[3], struct vm * vm) {
    char* message = "  -No change required...";
    /* display_coins(vm); */
    meta_dispense_change(stats, vm->coins, 0, 0, message);
    /* display_coins(vm); */
}

void dispense_one_dollar_change(int stats[3], struct vm * vm) {
    char* message = "  -$1 change required...";
    /* display_coins(vm); */
    meta_dispense_change(stats, vm->coins, 100, 1, message);
    /* display_coins(vm); */
}

void dispense_one_dollar_change_cascade(int stats[3], struct vm * vm) {
    char* message = "  -2 * 50c change (no $1)...";
    vm->coins[4].count = 0;
    /* display_coins(vm); */
    meta_dispense_change(stats, vm->coins, 100, 2, message);
    /* display_coins(vm); */
    vm->coins[4].count = 20;
}

void dispense_eighteen_dollars_eighty_five_cents(int stats[3], struct vm * vm) {
    char* message = "  -$18.85 (one of each coin)...";
    /* display_coins(vm); */
    meta_dispense_change(stats, vm->coins, 1885, NUMDENOMS, message);
    /* display_coins(vm); */
}
/* end change dispenser tests */

/* Test suites */
void item_retrieval_tests(int stats[3], struct vm* vm) {
    printf("Testing item retrieval :\n");
    get_missing_item(stats, vm);
    get_present_item(stats, vm);
    printf("\n");
}

void validate_coin_tests(int stats[3]) {
    printf("Testing validate coin on:\n");
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
}

void take_coin_tests(int stats[3]) {
    printf("Testing taking coins:\n");
    take_coin_10_returns_10(stats);
    take_coin_15_returns_0(stats);
    take_coin_empty_returns_neg1(stats);
    printf("\n");
}

void accept_payment_tests(int stats[3]) {
    printf("Testing accept payment:\n");
    accept_payment_exact_change_returns_0(stats);
    accept_payment_too_much_returns_5(stats);
    accept_payment_abort_returns_neg1(stats);
    printf("\n");
}

void dispense_change_tests(int stats[3], struct vm* vm) {
/* TODO: */
    printf("Testing dispense change:\n");
    dispense_no_change(stats, vm);
    dispense_one_dollar_change(stats, vm);
    dispense_one_dollar_change_cascade(stats, vm);
    dispense_eighteen_dollars_eighty_five_cents(stats, vm);
    printf("\n");

}


/* Main test function (this is where the party starts... ) */
void run_tests(struct vm* vm) {
    int stats[3] = {0, 0, 0};
    
    printf("\n\nRunning test suite.\n\n");

    item_retrieval_tests(stats, vm);

    validate_coin_tests(stats);

    take_coin_tests(stats);
/*  
 *  These tests require user input, it's annoying so they're left out for now
 *  accept_payment_tests(stats);
 */

    dispense_change_tests(stats, vm);
    
    printf("\n\n%d tests run, %d passed, %d failed\n", stats[0], stats[1], stats[2]);
}
