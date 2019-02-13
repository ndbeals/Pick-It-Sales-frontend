#ifndef USERTRANSACTION_H
#define USERTRANSACTION_H

#include <string>
#include <vector>
#include "user.h"

class Transaction {
private:


public:
	Transaction();
    void addCredit(const User user, const double creditToAdd);
    // void buyTicket(const User buyer, const TicketBatch ticketBatch);
    void removeCredit(User , double );
    void refund(const User buyer, const User seller, const double creditAmount);
};

#endif