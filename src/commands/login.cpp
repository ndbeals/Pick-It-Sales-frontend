#include <string>
#include <map>

#include "../constants.h"
#include "../helperfunctions.h"
#include "../userinput.h"
#include "../command.h"
#include "login.h"

// Set static members of this class.
const std::string Login::CommandName = "login";
const char Login::TransactionNumber = 1;

/// Constructor method for Login, takes a session which is the current session in progress.
Login::Login( Session* inSession )
{
    userSession = inSession;
}

/// Stub constructor (must exist though)
Login::Login()
{}

/// Stub deconstructor
Login::~Login()
{
}

/** Validates that the user input is a valid username. 
 * @param user name
 */
bool isValidUsername( std::string name )
{
    if ( Session::AvailableUsers.find(name) == Session::AvailableUsers.end() )
    {
        // not found
        return false;
    }
    return true;
}

/** Validates that the user input is a valid username. 
 * @param user input
 */
bool Login::validateInput( std::string input )
{
    if ( isValidUsername( input ) ) 
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Login::Process()
{
    // check if already logged in, if so, print the associated error and return
    if ( getSession()->isLoggedIn() )
    {
        errorPrintf(LOGIN_TWICE_ERROR);
        return true;
    }


    bool success = false;

    printf("Enter a username: ");

    while ( !success )
    {

        std::string username = UserInput::GetStringInput( 0 , 15 );

        if ( this->validateInput( username ) )
        {
            printf("Welcome, %s!\n" , username.c_str() );

            getSession()->LogIn();
            return true;
        }
        else
        {
            printf("Invalid username, try again: ");
            // return false;
        }

        // printf("\n\nYou entered: %s\n",username.c_str());

    }

    return success;
}