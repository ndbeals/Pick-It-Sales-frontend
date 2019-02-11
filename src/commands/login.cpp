#include <string>
#include <map>

#include "../constants.h"
#include "../helperfunctions.h"
#include "../userinput.h"
#include "../command.h"
#include "login.h"

std::map<std::string,bool> users = {
    {"admin",true},
    {"userFS",true},
    {"userSS",true},
    {"userBS",true},
    {"user",true}
};
// users.insert("admin",true);

const std::string Login::CommandName = "login";
const char Login::TransactionNumber = 1;

Login::Login( Session* inSession )
{
    userSession = inSession;
    testes=2;
}
Login::Login()
{
    // userSession = inSession;
    testes=2;
}

Login::~Login()
{
}

bool isValidUsername( std::string name )
{
    return users[name];
}

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