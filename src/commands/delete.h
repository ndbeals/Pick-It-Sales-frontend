#ifndef DELETE_H
#define DELETE_H

#include "../command.h"
#include "../session.h"

class User;

/** Delete class is a child of the Command class.
 * 
 * Delete implements functionality specific to loggin into the system, username checking, session state changing, etc
 */ 
class Delete : public Command
{
private:

public:
	/// string name of this command
	static const std::string CommandName;
	/// string number of this command's transaction
	static const char TransactionNumber;

	/// Constructor method for Delete, takes a session which is the current session in progress.
	/// @param Current, in progress session.
	Delete( Session* );
	/// Stub constructor (must exist though)
	Delete() {};
	/// Stub deconstructor (must exist though)
	~Delete() {};

	/** Processes the delete command.
	 * 
	 * this entails asking the user for a username to delete as, validating that, and then returning whether the delete was successful. 
	 * @return Delete success.
	 */
	bool Process();

	/** Returns the command name of this command ('delete').
	 * @return Command name.
	 */
	static const std::string getCommandName() { return CommandName; };

	/** Returns the Transaction Number of this command
	 * @return Transaction number.
	 */
	static const char getTransactionNumber() { return TransactionNumber; };
};


#endif