#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "session.h"
#include "helperfunctions.h"
#include "user.h"
#include "ticketbatch.h"

/** TicketBatch default constructor
 * default price and quantityAvailable to 0
 */
TicketBatch::TicketBatch() {
	this->price = 0;
	this->quantityAvailable = 0;
}

/** TicketBatch constructor
 * Set given event title, price, and quantity available
 * @param string event title - title of ticket event
 * @param float price - price of ticket
 * @param int quantityAvailable - quantity of tickets available
 */
TicketBatch::TicketBatch(std::string newEventTitle, float newPrice, int newQuantity , User* newSeller) {
	this->eventTitle = newEventTitle;
	this->price = newPrice;
	this->quantityAvailable = newQuantity;
	this->seller = newSeller;
}

/** TicketBatch constructor
 * Set event title, seller, price, and quantity available based on given file line
 * @param string fileLine
 */
TicketBatch::TicketBatch(std::string fileLine) {
	// Cut out and trim the spaces off the different fields in each line
	this->eventTitle = trim( fileLine.substr(0,25) );
	this->seller = &Session::AvailableUsers.find( trim( fileLine.substr(26,15) ) )->second;
	this->quantityAvailable = std::stoi( trim( fileLine.substr(42,3) ) );
	this->price				= std::stof( trim( fileLine.substr(46,6) ) );
}

/** Finds matching ticket object based on search parameters
 * @param string eventTitle - title of event
 * @param int numberOfTicets - number of tickets the user is looking to purchase
 * @param string sellerName - name of seller
 * @return TicketBatch - matching object to criteria passed in the params or empty
 */ 
TicketBatch TicketBatch::find(const std::string title, const int numberOfTickets, const std::string sellerName) {
	TicketBatch ticket;

	for (auto &event : Session::AvailableTickets) {
		
		if ((event.first == title + sellerName) && event.second.getQuantityAvailable() >= numberOfTickets) {
			ticket = event.second;
			break;
		}
	}

	// return TicketBatch obj
	return ticket;
}

/** Returns event title of ticket
 * @return string event title
 */ 
std::string TicketBatch::getEventTitle() {
	return this->eventTitle;
}

/** Returns ticket price
 * @return float price
 */ 
float TicketBatch::getPrice(){
	return this->price;
}

/** Returns quantity of tickets available
 * @return int quantity available
 */ 
int TicketBatch::getQuantityAvailable(){
	return this->quantityAvailable;
}

/** Sets value for quantity of tickets available
 * @param int quantityAvailable - number of tickets available
 */ 
void TicketBatch::setQuantityAvailable( int quantity) {
	this->quantityAvailable = quantity;
}

