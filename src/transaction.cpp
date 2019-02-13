#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>

#include "constants.h"
#include "helperfunctions.h"
#include "ticketbatch.h"
#include "transaction.h"
#include "userinput.h"


/** Process the user buy a ticket.
 * @param User buyer - buyer of ticket
 * @param TicketBatch ticketBatch - the ticket to purchase
 * @param int numberOfTickets -number of tickets to buy
*/
void Transaction::buyTicket(User buyer, TicketBatch ticketBatch, int numberOfTickets) {
    User seller = ticketBatch.getSeller();
    bool validAmount = numberOfTickets > 0 && 
    numberOfTickets <= MAX_TICKET_PURCHASE && 
    numberOfTickets <= ticketBatch.getQuantityAvailable();
 
    // check if number of tickets the user wishes to purchase is less than or equal to the number available
    if (validAmount) {
        // if valid quantity check if buyer has enough credit
        double totalTicketCost = ticketBatch.getPrice() * numberOfTickets;s

        // write to transaction log
    } else {
        // error # of tickets invalid
        if (numberOfTickets > MAX_TICKET_PURCHASE) {
            errorPrintf("You may only purchase 4 tickets max.");
        } else {
            errorPrintf("You do not have enough credit to purchase these.");
        }
    }
}

/**
 * Process refund of ticket(s)
 */ 
void Transaction::refund(User buyer, User seller, double amount) {
    // check if amount to refund is greater than $0.00
    if (amount > 0) {
        // add amount to buyer account

        // subtract amount from seller account

        // write to log
    } else {
        // error
    }
}

Transaction::Transaction()
{
    
}

Transaction::~Transaction()
{

}