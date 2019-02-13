#ifndef USERTRANSACTION_H
#define USERTRANSACTION_H

#include <string>
#include <vector>

#include "ticketbatch.h"
#include "user.h"

class Transaction {
private:

public:
	Transaction();
    ~Transaction();

    /**
     * @param User user - user account to add credit to
     * @param double creditToAdd - the amount of credit to add
    */
    void addCredit(User user, double creditToAdd);

    /**
     * @param User buyer - buyer of ticket
     * @param TicketBatch ticketBatch - the ticket to purchase
     * @param int numberOfTickets -number of tickets to buy
    */
    void buyTicket(User buyer, TicketBatch ticketBatch, int numberOfTickets);

    /**
     * @param User buyer - user to refund credit to
     * @param User seller - user to refund credit from
     * @param double creditAmount - credit transfered between buyer and seller
    */
    void refund(User buyer, User seller, double creditAmount);

    /**
     * @param User user - user account to remove credit from
     * @param double creditToSubtract - the amount of credit to remove
    */
    void removeCredit(User user, double creditToSubtract);

    /**
     * 
    */
    void sell(/* args */);
};

#endif