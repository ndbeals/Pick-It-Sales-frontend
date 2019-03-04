#ifndef SELL_H
#define SELL_H

#include "../command.h"
#include "../session.h"

class User;

/** Sell class is a child of the Command class.
 * 
 * Sell implements functionality specific to loggin into the system, username checking, session state changing, etc
 */ 
class Sell : public Command
{
private:
    /** Validates that the user input is a valid username. 
     * @param user input.
     * @return Valid user name or not.
     */
    bool checkEventTitle( std::string );

    /** Checks if the given name is of valid length defined by 
     * MIN_USERNAME_LENGTH and MAX_USERNAME_LENGTH inclusive
     * @param string input - user input
     * @return bool - Valid user length or not.
     */
    bool checkEventTitleLength( std::string );

    /** Checks if the given type is a valid user type
     * @param string type - user type
     * @return bool - Valid user type or not.
     */
    bool checkSalePrice( float );
    
    /** Checks if the given credit amount is a valid amount
     * defined by MIN_CREDIT and MAX_CREDIT inclusive
     * @param string input - user input
     * @return bool - Valid user length or not.
     */
    bool checkTicketAmount( int );

public:
    /// string name of this command
    static const std::string CommandName;
    /// string number of this command's transaction
    static const char TransactionNumber;

    /// Constructor method for Sell, takes a session which is the current session in progress.
    /// @param Current, in progress session.
    Sell( Session* );
    /// Stub constructor (must exist though)
    Sell();
    /// Stub deconstructor (must exist though)
    ~Sell();

    /** Processes the sell command.
     * 
     * this entails asking the user for a username to sell as, validating that, and then returning whether the sell was successful. 
     * @return Sell success.
     */
    bool Process();

    /** Returns the command name of this command ('sell').
     * @return Command name.
     */
    static const std::string getCommandName() { return CommandName; };

    /** Returns the Transaction Number of this command
     * @return Transaction number.
     */
    static const char getTransactionNumber() { return TransactionNumber; };


    /** Returns the user that this command will log in
     * @return Sell in User
     */
    User* getLogInUser();
};


#endif