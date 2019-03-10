#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>

#include "user.h"
#include "constants.h"
#include "helperfunctions.h"
#include "ticketbatch.h"
#include "transaction.h"
#include "userinput.h"

#include "format.cc"
#include "fmt/format.h"



/** Logs the user out, creates an end of session transaction
 * @param User* user - the user
 * @param char transactionNumber - the transaction number
 */
void Transaction::LogOut( class User* user , char transactionNumber )
{
    // printf("logging out: %s\n",user->getUserName().c_str());

    // this->transactionString =  "00_" + user->getUserName();
    this->transactionString = fmt::format("{0:02d} {1:<15} {2:2} {3:#09.2f}",transactionNumber,user->getUserName(),user->getUserType(),user->getUserBalance());
    // this->transactionString = fmt::format("{0} {1:<15}","00",user->getUserName());
    // printf("length: %d  %s\n",this->transactionString.length(),getTransactionString().c_str());

}

/** Makes a Create transaction when a user is created
 * @param User* user - the user
 * @param char transactionNumber - the transaction number
 */
void Transaction::Create( class User* user , char transactionNumber )
{
    this->transactionString = fmt::format("{0:02d} {1:<15} {2:2} {3:#09.2f}",transactionNumber,user->getUserName(),user->getUserType(),user->getUserBalance());
}

void Transaction::Sell( TicketBatch sellBatch , char transactionNumber)
{
    // printf("sell? %d %s %s %d %f\n",transactionNumber,sellBatch.getEventTitle().c_str(),sellBatch.getSeller()->getUserName().c_str(),sellBatch.getQuantityAvailable(),sellBatch.getPrice());
    this->transactionString = fmt::format("{0:02d} {1:<25} {2:<15} {3:<3} {4:#06.2f}",transactionNumber,sellBatch.getEventTitle(),sellBatch.getSeller()->getUserName(),sellBatch.getQuantityAvailable(),sellBatch.getPrice());
    // printf("TRAN STR: %d \n",sellBatch.getQuantityAvailable())a;
}

/** Process the user buy a ticket.
 * @param User buyer - buyer of ticket
 * @param TicketBatch ticketBatch - the ticket to purchase
 * @param int numberOfTickets -number of tickets to buy
*/
void Transaction::BuyTicket(TicketBatch sellBatch, int buyAmount, char transactionNumber) 
{
    this->transactionString = fmt::format("{0:02d} {1:<25} {2:<15} {3:03d} {4:#06.2f}",transactionNumber,sellBatch.getEventTitle(),sellBatch.getSeller()->getUserName(),buyAmount,sellBatch.getPrice());
}

/** Process refund of a ticket
 * @param User buyer - user to refund credit to
 * @param User seller - user to refund credit from
 * @param double creditAmount - credit transfered between buyer and seller
*/
void Transaction::Refund(class User buyer, User seller, double amount) {
    // check if amount to refund is greater than $0.00
    if (amount > 0) {
        // add amount to buyer account

        // subtract amount from seller account

        // write to log
    } else {
        // error
    }
}

/// Stub constructor (must exist though)
Transaction::Transaction()
{
    
}

/// Stub deconstructor (must exist though)
Transaction::~Transaction()
{

}