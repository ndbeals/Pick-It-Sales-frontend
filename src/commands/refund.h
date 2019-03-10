#ifndef REFUND_H
#define REFUND_H

#include "../command.h"
#include "../session.h"

class User;

/** Refund class is a child of the Command class.
 * 
 * Refund implements functionality specific to loggin into the system, username checking, session state changing, etc
 */ 
class Refund : public Command
{
private:

public:
	/// string name of this command
	static const std::string CommandName;
	/// string number of this command's transaction
	static const char TransactionNumber;

	/// Constructor method for Refund, takes a session which is the current session in progress.
	/// @param Current, in progress session.
	Refund( Session* );
	/// Stub constructor (must exist though)
	Refund() {};
	/// Stub deconstructor (must exist though)
	~Refund() {};

	/** Processes the refund command.
	 * 
	 * this entails asking the user for a username to refund as, validating that, and then returning whether the refund was successful. 
	 * @return Refund success.
	 */
	bool Process();

	/** Returns the command name of this command ('refund').
	 * @return Command name.
	 */
	static const std::string getCommandName() { return CommandName; };

	/** Returns the Transaction Number of this command
	 * @return Transaction number.
	 */
	static const char getTransactionNumber() { return TransactionNumber; };
};


#endif