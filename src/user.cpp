#include <string>

#include "session.h"
#include "user.h"

/// Stub constructor (must exist though)
User::User()
{
}
/** User constructor
 * Set the given username, user type, and account balance
 * @param string userName - the user's username
 * @param string userType - the user's account type
 * @param float balance - the user's account balance
 */ 
User::User(std::string newUserName , std::string newUserType , float newBalance)
{
	this->userName = newUserName;
	this->userType = newUserType;

	this->userBalance = newBalance;
}

/// Stub deconstructor (must exist though)
User::~User()
{
}


/** getLoggedInSessionState
 * returns the session state object that this user should be when logged in.
 * @return SessionState object based on logged user type (admin or other user)
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
