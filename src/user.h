#ifndef USER_H
#define USER_H


#include <string>
#include <vector>

// #include "ticketbatch.h"
#include "session.h"

// enum Session::SessionState;


class User
{
private:
	std::string userName;
	std::string userType;

	float userBalance;
public:
	/// Stub constructor (must exist though)
	User();
	/** User constructor
	 * Set the given username, user type, and account balance
	 * @param string userName - the user's username
	 * @param string userType - the user's account type
	 * @param float balance - the user's account balance
	 */ 
	User(std::string, std::string,float);
	/// Stub deconstructor (must exist though)
	~User();


	/// Getters/setters
	/** setUserType
	 * sets the user's account type to given value
	 * @param string newType - user's account type to be set
	 */
	void setUserType( std::string newType ) { this->userType = newType; };
	/** getUserType
	 * returns the user's account type
	 * @return string userType - user's account type
	 */
	std::string getUserType(){ return this->userType; };

	/** getLoggedInSessionState
	 * returns the session state object that this user should be when logged in.
	 * @return SessionState object based on logged user type (admin or other user)
	 */
	Session::SessionState getLoggedInSessionState();

	/** getUserName
	 * returns the user's username
	 * @return string userName - username
	 */
	std::string getUserName() { return this->userName; };
	/** setUserName
	 * sets the user's username to given value
	 * @param string newName - username to be set to account
	 */
	void setUserName( std::string newName ) { this->userName = newName; };

	/** getUserBalance
	 * returns the user's account balance
	 * @return float userBalance - account balance
	 */
	float getUserBalance() { return this->userBalance; };
	/** setUserBalance
	 * sets the user's account balance to given value
	 * @param float newBalance - new account balance to be set
	 */
	void setUserBalance( float newBalance ) { this->userBalance = newBalance; };
};




#endif