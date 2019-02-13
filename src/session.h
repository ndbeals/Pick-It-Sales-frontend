#ifndef SESSION_H
#define SESSION_H
#include <queue>
#include "transaction.h"

/// ENUM DEF

/**
 * Session class manages the session state.
 * This class manages "the bulk" of the program. 
 * It runs the event loop, asks for user input, passes that input to functions,
 * stores valid transactions, and writes out the files at the end
 */
class Session
{
	public:
	/// This is an enum class
	enum SessionState
	{
		Error,
		New,
		User,
		Admin,
		LoggedOut,
	};
private:
	/// store the session state
	SessionState sessionState;

	/// The latest input from the user.
	std::string userInput;

	// Queue of all successful transactions
	/**
	 * Queue Transaction
	 */
	std::queue< Transaction > validTransactions;
public:
	// Variable block
	int num;

	// Method block
	Session(/* args */);
	~Session();

	// WaitForLogin
	//	Prompts user for a command (only accepts 'login')
	//	process that login command, changes the state upon login, then returns
	void WaitForLogin();

	// ProcessMainEventLoop
	//	The bulk of the program
	//	This handles all the other user commands inputs
	void ProcessMainEventLoop();

	SessionState getSessionState() { return sessionState; }
	void setSessionState( SessionState newState ) { sessionState = newState; }

	// void specialExitConditions();

	void ReadCommandInput();

	std::string getLastUserInput();

	bool isLoggedIn() { return (getSessionState() == SessionState::User || getSessionState() == SessionState::Admin); }
	bool LogIn();
	
	bool isLoggedOut() { return (getSessionState() == SessionState::LoggedOut || getSessionState() == SessionState::New); }
	bool LogOut();

	bool isAdmin() { return (getSessionState() == SessionState::Admin); }

	bool isActive(){ return (isLoggedIn() || getSessionState() == SessionState::New); }

};



#endif