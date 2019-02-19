#include <string>

#include "session.h"
#include "user.h"

User::User(/* args */)
{
}
User::User(std::string userName , std::string userType , float balance)
{
    this->userName = userName;
    this->userType = userType;

    this->userBalance = balance;
}


User::~User()
{
}



/** getLoggedInSessionState
 * returns the session state that this user should be when logged in.
 */
Session::SessionState User::getLoggedInSessionState()
{
    if ( this->userType == "AA" ) {
        return Session::SessionState::Admin;
    }
    else
    {
        return Session::SessionState::User;
    }
    
    
}
