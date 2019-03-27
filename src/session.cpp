#include <string>
#include <iostream>
#include <queue>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

#include "user.h"
#include "transaction.h"
#include "userinput.h"
#include "ticketbatch.h"
#include "session.h"
#include "constants.h"
#include "helperfunctions.h"
#include "userinput.h"
#include "command.h"
#include "commands/login.h"
#include "commands/logout.h"


std::map<std::string,class User> Session::AvailableUsers;
std::map<std::string,TicketBatch> Session::AvailableTickets;
std::string Session::UserAccountFile;
std::string Session::AvailableTicketsFile;
std::string Session::DailyTransactionFile;


/** Session default constructor
 * default state to logged out
 */
Session::Session()
{
	this->sessionState = SessionState::New;
}
/// Stub deconstructor (must exist though)
Session::~Session()
{
}

/**
 * GetCommandInput wraps GetStringInput and just prints a text prompt before asking for input, also checks for eof on std::cin and exits if true.
 * @return the user input as a string
 * @see  UserInput::GetStringInput
 */
void Session::ReadCommandInput()
{
	// print the command prompt prefix before asking for input
	printf(COMMAND_PROMPT_PREFIX);
	
	// ask for input
	this->userInput = UserInput::GetStringInput(0,25);
	
	if ( this->userInput=="exit" || std::cin.eof() ){
		exit(0); // exit program if users type exit
	}
}

/** Returns the stored last user input.
 * @return last user Input.
 * @see ReadCommandInput
 */
std::string Session::getLastUserInput()
{
	return this->userInput;
}


/** Prompts user for a command (only accepts 'login'). 
 * 
 * processes that login command, changes the state upon login, then returns control.
 */
void Session::WaitForLogin()
{
	while ( isLoggedOut() )
	{
		ReadCommandInput();

		if ( getLastUserInput() == Login::CommandName )
		{
			Login loginCommand = Login( this );
			// create login  command and process it
			loginCommand.Process();
		}
		else
		{
			errorPrintf(LOGIN_FIRST_PROMPT);
		}
	}
}

/**
 * The "bulk" of the program.
 * 
 * This handles all the other user commands inputs, instantiates command objects to process the input, stores the transactions and writes them out.
 */
void Session::ProcessMainEventLoop()
{
	while( isLoggedIn() ){ // loop forever while logged in
		ReadCommandInput(); // prompt for command input

		// parse string input into a user command
		Command *currentCommand = Command::GetCommandNameFromInput( getLastUserInput() , this );
		// if it's a valid command, the process will do command specific things, if not, process calls a generic error function
		currentCommand->Process();
		// delete the created command
		delete currentCommand;
	}
}


/** Log in the user, sets the state to logged in.
 * @param User* user - user logging in
 * @return bool - if change of the session state for the user logging in was successful or not
 */
bool Session::LogIn( class User* user )
{
	if ( isActive() && isLoggedOut() )
	{
		// set state to logged on, as the appropriate state.
		setSessionState( user->getLoggedInSessionState() );
		setCurrentUser( user );

		return true;
	}
	return false;
}

/** Log the user out, sets the state to logged out.
 * @param User* user - user logging in
 * @return bool - if change of the session state to logged out was successful or not
 */
bool Session::LogOut()
{
	if ( isLoggedIn() ){
		Transaction* logout = new Transaction();

		logout->LogOut( getCurrentUser() , Logout::TransactionNumber );
		AddTransaction( logout );

		WriteTransactionFile();

		// set session state to loggedout and the current user to null.
		setSessionState( SessionState::LoggedOut );
		setCurrentUser( NULL );

		return true;
	}
	return false;
}

/** Read in ticket file to session
 */ 
void Session::ReadTicketsFile()
{
	std::string line;
	std::ifstream ticketsFile ( getFullPath(AvailableTicketsFile) );

	if ( ticketsFile.is_open() )
	{
		while( std::getline( ticketsFile , line ) )
		{
			// Don't add the last line of the file to the list
			if ( trim(line) != END_OF_FILE_LINE )
			{
				TicketBatch batch(line);
				// printf("adding event: %s \n",(batch.getEventTitle() + batch.getSeller()->getUserName()).c_str());
				AvailableTickets.insert( std::pair<std::string,TicketBatch>( (batch.getEventTitle() + batch.getSeller()->getUserName()) ,batch));
			}
		}
	}
	ticketsFile.close();
}

/** Read the available users file and parse it into a map where the keys are the string names and the values are the user objects.
 * @return map< string , User > of available users.
 */
void Session::ReadUsersFile()
{
	std::string line;
	std::ifstream usersFile ( getFullPath( UserAccountFile) );

	if ( usersFile.is_open() )
	{
		while( std::getline( usersFile , line ))
		{
			// create a stringstream of each line
			std::istringstream lineStream(line);

			// three variables used to populate the user object
			std::string name;
			std::string type;
			float balance;

			// read from the line stream
			lineStream >> name >> type >> balance;

			// create the user and insert them into the availableusers map
			class User aUser(name,type,balance);
			
			AvailableUsers.insert(std::pair<std::string,class User>(name,aUser));
		}
	}
}


/** Adds a new Transaction to the transaction queue (validTransactions).
 * @param Transaction* validTransaction - validated Transaction object to store
 */
void Session::AddTransaction( Transaction* validTransaction )
{
	validTransactions.push( validTransaction );
}

/** Process writing trasactions to log file
 */ 
void Session::WriteTransactionFile()
{
	// printf("writing transactions\n");
	
	std::ofstream transactionFile;
	transactionFile.open( Session::DailyTransactionFile , std::ios::out | std::ios::app );

	while( !validTransactions.empty() && transactionFile.is_open() ){
		Transaction* currentTransaction = validTransactions.front();
		std::string trn = currentTransaction->getTransactionString();

		transactionFile << trn.c_str();

		validTransactions.pop();

		// if (!validTransactions.empty()) {
		transactionFile << "\n";
		// }
	}

	transactionFile.close();
	
}