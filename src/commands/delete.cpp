#include <string>
#include <map>

#include "../constants.h"
#include "../helperfunctions.h"
#include "../userinput.h"
#include "../command.h"
#include "../session.h"
#include "delete.h"
#include "../user.h"
#include "../transaction.h"
#include "../ticketbatch.h"

// Set static members of this class.
const std::string Delete::CommandName = "delete";
const char Delete::TransactionNumber = 2;

/// Constructor method for Delete, takes a session which is the current session in progress.
Delete::Delete( Session* inSession )
{
    userSession = inSession;
}

/// Stub constructor (must exist though)
Delete::Delete()
{}

/// Stub deconstructor (must exist though)
Delete::~Delete()
{
}


/** Checks if the given name is a name that's already being used.
 * @param user input.
 * @return Valid user name or not.
 */
bool Delete::checkEventTitle( std::string input )
{
    // printf("easring for: |%s|\n",input.c_str());
    // TicketBatch bat = Session::AvailableTickets[ input ];
    // printf(" is bat? %p  %s\n",&bat,bat.getEventTitle().c_str());
    for(std::map<std::string,TicketBatch>::iterator iter = Session::AvailableTickets.begin(); iter != Session::AvailableTickets.end(); ++iter)
    {
        std::string key = iter->first;
        if ( key.find(input) ) {
            return true;
        }
    }
    return false;


    // if ( (Session::AvailableTickets.find(input) == Session::AvailableTickets.end()) )
    // {
    //     // not found, therefore it's invalid
    //     return false;
    // }
    // return true;
}

/** Checks if the given name is of valid length defined by 
 * MIN_USERNAME_LENGTH and MAX_USERNAME_LENGTH inclusive
 * @param string input - user input
 * @return bool - Valid user length or not.
 */
bool Delete::checkEventTitleLength( std::string input )
{
    return (input.length() >= MIN_EVENTTITLE_LENGTH && input.length() <= MAX_EVENTTITLE_LENGTH);
}

/** Checks if the given type is a valid user type
 * @param string type - user type
 * @return bool - Valid user type or not.
 */
bool Delete::checkSalePrice( float price )
{
    return inRange( price, MIN_TICKET_PRICE, MAX_TICKET_PRICE );
}

/** Checks if the given credit amount is a valid amount
 * defined by MIN_CREDIT and MAX_CREDIT inclusive
 * @param string input - user input
 * @return bool - Valid user length or not.
 */
bool Delete::checkTicketAmount( int input )
{
    
    if ( getSession()->isAdmin() ){
        return inRange( input , MIN_TICKETS_FOR_SALE , 100 );
    }
    else
    {
        return inRange( input , MIN_TICKETS_FOR_SALE , MAX_TICKETS_TO_BUY );
    }
}

/** Validates that the user input is a valid username. 
 * @param user input.
 * @return Valid user name or not.
 */
// bool Delete::validateUserName( std::string input )
// {
//     if ( Session::AvailableUsers.find(input) == Session::AvailableUsers.end() )
//     {
//         // not found
//         return false;
//     }
//     return true;
// }


/** Processes the delete command.
 * 
 * this entails asking the user for a username to delete as, validating that, and then returning whether the delete was successful. 
 * @return Delete success.
 */
bool Delete::Process()
{
    // Check if the user is an Delete standard user, if they are, exit.
    if ( !getSession()->isAdmin() )
    {
        errorPrintf(DELETE_ERROR_ADMIN_ONLY);
        return false;
    }

    // Loop continuously until we get a valid input.    
    // bool titleSuccess = false;
    // while ( !titleSuccess )
    // {
        
        bool nameSuccess = false;
        // Ask for the sellers name,
        while( !nameSuccess){
            printf( DELETE_PROMPT_NAME );
            // printf( BUY_PROMPT_SELLER_NAME );
            std::string deleteName = UserInput::GetStringInput(MIN_USERNAME_LENGTH,MAX_USERNAME_LENGTH);

            // printf("entetred name: %s\n",deleteName.c_str());
            if ( validateUserName(deleteName) && deleteName != getSession()->getCurrentUser()->getUserName() )
            {
                nameSuccess = true;
                printf( DELETE_PROMPT_SUCCESS );

                Transaction* del = new Transaction();

                del->Delete( GetUserByName( deleteName ) , TransactionNumber );
                getSession()->AddTransaction( del );

                // // printf("is valid name! %s \n" , (eventTitle + deleteName).c_str());
                // if ( checkEventTitle( eventTitle + deleteName ) ) {

                //     // TicketBatch batch = Session::AvailableTickets.find( eventTitle + deleteName )->second;
                //     TicketBatch batch = Session::AvailableTickets[ eventTitle + deleteName ];
                    
                //     if (batch.getQuantityAvailable()>=ticketAmount) {
                    
                //         printf("Cost per Ticket: $%0.2f | Total Cost: $%0.2f\n" , batch.getPrice() , batch.getPrice() * ticketAmount );
                        
                //         bool confirmSuccess = false;
                //         while( !confirmSuccess ){
                //             printf(BUY_PROMPT_CONFIRM);
                //             std::string input = UserInput::GetStringInput(0,10);

                //             if ( input.compare("y") || input.compare("yes") || input.compare("YES") || input.compare("Yes") ) {
                //                 confirmSuccess = amountSuccess = nameSuccess = titleSuccess = true; // valid, stop asking for info.
                //                 if (getSession()->getCurrentUser()->getUserBalance() >= (batch.getPrice() * (float)ticketAmount)) {

                //                     // printf("User %d has been successfully deleted.\n",ticketAmount);
                //                     printf(BUY_PROMPT_SUCCESS);

                //                     // TicketBatch newBatch( eventTitle, salePrice , ticketAmount , getSession()->getCurrentUser() );
                //                     Transaction* delete = new Transaction();

                //                     delete->DeleteTicket( batch , ticketAmount , TransactionNumber );
                //                     getSession()->AddTransaction( delete );
                //                 }
                //                 else
                //                 {
                //                     errorPrintf("You do not have enough credit to purchase these.\n");
                //                 }
                //             }
                //             else if (input.compare("n") || input.compare("no") || input.compare("NO") || input.compare("no") )
                //             {
                //                 printf("Cancelled transaction.\n");
                //             }
                //         }
                //     }
                // }
            }
            else if ( getSession()->getCurrentUser()->getUserName() == deleteName ) {
                errorPrintf(DELETE_ERROR_CANT_DELETE_SELF);
                // return false;
            }
            else 
            {
                errorPrintf(DELETE_ERROR_USER_NOT_EXISTS);
            }
        // }
        // else
        // {
        //     errorPrintf(BUY_ERROR_WRONG_EVENT);
        // }
    }

    return nameSuccess;
}