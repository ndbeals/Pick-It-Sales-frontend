// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <string>
// #include <vector>
// #include <algorithm>
// #include <cstdio>

// #include "Constants.h"
// #include "ticketbatch.h"
// #include "usertransaction.h"
// #include "helperfunctions.h"


// void UserTransaction::buyTicket(const User buyer, const TicketBatch ticketBatch, const int numberOfTickets) {
//     User seller = ticketBatch.getSeller();

//     // check if number of tickets the user wishes to purchase is less than or equal to the number available
//     if (numberOfTickets <= MAX_TICKET_PURCHASE && numberOfTickets <= ticketBatch.getQuantityAvailable()) {
//         // if valid quantity check if buyer has enough credit
//         double totalTicketCost = ticketBatch.getPrice() * numberOfTickets;

//         // if (totalTicketCost > buyer.getCredit() {
//         //     // subtract amount from buyer account

//         //     // add amount to seller account
//         // } else {
//         //     // error buyer does not have enough credit
//         //     errorPrintf("Not enough credit");
//         // }

//         // write to log
//     } else {
//         // error # of tickets invalid
//         if (numberOfTickets > MAX_TICKET_PURCHASE) {
//             errorPrintf("You may only purchase 4 tickets max.");
//         } else {
//             errorPrintf("You do not have enough credit to purchase these.");
//         }
//     }
// }

// void UserTransaction::refund(const User buyer, const User seller, const double amount) {
//     // check if amount to refund is greater than $0.00
//     if (amount > 0) {
//         // add amount to buyer account

//         // subtract amount from seller account

//         // write to log
//     } else {
//         // error
//     }
// }