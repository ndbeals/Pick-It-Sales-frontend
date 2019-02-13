#ifndef LOGIN_H
#define LOGIN_H

#include "../command.h"
#include "../session.h"

/** Login class is a child of the Command class.
 * 
 * Login implements functionality specific to loggin into the system, username checking, session state changing, etc
 */ 
class Login : public Command
{
private:
    /** Validates that the user input is a valid username. 
     * @param user input.
     * @return Valid user name or not.
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

    /** Processes the login command.
     * 
     * this entails asking the user for a username to login as, validating that, and then returning whether the login was successful. 
     * @return Login success.
     */
    bool Process();

    /** Returns the command name of this command ('login').
     * @return Command name.
     */
    std::string GetCommandName() { return CommandName; }

};


#endif