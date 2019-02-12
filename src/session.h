#ifndef SESSION_H
#define SESSION_H

enum SessionState
{
	Error,
	New,
	User,
	Admin,
	LoggedOut,
};

class Session
{
private:
	// store the session state
	SessionState sessionState;

	std::string userInput;
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

	void specialExitConditions();

	void readCommandInput();

	std::string getLastUserInput();

	bool isLoggedIn() { return (getSessionState() == SessionState::User || getSessionState() == SessionState::Admin); }
	void LogIn();
	bool isLoggedOut() { return (getSessionState() == SessionState::LoggedOut || getSessionState() == SessionState::New); }
	void LogOut();

	bool isAdmin() { return (getSessionState() == SessionState::Admin); }

	bool isActive(){ return (isLoggedIn() || getSessionState() == SessionState::New); }

};



#endif