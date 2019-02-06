#ifndef TICKETBATCH_H
#define TICKETBATCH_H

#include <iostream>
#include <string>
#include <vector>

#include "user.h"

// #include <user.h>

// class User {};

class TicketBatch {
private:
    std::string eventTitle;
    User seller;
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