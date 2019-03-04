#ifndef LOGOUT_H
#define LOGOUT_H

#include "../command.h"
#include "../session.h"

/** Logout class is a child of Command
 * 
 * It implements the logout specific functionality of the logout command, session state changing, etc
 */
class Logout  : public Command
{
private:
    /* data */
public:
    /// string name of this command
    static const std::string CommandName;
    /// string number of this command's transaction
    static const char TransactionNumber;

    // Method Block
    /** Constructor method for Logout, takes a session which is the current session in progress.
     * @param Session* inSession - in progress session.
     */ 
    Logout( Session* );
    /// Stub constructor (must exist though)
    Logout();
    /// Stub deconstructor (must exist though)
    ~Logout();
    
    /** Processes the logout command.
     * 
     * Changes the session state to ended and terminates session.
     * @return Logout success.
     */
    bool Process();

    /** Returns the command name of this command ('logout').
     * @return Command name.
     */
    std::string GetCommandName() { return CommandName; }
};

#endif