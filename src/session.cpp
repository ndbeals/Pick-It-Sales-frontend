#include <string>
#include <iostream>
#include <queue>

#include "userinput.h"
#include "session.h"
#include "constants.h"
#include "helperfunctions.h"
#include "userinput.h"
#include "command.h"
#include "commands/login.h"

/// Session constructor
///  set state to logged out by default
Session::Session(/* args */)
{
    this->sessionState = SessionState::New;
}
/// Stub deconstructor (must exist though)
Session::~Session()
{
}

/// Wrapper function for reading command inputs, also checks for eof on std::cin and exits if true.
	/// @see UserInput::GetCommandInput
void Session::ReadCommandInput()
{
    this->userInput = UserInput::GetCommandInput();/// UserInput::GetStringInput(0 , 25);
    
    if (this->userInput=="exit" || std::cin.eof()){
        exit(0);
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
    while ( this->isLoggedOut() )
    {
        this->ReadCommandInput();

        if ( this->getLastUserInput() == Login::CommandName )
        {

            Login loginCommand = Login( this );

		    bool suc = loginCommand.Process();

            if (suc) {
                // setSessionState( SessionState::User );
                // printf("newstate: %d\n",this->sessionState);
                // printf("name? %s\n",loginCommand.commandName.c_str());
            }
            
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
        // printf("proc man lop\n");
    while( this->isLoggedIn() ){
        // printf("proc man lop\n");
        this->ReadCommandInput();

        Command *currentCommand = Command::GetCommandNameFromInput( this->getLastUserInput() , this );
        currentCommand->Process();

        delete currentCommand;
    }
    
}

/// Log in the user, sets the state to logged in.
bool Session::LogIn( )
{
    // printf("active? %d\n",isActive());
    if ( isActive() && isLoggedOut() )
    {
        setSessionState( SessionState::User );
        return true;
    }
    return false;
}

/// Log the user out, sets the state to logged out.
bool Session::LogOut()
{
    if ( isLoggedIn() ){
        this->setSessionState( SessionState::LoggedOut );
        return true;
    }
    return false;
}


/** Adds a new Transaction to the transaction queue (validTransactions).
 * @param Transaction to store
 */
void Session::AddTransaction( Transaction* validTransaction )
{
    validTransactions.push( validTransaction );
}