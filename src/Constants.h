#ifndef CONSTANTS_H
#define CONSTANTS_H

#define ERROR_PREFIX "ERROR: "
// #define ErrorPrintf(...) printf("macro ERROR: %s", ##__VA_ARGS__)
#define MAX_ADD_CREDIT 1000
#define MAX_CREDIT 999999.00
#define MAX_EVENT_TITLE_LENGTH 25
#define MAX_TICKET_PRICE 999.99
#define MAX_TICKET_PURCHASE 4
#define MAX_TICKETS_FOR_SALE 100
#define MAX_USERNAME_LENGTH 15

// TRANSACTIONS
#define T00_END_OF_SESSION "00"
#define T01_CREATE "01"
#define T02_DELETE "02"
#define T03_SELL "03"
#define T04_BUY "04"
#define T05_REFUND "05"
#define T06_ADD_CREDIT "06"

#endif