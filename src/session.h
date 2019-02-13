#ifndef SESSION_H
#define SESSION_H
#include <queue>
#include <map>
#include "transaction.h"
// #include "command.h"

// forward declare the transaction class for use here.
class Trans;
class Command;

/**
 * \brief Session class manages the session state.
 * 
 * This class manages "the bulk" of the program. 
 * It runs the event loop, asks for user input, passes that input to functions,
 * stores valid transactions, and writes out the files at the end.
 */
class Session
{
	public:
	/// Enum to describe the different session states
	enum SessionState
	{
		/// Error state, shouldn't enter this ever.
		Error,
		/// Newly created state, only true when first constructed.
		New,
		/// Logged in as a normal user state.
		User,
		/// Logged in as an admin state.
		Admin,
		/// logged out (dead session) state.
		LoggedOut,
	};

	/// List of all the available users
	std::map<std::string,Transaction> AvailableUsers;

private:
	/// Store the session's state.
	SessionState sessionState;

	/// The latest input from the user.
	std::string userInput;

	/// Queue of all successful transactions.
	std::queue< Transaction* > validTransactions;
public:
	// Variable block

	// Method block
	/// cosntat
	Session(/* args */);
	~Session();

	/** Prompts user for a command (only accepts 'login'). 
	 * 
	 * processes that login command, changes the state upon login, then returns control.
	 */
	void WaitForLogin();

	/**
	 * The "bulk" of the program.
	 * 
	 * This handles all the other user commands inputs, instantiates command objects to process the input, stores the transactions and writes them out.
	 */
	void ProcessMainEventLoop();

	/** Returns the current state of the session.
	 * @return Current session state.
	 * @see setSessionState
	 */
	SessionState getSessionState() { return sessionState; }
	/// Sets the sessions current state.
	/// @see getSessionState
	void setSessionState( SessionState newState ) { sessionState = newState; }

	/// Wrapper function for reading command inputs, also checks for eof on std::cin and exits if true.
	/// @see UserInput::GetCommandInput
	void ReadCommandInput();

	/** Returns the stored last user input.
	 * @return last user Input.
	 * @see ReadCommandInput
	 */
	std::string getLastUserInput();

	/// Check if user is logged in at all.
	bool isLoggedIn() { return (getSessionState() == SessionState::User || getSessionState() == SessionState::Admin); }
	/// Log in the user, sets the state to logged in.
	bool LogIn();
	
	/// Check if the user has logged out. 
	bool isLoggedOut() { return (getSessionState() == SessionState::LoggedOut || getSessionState() == SessionState::New); }
	/// Log the user out, sets the state to logged out.
	bool LogOut();

	/// Checks if the logged in user is an admin. 
	bool isAdmin() { return (getSessionState() == SessionState::Admin); }
	/// Checks if the state is active (logged in or newly created).
	bool isActive(){ return (isLoggedIn() || getSessionState() == SessionState::New); }

	/** Adds a new Transaction to the transaction queue (validTransactions).
	 * @param Transaction to store
	 */
	void AddTransaction( Transaction* );
};



#endif