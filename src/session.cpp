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
#include "session.h"
#include "constants.h"
#include "helperfunctions.h"
#include "userinput.h"
#include "command.h"
#include "commands/login.h"


std::map<std::string,class User> Session::AvailableUsers;
std::string Session::UserAccountFile;
std::string Session::AvailableTicketsFile;
std::string Session::DailyTransactionFile;


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
    
    if ( this->userInput=="exit" || std::cin.eof() ){
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
bool Session::LogIn( class User* user )
{
    // printf("active? %d\n",isActive());
    if ( isActive() && isLoggedOut() )
    {
        // set state to logged on, as the appropriate state.
        setSessionState( user->getLoggedInSessionState() );
        setCurrentUser( user );

        return true;
    }
    return false;
}

/// Log the user out, sets the state to logged out.
bool Session::LogOut()
{
    if ( isLoggedIn() ){
        Transaction* logout = new Transaction();

        logout->LogOut( getCurrentUser() , 0 );
        AddTransaction( logout );

        this->setSessionState( SessionState::LoggedOut );
        setCurrentUser( nullptr );
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

void Session::WriteTransactionFile()
{
    printf("writing transactions\n");
    
    std::ofstream transactionFile;
    transactionFile.open( Session::DailyTransactionFile , std::ios::out | std::ios::app );

    while( !validTransactions.empty() && transactionFile.is_open() ){
        Transaction* currentTransaction = validTransactions.front();
        std::string trn = currentTransaction->getTransactionString();

        transactionFile << trn.c_str();

        printf("writing transaction: %d %s \n",trn.length(),trn.c_str());

        validTransactions.pop();
        // delete currentTransaction;
    }

    transactionFile.close();
    
}