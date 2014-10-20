#include "vm_coins.h"
#include "vm_type.h"

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
        denom = str_to_denom(tok);
        tok = strtok(NULL, "\n");
        count = strtol(tok, NULL, 10);
        
        vm->coins[denom].denom = denom;
        vm->coins[denom].count = count;
    }

    fclose(fh);

    return TRUE;
}

enum denomination str_to_denom(char * str) {
    int value;

    value = strtol(str, NULL, 10);

    switch(value) {
    case 1000:
        return TEN_DOLLARS;
    case 500:
        return FIVE_DOLLARS;
    case 200:
        return TWO_DOLLARS;
    case 100:
        return ONE_DOLLAR;
    case 50:
        return FIFTY_CENTS;
    case 20:
        return TWENTY_CENTS;
    case 10:
        return TEN_CENTS;
    case 5:
        return FIVE_CENTS;
    default:
        break;
    }

    return 0;

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
