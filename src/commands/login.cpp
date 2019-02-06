#include <string>
#include <map>

#include "../userinput.h"
#include "../command.h"
#include "login.h"

std::map<std::string,bool> users = {
    {"admin",true},
    {"user",true}
};
// users.insert("admin",true);

Login::Login(/* args */)
{
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
    bool success = false;

    printf("Enter a username: ");

    while ( !success )
    {

        std::string username = UserInput::GetStringInput( 0 , 15 );

        if ( this->validateInput( username ) )
        {
            printf("Welcome, %s!\n" , username.c_str() );
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