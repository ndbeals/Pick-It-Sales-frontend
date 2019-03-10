#ifndef COMMAND_H
#define COMMAND_H

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
	// The session this command is running in.
	Session* userSession;

	/** Checks if the given ticket count is a valid amount
     * defined by MIN_TICKETS and MAX_SELL_TICKERS inclusive
     * @param int input - the ticket count
     * @return bool - count valid or not
     */
    bool checkTicketAmount( int );

	/** Validates that the user input is a valid username. 
	 * @param user input.
	 * @return Valid user name or not.
	 */
	bool validateUserName( std::string );

	/** Checks if the given sale price is valid or not
	 * @param float price - sale price
	 * @return bool - Valid price?.
	 */
	bool checkSalePrice( float );

	/** Checks if the given name is a name that's already being used.
	 * @param user input.
	 * @return Valid user name or not.
	 */
	bool checkEventTitle( std::string );

	/** Checks if the given name is of valid length defined by 
	 * MIN_EVENTTITLE_LENGTH and MAX_EVENTTITLE_LENGTH inclusive
	 * @param string input - user input
	 * @return bool - Valid length or not.
	 */
	bool checkEventTitleLength( std::string );

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

	/** Gets a user object with the given name;
	 * @param user name
	 * @return valid user object
	 */
	User* GetUserByName( std::string );

	/** Processes the command
	 * 
	 * this is the function declaration that'll be overwritten by each child to implement their specific functionality.
	 * @return bool - whether or not the Login was successful.
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
	 * @param string commandName - name of command
	 * @param Session* session - current session
	 * @return New Command.
	 */
	static Command* GetCommandNameFromInput( std::string , Session* );
};


#endif