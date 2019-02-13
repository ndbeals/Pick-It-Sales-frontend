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

Session::~Session()
{
}

void Session::ReadCommandInput()
{
    this->userInput = UserInput::GetCommandInput();/// UserInput::GetStringInput(0 , 25);
    
    if (this->userInput=="exit" || std::cin.eof()){
        exit(0);
    }
}

std::string Session::getLastUserInput()
{
    return this->userInput;
}

// Prompt for a command (login only) until the user has logged in successfully, then we can continue
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

// Session::LogOut
//  
bool Session::LogOut()
{
    if ( isLoggedIn() ){
        this->setSessionState( SessionState::LoggedOut );
        return true;
    }
    return false;
}


// Add transaction adds a valid transaction to the queue
void Session::AddTransaction( Transaction* validTransaction )
{
    validTransactions.push( validTransaction );
}