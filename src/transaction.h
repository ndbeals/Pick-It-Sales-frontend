#ifndef USERTRANSACTION_H
#define USERTRANSACTION_H

#include <string>
#include <vector>

#include "ticketbatch.h"
// #include "user.h"
class User;

class Transaction {
private:
	std::string transactionString;
public:
	/// Stub constructor (must exist though)
	Transaction();
	/// Stub deconstructor (must exist though)
	~Transaction();

	/** Logs the user out, creates an end of session transaction
	 * @param User* user - the user
	 * @param char transactionNumber - the transaction number
	 */
	void LogOut( User* , char);

	/** Makes a Create transaction when a user is created
	 * @param User* user - the user
	 * @param char transactionNumber - the transaction number
	 */
	void Create( User* , char );

	/** Makes a Delete transaction when a user is created
	 * @param User* user - the user
	 * @param char transactionNumber - the transaction number
	 */
	void Delete( User* , char );

	/** Process adding credit to user account
	 * @param User user - user account to add credit to
	 * @param double creditToAdd - the amount of credit to add
	*/
	void AddCredit(User* , float , char);

	/** Process the user buy a ticket.
	 * @param User buyer - buyer of ticket
	 * @param TicketBatch ticketBatch - the ticket to purchase
	 * @param int numberOfTickets -number of tickets to buy
	*/
	void BuyTicket( TicketBatch, int, char);

	/** Process refund of a ticket
	 * @param User buyer - user to refund credit to
	 * @param User seller - user to refund credit from
	 * @param float creditAmount - credit transfered between buyer and seller
	*/
	void Refund(User*, User* , float, char);

	/** Process removal of credit from a user account
	 * @param User user - user account to remove credit from
	 * @param double creditToSubtract - the amount of credit to remove
	*/
	void RemoveCredit(User user, double creditToSubtract);

	/** Procces the sale of the ticket
	*/
	void Sell( TicketBatch, char );

	/** Returns the Transaction object's transaction string
	 * @return string transactionString - transaction string of all concatenated transactions
	 */
	std::string getTransactionString() { return this->transactionString; };
	void setTransactionString( std::string newString ) { this->transactionString = newString; };
};

#endif