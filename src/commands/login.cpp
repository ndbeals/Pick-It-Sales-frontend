#include <string>
#include <map>

#include "../constants.h"
#include "../helperfunctions.h"
#include "../userinput.h"
#include "../command.h"
#include "../session.h"
#include "login.h"
#include "../user.h"

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

/// Stub deconstructor (must exist though)
Login::~Login()
{
}


/** Validates that the user input is a valid username. 
 * @param user input.
 * @return Valid user name or not.
 */
bool Login::validateInput( std::string input )
{
    if ( Session::AvailableUsers.find(input) == Session::AvailableUsers.end() )
    {
        // not found
        return false;
    }
    return true;
}


/** Processes the login command.
 * 
 * this entails asking the user for a username to login as, validating that, and then returning whether the login was successful. 
 * @return Login success.
 */
bool Login::Process()
{
    // check if already logged in, if so, print the associated error and return
    if ( getSession()->isLoggedIn() )
    {
        errorPrintf(LOGIN_TWICE_ERROR);
        return true;
    }

    printf("Enter a username: ");

    // Loop continuously until we get a valid input.    
    bool success = false;
    while ( !success )
    {
        std::string username = UserInput::GetStringInput( 0 , 15 );

        if ( this->validateInput( username ) )
        {
            User* login = &Session::AvailableUsers.find( username )->second;

            printf("Welcome, %s!\n" , login->getUserName().c_str() );

            getSession()->LogIn( login);
            return true;
        }
        else
        {
            printf("Invalid username, try again: ");
        }
    }

    return success;
}