#ifndef CONSTANTS_H
#define CONSTANTS_H

/**
 * Here defines all the global constants we use.
 */


// FILE NAMES
#define USERS_ACCOUNT_FILE "./CurrentUserAccounts.txt"

// STRING CONSTANTS
#define COMMAND_PROMPT_PREFIX "Enter a command: "
#define ERROR_PREFIX "ERROR: "
#define ERROR_COMMAND "invalid command.\n"
#define LOGIN_FIRST_PROMPT "You must login before executing that command.\n"
#define LOGIN_TWICE_ERROR "You are already logged in!\n"

// MIN & MAX VALUES
#define MAX_ADD_CREDIT 1000
#define MAX_CREDIT 999999.00
#define MAX_EVENT_TITLE_LENGTH 25
#define MAX_TICKET_PRICE 999.99
#define MAX_TICKET_PURCHASE 4
#define MAX_TICKETS_FOR_SALE 100
#define MAX_USERNAME_LENGTH 15

// TRANSACTION TYPES
enum TRANSACTION {
    T00_END_OF_SESSION = 00,
    T01_CREATE = 01,
    T02_DELETE = 02,
    T03_SELL = 03,
    T04_BUY = 04,
    T05_REFUND = 05,
    T06_ADD_CREDIT = 06
};

// const boost::map<const char*, TRANSACTION> commandToTransaction = boost::assign::map_list_of
//     ("exit", T00_END_OF_SESSION)
//     ("create", T01_CREATE)
//     ("delete",T02_DELETE)
//     ("sell", T03_SELL)
//     ("buy", T04_BUY)
//     ("refund", T05_REFUND)
//     ("addcredit", T06_ADD_CREDIT)
// ;

#endif