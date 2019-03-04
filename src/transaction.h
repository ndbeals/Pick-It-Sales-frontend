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
	Transaction();
    ~Transaction();

    /** LogOut
     * Logs the user out, creates an end of session transaction
     */
    void LogOut( User* , char);

    /** Create
     * makes a Create transactions
     */
    void Create( User* , char );

    /** Process adding credit to user account
     * @param User user - user account to add credit to
     * @param double creditToAdd - the amount of credit to add
    */
    void AddCredit(User user, double creditToAdd);

    /** Process the user buy a ticket.
     * @param User buyer - buyer of ticket
     * @param TicketBatch ticketBatch - the ticket to purchase
     * @param int numberOfTickets -number of tickets to buy
    */
    void BuyTicket(User buyer, TicketBatch ticketBatch, int numberOfTickets);

    /** Process refund of a ticket
     * @param User buyer - user to refund credit to
     * @param User seller - user to refund credit from
     * @param double creditAmount - credit transfered between buyer and seller
    */
    void Refund(User buyer, User seller, double creditAmount);

    /** Process removal of credit from a user account
     * @param User user - user account to remove credit from
     * @param double creditToSubtract - the amount of credit to remove
    */
    void RemoveCredit(User user, double creditToSubtract);

    /** Procces the sale of the ticket
    */
    void Sell(/* args */);

    /// TransactionString
    std::string getTransactionString() { return this->transactionString; };
    void setTransactionString( std::string newString ) { this->transactionString = newString; };
};

#endif