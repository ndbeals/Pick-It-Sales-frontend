#include <string>
#include <iostream>

#include "userinput.h"
#include "session.h"
#include "constants.h"
#include "helperfunctions.h"
#include "userinput.h"
#include "command.h"
#include "commands/login.h"

// Session constructor
//  set state to logged out by default
Session::Session(/* args */)
{
    this->sessionState = SessionState::New;
}

Session::~Session()
{
}

void Session::specialExitConditions()
{
    if (this->userInput=="exit" || std::cin.eof()){
        exit(0);
    }
}

void Session::getCommandInput()
{
    this->userInput = UserInput::GetCommandInput();//UserInput::GetStringInput(0 , 25);
}

// Prompt for a command (login only) until the user has logged in successfully, then we can continue
void Session::WaitForLogin()
{
    while ( this->isLoggedOut() )
    {
        this->getCommandInput();

        if ( this->userInput == Login::CommandName )
        {
            // printf("static worked\n");

            this->specialExitConditions();

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
        this->getCommandInput();

        this->specialExitConditions();

        Command *currentCommand = Command::GetCommandNameFromInput( this->userInput , this );
        currentCommand->Process();

        delete currentCommand;
    }
    
}

void Session::LogIn( )
{
    // printf("active? %d\n",isActive());
    if ( isActive() && isLoggedOut() )
    {
        setSessionState( SessionState::User );
    }
}

void Session::LogOut()
{
    if ( isLoggedIn() ){
        this->setSessionState( SessionState::LoggedOut );
    }
}