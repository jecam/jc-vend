#include "vm_coins.h"
#include "vm_type.h"
#include "vm_utility.h"

/* Loads coins from a file */
BOOLEAN load_coins(struct vm * vm, const char * coins_fname) {
    FILE* fh;
    char line[LINELEN];
    char * tok;

    fh = fopen(coins_fname, "r");
    if(!fh) { 
        fprintf(stderr, "Could not open file: %s\n", coins_fname);
        return FALSE;       
    }

    while (fgets(line, LINELEN, fh) != NULL) {
        enum denomination denom;
        unsigned count;

        tok = strtok(line, ",");
        if(!str_to_denom(tok, &denom)) {
            return FALSE;
        }
        tok = strtok(NULL, "\n");
        count = strtol(tok, NULL, 10);
        
        vm->coins[denom].denom = denom;
        vm->coins[denom].count = count;
    }

    fclose(fh);

    return TRUE;
}

BOOLEAN validate_coin(int coin) {
    int valid_coins[NUMDENOMS] = {5, 10, 20, 50, 100, 200, 500, 1000};
    int i;

    for ( i = 0; i < NUMDENOMS; i++ ) {
        if ( valid_coins[i] == coin ) {
            return TRUE;
        }
        if ( valid_coins[i] > coin ) {
            break;
        }
    }
    return FALSE;
}

BOOLEAN str_to_denom(char * str, enum denomination * denom) {
    int value;

    value = strtol(str, NULL, 10);

    if(!validate_coin(value)) {
        return FALSE;
    }

    return int_to_denom(value, denom);
}

BOOLEAN int_to_denom(int value, enum denomination * denom) {

    switch(value) {
    case 1000:
        *denom = TEN_DOLLARS;
        return TRUE;
    case 500:
        *denom = FIVE_DOLLARS;
        return TRUE;
    case 200:
        *denom = TWO_DOLLARS;
        return TRUE;
    case 100:
        *denom = ONE_DOLLAR;
        return TRUE;
    case 50:
        *denom = FIFTY_CENTS;
        return TRUE;
    case 20:
        *denom = TWENTY_CENTS;
        return TRUE;
    case 10:
        *denom = TEN_CENTS;
        return TRUE;
    case 5:
        *denom = FIVE_CENTS;
        return TRUE;
    default:
        break;
    }
    return FALSE;
}

char * denom_to_str(enum denomination denom) {
    
    switch(denom) {
    case TEN_DOLLARS:
        return "$10";
    case FIVE_DOLLARS:
        return "$5";
    case TWO_DOLLARS:
        return "$2";
    case ONE_DOLLAR:
        return "$1";
    case FIFTY_CENTS:
        return "50c";
    case TWENTY_CENTS:
        return "20c";
    case TEN_CENTS:
        return "10c";
    case FIVE_CENTS:
        return "5c";
    default:
        return "null";
    }
}



int take_coin(int coin_buffer[NUMDENOMS]) {
    char input[5];
    
    enum denomination denom;
    
    printf("Insert coin: ");
    fgets(input, 5, stdin);

    if(str_to_denom(input, &denom)) {
        coin_buffer[denom]++;
        return strtol(input, NULL, 10);
    }
    return -1;
}


/* Take input of coins into a "coin buffer" array
 * Accepts value required, returns pointer to coin buffer
 */

int* accept_payment(int required) {
    int* coin_buffer;
    int payment = 0;

    coin_buffer = safe_malloc(sizeof(*coin_buffer * NUMDENOMS));

    while ( payment < required ) {
        int coinval = take_coin(coin_buffer);
        if(coinval == -1) {
            return NULL;
        } else {
            payment += coinval;
        }
    }

    return coin_buffer;
}

