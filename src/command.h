#ifndef COMMAND_H
#define COMMAND_H

#include <mutex>
#include "session.h"

/** Command is the parent class for all commands (parent to Login, Logout, etc).
 * 
 * It implements some generic, virtual functions that're then overwritten by the children implementations
 */
class Command
{
private:
    /// string name of this command
    static const std::string CommandName;
    /// string number of this command's transaction
    static const char TransactionNumber;
protected:

    Session* userSession;

public:
    // Method block
    /** Constructor method for Command, takes a session which is the current session in progress.
     * @param Session* inSession - in progress session.
     */
    Command( Session* );
    /// Stub constructor (must exist though)
    Command(  );
    /// Stub deconstructor (must exist though)
    virtual ~Command();


    /** Processes the command
     * 
     * this is the function declaration that'll be overwritten by each child to implement their specific functionality.
     * @return Login success.
     */
    virtual bool Process();


    /** Returns the current session this command is attached to.
     * @return Current session.
     */
    Session* getSession() { return userSession; }


    /** Returns the command name of this command ('empty').
     * @return Command name.
     */
    virtual std::string GetCommandName() { return "empty"; }

    /** Returns the transaction number of this command
     * @return Command name.
     */
    const char GetTransactionNumber() { return TransactionNumber; }

    /** Factory function to create commands.
     * @return New Command.
     */
    static Command* GetCommandNameFromInput( std::string , Session* );
};





#endif