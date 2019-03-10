#ifndef BUY_H
#define BUY_H

#include "../command.h"
#include "../session.h"

class User;

/** Buy class is a child of the Command class.
 * 
 * Buy implements functionality specific to loggin into the system, username checking, session state changing, etc
 */ 
class Buy : public Command
{
private:

public:
	/// string name of this command
	static const std::string CommandName;
	/// string number of this command's transaction
	static const char TransactionNumber;

	/// Constructor method for Buy, takes a session which is the current session in progress.
	/// @param Current, in progress session.
	Buy( Session* );
	/// Stub constructor (must exist though)
	Buy() {};
	/// Stub deconstructor (must exist though)
	~Buy() {};

	/** Processes the buy command.
	 * 
	 * this entails asking the user for a username to buy as, validating that, and then returning whether the buy was successful. 
	 * @return Buy success.
	 */
	bool Process();

	/** Returns the command name of this command ('buy').
	 * @return Command name.
	 */
	static const std::string getCommandName() { return CommandName; };

	/** Returns the Transaction Number of this command
	 * @return Transaction number.
	 */
	static const char getTransactionNumber() { return TransactionNumber; };
};


#endif