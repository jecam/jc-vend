#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vm_type.h"

#ifndef VM_COINS
#define VM_COINS
#define LINELEN 300


BOOLEAN load_coins(struct coin* coins, const char * coins_fname);
BOOLEAN validate_coin(int coin);
BOOLEAN str_to_denom(char * str, enum denomination * denom);
BOOLEAN int_to_denom(int value, enum denomination* denom);
int denom_to_int(enum denomination denom);
char* denom_to_str(enum denomination denom);
char* take_coin_input(char * input);
int take_coin(int coin_buffer[NUMDENOMS], char* input);
int accept_payment(int coin_buffer[NUMDENOMS], int required);
void dispense_change(struct coin* coins, int change_required);

#endif
