#include <string>
#include <map>

#include "../constants.h"
#include "../helperfunctions.h"
#include "../userinput.h"
#include "../command.h"
#include "../session.h"
#include "create.h"
#include "../user.h"

// Set static members of this class.
const std::string Create::CommandName = "create";
const char Create::TransactionNumber = 1;

/// Constructor method for Create, takes a session which is the current session in progress.
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
 * @param user input.
 * @return Valid user name or not.
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

bool Create::checkUserType( std::string type )
{
    if ( type=="AA" || type=="FS" || type=="BS" || type=="SS" ) {
        return true;
    }
    return false;
}

bool Create::checkNameLength( std::string input )
{
    return (input.length() >= MIN_USERNAME_LENGTH && input.length() <= MAX_USERNAME_LENGTH);
}


/** Processes the create command.
 * 
 * this entails asking the user for a username to create as, validating that, and then returning whether the create was successful. 
 * @return Create success.
 */
bool Create::Process()
{
    // Check if the user is an admin, if not, exit.
    if ( !getSession()->isAdmin() )
    {
        errorPrintf(COMMAND_NOT_PERMITTED);
        return false;
    }



    // check if already logged in, if so, print the associated error and return
    // if ( getSession()->isLoggedIn() )
    // {
        // errorPrintf(LOGIN_TWICE_ERROR);
        // return true;
    // }


    // Loop continuously until we get a valid input.    
    bool success = false;
    while ( !success )
    {
        printf( CREATE_PROMPT_NEW_NAME );
        
        // get user cli input
        std::string newUsername = UserInput::GetStringInput( MIN_USERNAME_LENGTH , MAX_USERNAME_LENGTH , "Username length must be 15 characters or less.\n" , "Username cannot be empty.\n");
        // printf("Welcome, %s!  l: %d\n" , newUsername.c_str() ,newUsername.length());

        // validate the username is valid to use
        if ( checkUserName( newUsername ) && checkNameLength( newUsername ) )
        {
            printf( CREATE_PROMPT_USER_TYPE );
            std::string userType = UserInput::GetStringInput(0,2);

            if ( checkUserType( userType ) ) {
                printf( CREATE_PROMPT_STARTING_CREDITS );
                float startingCredit = UserInput::GetFloatInput(0,MAX_CREDIT); 
            }
            

            // User* create = &Session::AvailableUsers.find( newUsername )->second;
            // success = getSession()->LogIn( create );

            // if ( success ) 
            // {
                // printf("Welcome, %s!\n" , create->getUserName().c_str() );
            // }
        }
        else if ( !checkUserName( newUsername ) )
        {
            errorPrintf(CREATE_ERROR_NAME_TAKEN);
            // printf("Invalid username, try again: ");
        }
    }

    return success;
}