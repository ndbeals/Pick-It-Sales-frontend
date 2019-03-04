#include <string>
#include <map>

#include "../constants.h"
#include "../helperfunctions.h"
#include "../userinput.h"
#include "../command.h"
#include "../session.h"
#include "create.h"
#include "../user.h"
#include "../transaction.h"

// Set static members of this class.
const std::string Create::CommandName = "create";
const char Create::TransactionNumber = 1;

/** Constructor method for Create
 * takes a session which is the current session in progress.
 * @param Session* inSession - in progress session.
 */ 
Create::Create( Session* inSession )
{
    userSession = inSession;
}

/// Stub constructor (must exist though)
Create::Create()
{}

/// Stub deconstructor (must exist though)
Create::~Create()
{
}


/** Checks if the given name is a name that's already being used.
 * @param string input - user input.
 * @return bool - Valid user name or not.
 */
bool Create::checkUserName( std::string input )
{
    if ( (Session::AvailableUsers.find(input) == Session::AvailableUsers.end()) )
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
bool Create::checkNameLength( std::string input )
{
    return (input.length() >= MIN_USERNAME_LENGTH && input.length() <= MAX_USERNAME_LENGTH);
}

/** Checks if the given type is a valid user type
 * @param string type - user type
 * @return bool - Valid user type or not.
 */
bool Create::checkUserType( std::string type )
{
    if ( type=="AA" || type=="FS" || type=="BS" || type=="SS" ) {
        return true;
    }
    return false;
}

/** Checks if the given credit amount is a valid amount
 * defined by MIN_CREDIT and MAX_CREDIT inclusive
 * @param string input - user input
 * @return bool - Valid user length or not.
 */
bool Create::checkCreditAmount( float input )
{
    return inRange( input , MIN_CREDIT , MAX_CREDIT );
}


/** Processes the create command.
 * 
 * this entails asking the user for a username to create as, validating that, and then returning whether the create was successful. 
 * @return bool - create was successful or not
 */
bool Create::Process()
{
    // Check if the user is an admin, if not, exit.
    if ( !getSession()->isAdmin() )
    {
        errorPrintf(COMMAND_NOT_PERMITTED_ADMIN);
        return false;
    }

    // Loop continuously until we get a valid input.    
    bool nameSuccess = false;
    while ( !nameSuccess )
    {
        printf( CREATE_PROMPT_NEW_NAME );
        
        // get user cli input
        std::string newUsername = UserInput::GetStringInput( MIN_USERNAME_LENGTH , MAX_USERNAME_LENGTH , "Username length must be 15 characters or less.\n" , "Username cannot be empty.\n");

        // validate the username is valid to use
        if ( checkUserName( newUsername ) && checkNameLength( newUsername ) )
        {
            bool typeSuccess = false;
            while( !typeSuccess){
                printf( CREATE_PROMPT_USER_TYPE );
                std::string userType = UserInput::GetStringInput(0,2);

                if ( checkUserType( userType ) )
                {
                    bool creditSuccess = false;
                    while( !creditSuccess ){
                        printf( CREATE_PROMPT_STARTING_CREDITS );
                        float startingCredit = UserInput::GetFloatInput(0, MAX_CREDIT , CREATE_ERROR_CREDITS_LOW , CREATE_ERROR_CREDITS_HIGH );

                        // check if input credit is valid, if so, proceed
                        if ( checkCreditAmount( startingCredit ) ) {
                            creditSuccess = typeSuccess = nameSuccess = true; // credit is valid, stop asking for info.
                            printf("User %s has been successfully created.\n",newUsername.c_str());

                            User newUser( newUsername , userType , startingCredit );
                            Transaction* create = new Transaction();

                            create->Create( &newUser , TransactionNumber );
                            getSession()->AddTransaction( create );
                        }
                        
                    }
                }
                else
                {
                    errorPrintf(CREATE_ERROR_INVALID_TYPE);
                }
            }
        }
        else if ( ! checkUserName( newUsername ) )
        {
            errorPrintf(CREATE_ERROR_NAME_TAKEN);
        }
    }

    return nameSuccess;
}