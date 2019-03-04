#ifndef CREATE_H
#define CREATE_H

#include "../command.h"
#include "../session.h"

class User;

/** Create class is a child of the Command class.
 * 
 * Create implements functionality specific to loggin into the system, username checking, session state changing, etc
 */ 
class Create : public Command
{
private:
    /** Validates that the user input is a valid username. 
     * @param user input.
     * @return Valid user name or not.
     */
    bool checkUserName( std::string );

    bool checkUserType( std::string );

    bool checkNameLength( std::string );
    
    bool checkCreditAmount( float );

public:
    /// string name of this command
    static const std::string CommandName;
    /// string number of this command's transaction
    static const char TransactionNumber;

    /// Constructor method for Create, takes a session which is the current session in progress.
    /// @param Current, in progress session.
    Create( Session* );
    /// Stub constructor (must exist though)
    Create();
    /// Stub deconstructor (must exist though)
    ~Create();

    /** Processes the create command.
     * 
     * this entails asking the user for a username to create as, validating that, and then returning whether the create was successful. 
     * @return Create success.
     */
    bool Process();

    /** Returns the command name of this command ('create').
     * @return Command name.
     */
    static const std::string getCommandName() { return CommandName; };

    /** Returns the Transaction Number of this command
     * @return Transaction number.
     */
    static const char getTransactionNumber() { return TransactionNumber; };


    /** Returns the user that this command will log in
     * @return Create in User
     */
    User* getLogInUser();
};


#endif