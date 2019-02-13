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

    /**
     * @param User; user account to add credit to
     * @param double; the amount of credit to add
    */
    void addCredit(User user, double creditToAdd);

    /**
     * @param User; buyer
     * @param TicketBatch; the ticket to purchase
     * @param integer; number of tickets to buy
    */
    void buyTicket(User buyer, TicketBatch ticketBatch, int numberOfTickets);

    /**
     * @param User; buyer
     * @param User; seller
     * @param double; credit transfered between buyer and seller
    */
    void refund(User buyer, User seller, double creditAmount);

    /**
     * @param User; user account to remove credit fro
     * @param double; the amount of credit to remove
    */
    void removeCredit(User user, double creditToSubtract);

    /**
     * 
    */
    void sell(/* args */);
};

#endif