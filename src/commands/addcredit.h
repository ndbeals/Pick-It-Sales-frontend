#ifndef ADDCREDIT_H
#define ADDCREDIT_H

#include "../command.h"
#include "../session.h"

class User;

/** AddCredit class is a child of the Command class.
 * 
 * AddCredit implements functionality specific to loggin into the system, username checking, session state changing, etc
 */ 
class AddCredit : public Command
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

    /** Validates that the user input is a valid username. 
     * @param user input.
     * @return Valid user name or not.
     */
    // bool validateUserName( std::string );

public:
    /// string name of this command
    static const std::string CommandName;
    /// string number of this command's transaction
    static const char TransactionNumber;

    /// Constructor method for AddCredit, takes a session which is the current session in progress.
    /// @param Current, in progress session.
    AddCredit( Session* );
    /// Stub constructor (must exist though)
    AddCredit();
    /// Stub deconstructor (must exist though)
    ~AddCredit();

    /** Processes the addCredit command.
     * 
     * this entails asking the user for a username to addCredit as, validating that, and then returning whether the addCredit was successful. 
     * @return AddCredit success.
     */
    bool Process();

    /** Returns the command name of this command ('addCredit').
     * @return Command name.
     */
    static const std::string getCommandName() { return CommandName; };

    /** Returns the Transaction Number of this command
     * @return Transaction number.
     */
    static const char getTransactionNumber() { return TransactionNumber; };


    /** Returns the user that this command will log in
     * @return AddCredit in User
     */
    User* getLogInUser();
};


#endif