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
	/** Checks if the given ticket count is a valid amount
	 * defined by MIN_TICKETS and MAX_SELL_TICKERS inclusive
	 * @param int input - the ticket count
	 * @return bool - count valid or not
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
	Sell() {};
	/// Stub deconstructor (must exist though)
	~Sell() {};

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
};


#endif