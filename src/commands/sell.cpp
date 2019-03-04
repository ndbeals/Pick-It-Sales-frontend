#include <string>
#include <map>

#include "../constants.h"
#include "../helperfunctions.h"
#include "../userinput.h"
#include "../command.h"
#include "../session.h"
#include "sell.h"
#include "../user.h"
#include "../transaction.h"
#include "../ticketbatch.h"

// Set static members of this class.
const std::string Sell::CommandName = "sell";
const char Sell::TransactionNumber = 3;

/** Constructor method for Sell, takes a session which is the current session in progress.
 * @param Session* inSession - in progress session.
 */ 
Sell::Sell( Session* inSession )
{
    userSession = inSession;
}

/// Stub constructor (must exist though)
Sell::Sell()
{}

/// Stub deconstructor (must exist though)
Sell::~Sell()
{
}


/** Checks if the given name is a name that's already being used.
 * @param user input.
 * @return Valid user name or not.
 */
bool Sell::checkEventTitle( std::string input )
{
    if ( (Session::AvailableTickets.find(input) == Session::AvailableTickets.end()) )
    {
        // not found, therefore it's valid
        return true;
    }
    return false;
}

/** Checks if the given event name is of valid length defined by 
 * MIN_EVENTTITLE_LENGTH and MAX_EVENT_TITLE_LENGTH inclusive
 * @param string input - user input
 * @return bool - Valid user length or not.
 */
bool Sell::checkEventTitleLength( std::string input )
{
    return (input.length() >= MIN_EVENTTITLE_LENGTH && input.length() <= MAX_EVENTTITLE_LENGTH);
}

/** Checks if the given ticket sale price is valid or not
 * @param float price - sale price
 * @return bool - Valid sale price or not
 */
bool Sell::checkSalePrice( float price )
{
    return inRange( price, MIN_TICKET_PRICE, MAX_TICKET_PRICE );
}

/** Checks if the given ticket amount is a valid amount
 * defined by MIN_TICKETS_FOR_SALE and MAX_TICKETS_FOR_SALE inclusive
 * @param int input - user input
 * @return bool - Valid quantity of tickets for sale
 */
bool Sell::checkTicketAmount( int input )
{
    return inRange( input , MIN_TICKETS_FOR_SALE , MAX_TICKETS_FOR_SALE );
}


/** Processes the sell command.
 * 
 * this entails asking the user for a username to sell as, validating that, and then returning whether the sell was successful. 
 * @return Sell success.
 */
bool Sell::Process()
{
    // Check if the user is an Buy standard user, if they are, exit.
    if ( getSession()->getCurrentUser()->getUserType() == "BS" )
    {
        errorPrintf(SELL_ERROR_WRONG_ACCOUNT);
        return false;
    }

    // Loop continuously until we get a valid input.    
    bool titleSuccess = false;
    while ( !titleSuccess )
    {
        printf( SELL_PROMPT_EVENT_TILE );
        
        // get user cli input
        std::string eventTitle = UserInput::GetStringInput( MIN_EVENTTITLE_LENGTH , MAX_EVENTTITLE_LENGTH , SELL_ERROR_EVENT_TOO_LONG , SELL_ERROR_EVENT_TOO_SHORT);
        // validate the username is valid to use
        if ( checkEventTitleLength( eventTitle ) )
        {
            bool priceSuccess = false;
            while( !priceSuccess){
                printf( SELL_PROMPT_SALE_PRICE );
                float salePrice = UserInput::GetFloatInput(MIN_TICKET_PRICE,MAX_TICKET_PRICE,SELL_ERROR_PRICE_TOO_LOW,SELL_ERROR_PRICE_TOO_HIGH);

                if ( checkSalePrice( salePrice ) )
                {
                    bool amountSuccess = false;
                    while( !amountSuccess ){
                        printf( SELL_PROMPT_NUMBER_TICKETS );
                        int ticketAmount = UserInput::GetIntegerInput(MIN_TICKETS_FOR_SALE, MAX_TICKETS_FOR_SALE , SELL_ERROR_MIN_TICKETS , SELL_ERROR_MAX_TICKETS );

                        // check if input credit is valid, if so, proceed
                        if ( checkTicketAmount( ticketAmount ) ) {
                            amountSuccess = priceSuccess = titleSuccess = true; // credit is valid, stop asking for info.
                            // printf("User %d has been successfully selld.\n",ticketAmount);
                            printf(SELL_PROMPT_SUCCESS);

                            TicketBatch newBatch( eventTitle, salePrice , ticketAmount , getSession()->getCurrentUser() );
                            Transaction* sell = new Transaction();

                            sell->Sell( newBatch , TransactionNumber );
                            getSession()->AddTransaction( sell );
                        }
                        
                    }
                }
                // else
                // {
                    // errorPrintf(CREATE_ERROR_INVALID_TYPE);
                // }
            }
        }
        else if ( ! checkEventTitle( eventTitle ) )
        {
            errorPrintf(CREATE_ERROR_NAME_TAKEN);
        }
    }

    return titleSuccess;
}