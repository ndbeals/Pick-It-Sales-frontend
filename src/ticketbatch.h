#ifndef TICKETBATCH_H
#define TICKETBATCJ_H

#include <iostream>
#include <string>
#include <vector>

#include <User.h>

class TicketBatch {
private:
    std::string eventTitle;
    User sellerName;
    double price;
    int quantityAvailable;
public:
	TicketBatch();
    TicketBatch(std::string eventTitle, double price, int quantityAvailable);
    
    TicketBatch find(const std::string eventTitle, const int numberOfTickets, const std::string sellerName);

    std::string getEventTitle();
    User getSeller();
    double getPrice();
    int getQuantityAvailable();

    void setQuantityAvailable(const int quantityAvailable);
};

#endif