#include "vm_coins.h"
#include "vm_type.h"
#include "vm_utility.h"

/* Loads coins from a file */
BOOLEAN load_coins(struct coin * coins, const char * coins_fname) {
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
        
        coins[denom].denom = denom;
        coins[denom].count = count;
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

int denom_to_int(enum denomination denom) {
    
    switch(denom) {
    case TEN_DOLLARS:
        return 1000;
    case FIVE_DOLLARS:
        return 500;
    case TWO_DOLLARS:
        return 200;
    case ONE_DOLLAR:
        return 100;
    case FIFTY_CENTS:
        return 50;
    case TWENTY_CENTS:
        return 20;
    case TEN_CENTS:
        return 10;
    case FIVE_CENTS:
        return 5;
    default:
        return 0;
    }
}


char* take_coin_input(char * input) {    
    printf("Insert coin: ");
    fgets(input, 5, stdin);
    
    return input;
}

/* Feed a coin into the coin buffer, 
 * coin buffer and input string are passed in
 * returns -1 for abort, 0 if input was invalid, or value of the coin
 * in cents if it worked.
 */
int take_coin(int coin_buffer[NUMDENOMS], char* input) {
    enum denomination denom;

    if(input[0] == '\0' || input[0] == '\n'){
        return -1;
    }
    
    if(str_to_denom(input, &denom)) {
        coin_buffer[denom]++;
        return strtol(input, NULL, 10);
    }
    return 0;
}


/* Take input of coins into a "coin buffer" array
 * Accepts as parameters the coin buffer and the required amount
 * Returns the amount of change owing in cents, or -1 for abort
 */

int accept_payment(int coin_buffer[NUMDENOMS], int required){
    int payment = 0;
    
    while ( payment < required ) {
        int coinval;
        char* coin_input = safe_malloc(sizeof(*coin_input) * 5);

        take_coin_input(coin_input);
        coinval = take_coin(coin_buffer, coin_input);
        free(coin_input);
        if(coinval == 0) {
            printf("Invalid coin denomination.\n");
        } else if (coinval == -1) {
            return -1;        
        } else {
            payment += coinval;
        }
    }

    return payment - required;
}

void dispense_change(struct coin* coins, int change_required) {

    while(change_required > 0) {
        int i;
        for (i = NUMDENOMS - 1; i >= 0; i--) {
            if(coins[i].count > 0 && change_required >= denom_to_int(coins[i].denom)) {
                
                change_required -= denom_to_int(coins[i].denom);
                coins[i].count--;
                break; /* out of for loop */
            }
        }
    }

}
