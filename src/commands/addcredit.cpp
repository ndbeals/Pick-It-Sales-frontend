#include <string>
#include <map>

#include "../constants.h"
#include "../helperfunctions.h"
#include "../userinput.h"
#include "../command.h"
#include "../session.h"
#include "addcredit.h"
#include "../user.h"
#include "../transaction.h"
#include "../ticketbatch.h"

// Set static members of this class.
const std::string AddCredit::CommandName = "addcredit";
const char AddCredit::TransactionNumber = 6;

/// Constructor method for AddCredit, takes a session which is the current session in progress.
AddCredit::AddCredit( Session* inSession )
{
    userSession = inSession;
}

/// Stub constructor (must exist though)
AddCredit::AddCredit()
{}

/// Stub deconstructor (must exist though)
AddCredit::~AddCredit()
{
}


/** Checks if the given name is a name that's already being used.
 * @param user input.
 * @return Valid user name or not.
 */
bool AddCredit::checkEventTitle( std::string input )
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
bool AddCredit::checkEventTitleLength( std::string input )
{
    return (input.length() >= MIN_EVENTTITLE_LENGTH && input.length() <= MAX_EVENTTITLE_LENGTH);
}

/** Checks if the given type is a valid user type
 * @param string type - user type
 * @return bool - Valid user type or not.
 */
bool AddCredit::checkSalePrice( float price )
{
    return inRange( price, MIN_TICKET_PRICE, MAX_TICKET_PRICE );
}

/** Checks if the given credit amount is a valid amount
 * defined by MIN_CREDIT and MAX_CREDIT inclusive
 * @param string input - user input
 * @return bool - Valid user length or not.
 */
bool AddCredit::checkTicketAmount( int input )
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
// bool AddCredit::validateUserName( std::string input )
// {
//     if ( Session::AvailableUsers.find(input) == Session::AvailableUsers.end() )
//     {
//         // not found
//         return false;
//     }
//     return true;
// }


/** Processes the addCredit command.
 * 
 * this entails asking the user for a username to addCredit as, validating that, and then returning whether the addCredit was successful. 
 * @return AddCredit success.
 */
bool AddCredit::Process()
{
    // Check if the user is an AddCredit standard user, if they are, exit.
    // if ( !getSession()->isAdmin() )
    // {
        // errorPrintf(REFUND_ERROR_ADMIN_ONLY);
        // return false;
    // }

    // Loop continuously until we get a valid input.    
    User* creditUser = getSession()->getCurrentUser();
    bool userSuccess = !getSession()->isAdmin(); //set this var to false if we admin, forcing us to ask for a username
    
    while( !userSuccess ){
        printf(ADDCREDIT_PROMPT_USERNAME);
        std::string userName = UserInput::GetStringInput(MIN_USERNAME_LENGTH,MAX_USERNAME_LENGTH);

        if ( validateUserName(userName) ) {
            userSuccess = true;
            creditUser = GetUserByName( userName );
        }
        else
        {
            errorPrintf(ADDCREDIT_ERROR_USERNAME);
        }
        
    }

    bool amountSuccess = false;
    while( !amountSuccess )
    {
        printf(ADDCREDIT_PROMPT_AMOUNT);
        float amount = UserInput::GetFloatInput(MIN_CREDIT+0.005f,MAX_ADD_CREDIT,ADDCREDIT_ERROR_AMOUNT_NEG,ADDCREDIT_ERROR_AMOUNT_MAX);

        if ( inRange(amount, MIN_CREDIT+0.005f, MAX_ADD_CREDIT) )
        {
            amountSuccess = true;

            if ( (creditUser->getUserBalance() + amount) <= MAX_CREDIT ) {
                amountSuccess = userSuccess = true;

                printf(ADDCREDIT_PROMPT_SUCCESS);

                Transaction* addCredit = new Transaction();
                
                addCredit->AddCredit( creditUser , amount , TransactionNumber);
                getSession()->AddTransaction(addCredit);
            }
            else
            {
                errorPrintf(ADDCREDIT_ERROR_USER_AT_MAX);
            }
        }
    }


    // bool buyerSuccess = false;
    // while ( !buyerSuccess )
    // {
    //     printf( REFUND_PROMPT_BUYER );
        
    //     // get user cli input
    //     std::string buyerName = UserInput::GetStringInput(MIN_USERNAME_LENGTH,MAX_USERNAME_LENGTH);
    //     // validate the buyer name is valid to use
    //     if ( validateUserName( buyerName ) )
    //     {
    //         bool sellerSuccess = false;
    //         // Ask for the sellers name,
    //         while( !sellerSuccess){
    //             printf( REFUND_PROMPT_SELLER );
    //             std::string sellerName = UserInput::GetStringInput(MIN_USERNAME_LENGTH,MAX_USERNAME_LENGTH);

    //             // printf("entetred name: %s\n",sellerName.c_str());
    //             if ( validateUserName(sellerName) )
    //             {
                   

    //                     User* buyer = GetUserByName( buyerName );
    //                     User* seller = GetUserByName( sellerName );

    //                     if ( seller->getUserBalance() >= amount && inRange(amount,MIN_CREDIT,MAX_CREDIT) ) {
    //                         amountSuccess = amountSuccess = sellerSuccess = buyerSuccess = true; // valid, stop asking for info.
    //                         // printf("User %d has been successfully addCreditd.\n",ticketAmount);
    //                         printf(REFUND_PROMPT_SUCCESS);

    //                         // TicketBatch newBatch( buyerName, salePrice , ticketAmount , getSession()->getCurrentUser() );
    //                         Transaction* addCredit = new Transaction();

    //                         addCredit->AddCredit( buyer , seller , amount , TransactionNumber );
    //                         // addCredit->AddCreditTicket( batch , ticketAmount , TransactionNumber );
    //                         getSession()->AddTransaction( addCredit );
    //                     }
    //                     else if (seller->getUserBalance() < amount)
    //                     {
    //                         errorPrintf(REFUND_ERROR_NOT_ENOUGH_BALANCE);
    //                     }
    //                 }
    //             }   
    //             else 
    //             {
    //                 errorPrintf(REFUND_ERROR_SELLER_NAME);
    //             }
    //         }
    //     }
    //     else
    //     {
    //         errorPrintf(REFUND_ERROR_BUYER_NAME);
    //     }
    // }

    return amountSuccess;
}