#include <string>
#include <map>

#include "../constants.h"
#include "../helperfunctions.h"
#include "../userinput.h"
#include "../command.h"
#include "../session.h"
#include "buy.h"
#include "../user.h"
#include "../transaction.h"
#include "../ticketbatch.h"

// Set static members of this class.
const std::string Buy::CommandName = "buy";
const char Buy::TransactionNumber = 3;

/// Constructor method for Buy, takes a session which is the current session in progress.
Buy::Buy( Session* inSession )
{
    userSession = inSession;
}

/// Stub constructor (must exist though)
Buy::Buy()
{}

/// Stub deconstructor (must exist though)
Buy::~Buy()
{
}


/** Checks if the given name is a name that's already being used.
 * @param user input.
 * @return Valid user name or not.
 */
bool Buy::checkEventTitle( std::string input )
{
    if ( (Session::AvailableTickets.find(input) == Session::AvailableTickets.end()) )
    {
        // not found, therefore it's valid
        return true;
    }
    return false;
}

/** Checks if the given name is of valid length defined by 
 * MIN_USERNAME_LENGTH and MAX_USERNAME_LENGTH inclusive
 * @param string input - user input
 * @return bool - Valid user length or not.
 */
bool Buy::checkEventTitleLength( std::string input )
{
    return (input.length() >= MIN_EVENTTITLE_LENGTH && input.length() <= MAX_EVENTTITLE_LENGTH);
}

/** Checks if the given type is a valid user type
 * @param string type - user type
 * @return bool - Valid user type or not.
 */
bool Buy::checkSalePrice( float price )
{
    return inRange( price, MIN_TICKET_PRICE, MAX_TICKET_PRICE );
}

/** Checks if the given credit amount is a valid amount
 * defined by MIN_CREDIT and MAX_CREDIT inclusive
 * @param string input - user input
 * @return bool - Valid user length or not.
 */
bool Buy::checkTicketAmount( int input )
{
    return inRange( input , MIN_TICKETS_FOR_SALE , MAX_TICKETS_FOR_SALE );
}

/** Validates that the user input is a valid username. 
 * @param user input.
 * @return Valid user name or not.
 */
bool Buy::validateUserName( std::string input )
{
    if ( Session::AvailableUsers.find(input) == Session::AvailableUsers.end() )
    {
        // not found
        return false;
    }
    return true;
}


/** Processes the buy command.
 * 
 * this entails asking the user for a username to buy as, validating that, and then returning whether the buy was successful. 
 * @return Buy success.
 */
bool Buy::Process()
{
    // Check if the user is an Buy standard user, if they are, exit.
    if ( getSession()->getCurrentUser()->getUserType() == "SS" )
    {
        errorPrintf(BUY_ERROR_WRONG_ACCOUNT);
        return false;
    }

    // Loop continuously until we get a valid input.    
    bool titleSuccess = false;
    while ( !titleSuccess )
    {
        printf( BUY_PROMPT_EVENT_TILE );
        
        // get user cli input
        std::string eventTitle = UserInput::GetStringInput( MIN_EVENTTITLE_LENGTH , MAX_EVENTTITLE_LENGTH , BUY_ERROR_EVENT_TOO_LONG , BUY_ERROR_EVENT_TOO_SHORT);
        // validate the username is valid to use
        if ( checkEventTitleLength( eventTitle ) )
        {

            bool amountSuccess = false;
            while( !amountSuccess ){
                printf( BUY_PROMPT_NUMBER_TICKETS );
                int max = MAX_TICKETS_TO_BUY;
                if ( getSession()->isAdmin() ){
                    max = 1000;
                }
                int ticketAmount = UserInput::GetIntegerInput(MIN_TICKETS_FOR_SALE, max, BUY_ERROR_MIN_TICKETS , BUY_ERROR_MAX_TICKETS );

                // check if input credit is valid, if so, proceed
                if ( checkTicketAmount( ticketAmount ) ) {

                    bool sellerSuccess = false;
                    while( !sellerSuccess){
                        printf( BUY_PROMPT_SELLER_NAME );
                        std::string sellerName = UserInput::GetStringInput(MIN_USERNAME_LENGTH,MAX_USERNAME_LENGTH);

                        if ( validateUserName(sellerName) )
                        {
                            if ( checkEventTitle( eventTitle + sellerName ) ) {
                                printf("found event! \n");

                                TicketBatch batch = Session::AvailableTickets.find( eventTitle + sellerName )->second;
                                
                                if (batch.getQuantityAvailable()>=ticketAmount) {
                                

                                    printf("Cost per Ticket: $%0.2f | Total Cost: $%0.2f\n" , batch.getPrice() , batch.getPrice() * ticketAmount );
                                    
                                    bool confirmSuccess = false;
                                    while(confirmSuccess){
                                        printf(BUY_PROMPT_CONFIRM);
                                        std::string input = UserInput::GetStringInput(0,10);

                                        if (input.compare("y") || input.compare("yes") || input.compare("YES") || input.compare("Yes") ) {
                                            confirmSuccess = amountSuccess = sellerSuccess = titleSuccess = true; // valid, stop asking for info.

                                            // printf("User %d has been successfully buyd.\n",ticketAmount);
                                            printf(BUY_PROMPT_SUCCESS);

                                            // TicketBatch newBatch( eventTitle, salePrice , ticketAmount , getSession()->getCurrentUser() );
                                            Transaction* buy = new Transaction();

                                            buy->BuyTicket( batch , ticketAmount , TransactionNumber );
                                            getSession()->AddTransaction( buy );
                                        }
                                    }
                                }
                            }
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