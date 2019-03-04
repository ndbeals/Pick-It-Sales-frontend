#ifndef TICKETBATCH_H
#define TICKETBATCH_H

#include <iostream>
#include <string>
#include <vector>

class User ;
// #include "user.h"

class TicketBatch {
private:
    std::string eventTitle; // title of event
    User* seller;   // user selling ticketbatch
    float price;           // price of ticketbatch
    int quantityAvailable;  // number of tickets available in a ticketbatch
public:
	TicketBatch();
    TicketBatch(std::string eventTitle, float price, int quantityAvailable);
    TicketBatch(std::string fileLine );
    
    /**
     * Find matching ticket object(s) based on search parameters
     * @param string eventTitle - title of event
     * @param int numberOfTicets - number of tickets the user is looking to purchase
     * @param string sellerName - name of seller
     * @return TicketBatch - matching object to criteria passed in the params or empty
     */ 
    TicketBatch find(std::string eventTitle, int numberOfTickets, std::string sellerName);

    /**
     * Returns event title of ticket
     * @return string event title
     */ 
    std::string getEventTitle();

    /** Get seller user object
     * @return User seller
     */ 
    User* getSeller() { return this->seller; };

    /** Returns ticket price
     * @return float price
     */ 
    float getPrice();

    /** Returns quantity of tickets available
     * @return int quantity available
     */ 
    int getQuantityAvailable();

    /** Sets value for quantity of tickets available
     * @param int quantityAvailable - number of tickets available
     */ 
    void setQuantityAvailable(int quantityAvailable);
};

#endif