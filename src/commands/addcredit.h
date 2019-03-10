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

public:
	/// string name of this command
	static const std::string CommandName;
	/// string number of this command's transaction
	static const char TransactionNumber;

	/// Constructor method for AddCredit, takes a session which is the current session in progress.
	/// @param Current, in progress session.
	AddCredit( Session* );
	/// Stub constructor (must exist though)
	AddCredit() {};
	/// Stub deconstructor (must exist though)
	~AddCredit() {};

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
};


#endif