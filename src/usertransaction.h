#ifndef USERTRANSACTION_H
#define USERTRANSACTION_H

#include <string>
#include <vector>

class UserTransaction {
private:


public:
	UserTransaction();
    void addCredit(const User user, const double creditToAdd);
    void buyTicket(const User buyer, const TicketBatch ticketBatch);
    void removeCredit(const User user, const double creditToSubtract);
    void refund(const User buyer, const User seller, const double creditAmount);
};

#endif