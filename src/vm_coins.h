#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vm_type.h"

#ifndef VM_COINS
#define VM_COINS
#define LINELEN 300


BOOLEAN load_coins(struct vm * vm, const char * coins_fname);
enum denomination str_to_denom(char * str);
char * denom_to_str(enum denomination denom);

#endif
