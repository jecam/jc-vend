#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vm_type.h"

#ifndef VM_COINS
#define VM_COINS
#define LINELEN 300


BOOLEAN load_coins(struct vm * vm, const char * coins_fname);
BOOLEAN validate_coin(int coin);
BOOLEAN str_to_denom(char * str, enum denomination * denom);
BOOLEAN int_to_denom(int value, enum denomination* denom);
char * denom_to_str(enum denomination denom);
int take_coin(int coin_buffer[NUMDENOMS]);
int* accept_payment(int required);


#endif
