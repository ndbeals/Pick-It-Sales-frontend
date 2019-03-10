#ifndef CONSTANTS_H
#define CONSTANTS_H

/**
 * Here defines all the global constants we use.
 */


// FILE NAMES
#define USERS_ACCOUNT_FILE "./CurrentUserAccounts.txt"

#define END_OF_FILE_LINE "END"

// STRING CONSTANTS
#define COMMAND_PROMPT_PREFIX "Enter a command: "
#define COMMAND_NOT_PERMITTED_ADMIN "You are not permitted to access this.\n"

#define ERROR_PREFIX "ERROR: "
#define ERROR_COMMAND "invalid command.\n"
#define LOGIN_FIRST_PROMPT "You must login before executing that command.\n"
#define LOGIN_TWICE_ERROR "You are already logged in!\n"

// Create prompts
#define CREATE_PROMPT_NEW_NAME "Enter a new username: "
#define CREATE_PROMPT_USER_TYPE "Enter an account type: "
#define CREATE_PROMPT_STARTING_CREDITS "Enter a credit amount: "
#define CREATE_ERROR_NAME_TAKEN "That name is already in use.\n"
#define CREATE_ERROR_INVALID_TYPE "Account type not recognized.\n"
#define CREATE_ERROR_CREDITS_LOW "Credit amounts must be 0 or greater.\n"
#define CREATE_ERROR_CREDITS_HIGH "Credit amounts must be 999,999.99 or lower.\n"

//Sell Prompts
#define SELL_PROMPT_EVENT_TILE "Enter an Event Title: "
#define SELL_PROMPT_SALE_PRICE "Enter a Sale Price: "
#define SELL_PROMPT_NUMBER_TICKETS "# of Tickets to sell: "
#define SELL_PROMPT_SUCCESS "Successfully created a sale order.\n"
#define SELL_ERROR_WRONG_ACCOUNT "Your account type may not sell tickets.\n"
#define SELL_ERROR_EVENT_TOO_LONG "Event Title too long.\n"
#define SELL_ERROR_EVENT_TOO_SHORT "Empty string not valid as Event Title.\n"
#define SELL_ERROR_PRICE_TOO_HIGH "Price must be below $1000.\n"
#define SELL_ERROR_PRICE_TOO_LOW "Price must be above $0.\n"
#define SELL_ERROR_MAX_TICKETS "# of tickets to sell must be 100 or less.\n"
#define SELL_ERROR_MIN_TICKETS "You cannot sell less than 1 ticket.\n"

//BUY Prompts
#define BUY_PROMPT_EVENT_TILE "Enter an Event Title: "
#define BUY_PROMPT_NUMBER_TICKETS "Enter the amount of tickets to buy: "
#define BUY_PROMPT_SELLER_NAME "Enter the seller's name: "
#define BUY_PROMPT_SUCCESS "Successfully purchased tickets.\n"
#define BUY_PROMPT_CONFIRM "Would you like to purchase this?: "
#define BUY_ERROR_WRONG_EVENT "You must enter a valid title.\n"
#define BUY_ERROR_WRONG_ACCOUNT "Your account type may not buy tickets.\n"
#define BUY_ERROR_EVENT_TOO_LONG "Event Title too long.\n"
#define BUY_ERROR_EVENT_TOO_SHORT "Empty string not valid as Event Title.\n"
#define BUY_ERROR_PRICE_TOO_HIGH "Price must be below $1000.\n"
#define BUY_ERROR_PRICE_TOO_LOW "Price must be above $0.\n"
#define BUY_ERROR_MAX_TICKETS "# of tickets to sell must be 100 or less.\n"
#define BUY_ERROR_MIN_TICKETS "You cannot sell less than 1 ticket.\n"

// DELETE PROmptys
#define DELETE_ERROR_ADMIN_ONLY "Unpriveleged users may not delete users.\n"
#define DELETE_ERROR_USER_NOT_EXISTS "Username does not exist, choose one that exists.\n"
#define DELETE_ERROR_CANT_DELETE_SELF "Cannot delete the logged in account.\n"
#define DELETE_PROMPT_SUCCESS "Successfully deleted the user.\n"
#define DELETE_PROMPT_NAME "Enter a username to delete: "

// REFUND Prompts
#define REFUND_PROMPT_BUYER "Enter the buyer's username: "
#define REFUND_PROMPT_SELLER "Enter the seller's username: "
#define REFUND_PROMPT_AMOUNT "Enter the amount to refund: "
#define REFUND_PROMPT_SUCCESS "Successfully processed the refund.\n"
#define REFUND_ERROR_AMOUNT_NEG "The refund amount must be positive.\n"
#define REFUND_ERROR_ADMIN_ONLY "only admins may issue refunds.\n"
#define REFUND_ERROR_BUYER_NAME "the buyer must exist to refund.\n"
#define REFUND_ERROR_SELLER_NAME "The seller must exist to refund.\n"
#define REFUND_ERROR_NOT_ENOUGH_BALANCE "The seller does not have a sufficent balance to refund the given amount.\n"

//ADDCREDIT prompts
#define ADDCREDIT_PROMPT_AMOUNT "Enter the amount of credit to add: "
#define ADDCREDIT_PROMPT_USERNAME "Enter a username to add credit to: "
#define ADDCREDIT_PROMPT_SUCCESS "Successfully added credit.\n"
#define ADDCREDIT_ERROR_USERNAME "must enter a username that exists to add credit.\n"
#define ADDCREDIT_ERROR_AMOUNT_NEG "credit amount must be over 0.\n"
#define ADDCREDIT_ERROR_AMOUNT_MAX "credit amount must be equal to or under $1000.\n"
#define ADDCREDIT_ERROR_USER_AT_MAX "the user is already at the maximum amount of credit.\n"
// #define ADDCREDIT_

// MIN & MAX VALUES
#define MAX_ADD_CREDIT 1000.0f
#define MAX_CREDIT 999999.99f
#define MIN_CREDIT 0.0f
#define MAX_TICKET_PRICE 999.99f
#define MIN_TICKET_PRICE 0.01f
#define MAX_TICKET_PURCHASE 4
#define MAX_TICKETS_FOR_SALE 100
#define MIN_TICKETS_FOR_SALE 1
#define MAX_TICKETS_TO_BUY 4

#define MAX_USERNAME_LENGTH 15
#define MIN_USERNAME_LENGTH 1

#define MAX_EVENTTITLE_LENGTH 25
#define MIN_EVENTTITLE_LENGTH 1

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

#endif