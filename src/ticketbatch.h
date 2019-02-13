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
    std::string eventTitle; // title of event
    User seller;            // user selling ticketbatch
    double price;           // price of ticketbatch
    int quantityAvailable;  // number of tickets available in a ticketbatch
public:
	TicketBatch();
    TicketBatch(std::string eventTitle, double price, int quantityAvailable);
    
    /**
     * @param string eventTitle - title of event
     * @param integer numberOfTicets - number of tickets the user is looking to purchase
     * @param string sellerName - name of seller
     * @retrn TicketBatch - matching object to criteria passed in the params or empty
     */ 
    TicketBatch find(std::string eventTitle, int numberOfTickets, std::string sellerName);

    /**
     * @return string event title
     */ 
    std::string getEventTitle();

    /**
     * @return User seller
     */ 
    User getSeller();

    /**
     * @return double price
     */ 
    double getPrice();

    /**
     * @return int quantity available
     */ 
    int getQuantityAvailable();

    /**
     * @param integer; number of tickets available
     */ 
    void setQuantityAvailable(int quantityAvailable);
};

#endif