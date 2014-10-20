/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #2
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller and Virginia King
 * Some codes are adopted here with permission by an anonymous author
 ***********************************************************************/
#ifndef VM_TYPE
#define VM_TYPE

#define NUMDENOMS 8
#define UNUSED(var) (void)var
#define COIN_COUNT 20
#define DEFAULT_ONHAND 20

/* The different denominations of coins available */
enum denomination
{
    FIVE_CENTS, TEN_CENTS, TWENTY_CENTS, FIFTY_CENTS, ONE_DOLLAR, 
    TWO_DOLLARS, FIVE_DOLLARS, TEN_DOLLARS
};

/* Each coin in the coins array will have a denomination (20 cents, 
 * 50 cents, etc) and a count - how many of that coin do we have on hand
 */
struct coin
{
    enum denomination denom;
    unsigned count;
};

/* Type definition for our boolean type */
typedef enum truefalse
{
    FALSE, TRUE
} BOOLEAN;

/* This is the head of our overall data structure. We have a pointer to 
 * the vending machine list as well as an array of coins. 
 */
struct vm
{
    struct vm_list * item_list;
    struct coin coins[NUMDENOMS];
    char * foodfile;
    char * coinsfile;
};

#endif
