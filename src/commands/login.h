#ifndef LOGIN_H
#define LOGIN_H

// #include <map>

// class Command;
#include "../command.h"
#include "../session.h"

class Login : public Command
{
private:
    /** Validates that the user input is a valid username. 
     * @param username
     */
    bool validateInput( std::string );

public:
    /// string name of this command
    static const std::string CommandName;
    /// string number of this command's transaction
    static const char TransactionNumber;

    /// Constructor method for Login, takes a session which is the current session in progress.
    /// @param Current, in progress session.
    Login( Session* );
    /// Stub constructor (must exist though)
    Login();
    /// Stub deconstructor (must exist though)
    ~Login();

    
    bool Process();

    std::string GetCommandName() { return CommandName; }

    int gettest() {return testes;}
};


#endif