#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "session.h"
#include "helperfunctions.h"
#include "user.h"
#include "ticketbatch.h"

TicketBatch::TicketBatch() {
	this->price = 0;
	this->quantityAvailable = 0;
}

TicketBatch::TicketBatch(std::string eventTitle, float price, int quantityAvailable) {
	this->eventTitle = eventTitle;
	this->price = price;
	this->quantityAvailable = quantityAvailable;
}


TicketBatch::TicketBatch(std::string fileLine) {
	// Cut out and trim the spaces off the different fields in each line
	this->eventTitle = trim( fileLine.substr(0,25) );
	this->seller = &Session::AvailableUsers.find( trim( fileLine.substr(26,39) ) )->second;
	this->quantityAvailable = std::stoi( trim( fileLine.substr(40,43) ) );
	this->price				= std::stof( trim( fileLine.substr(44,50) ) );
}

/**
 * @param string eventTitle - title of event
 * @param int numberOfTicets - number of tickets the user is looking to purchase
 * @param string sellerName - name of seller
 * @return TicketBatch - matching object to criteria passed in the params or empty
 */ 
TicketBatch TicketBatch::find(const std::string eventTitle, const int numberOfTickets, const std::string sellerName) {
	TicketBatch ticket;

	// find TicketBatch obj
	// if found, set TicketBatch obj

	
	// return TicketBatch obj
	return ticket;
}

/**
 * @return string event title
 */ 
std::string TicketBatch::getEventTitle() {
	return this->eventTitle;
}

/**
 * @return User seller
 */ 
// User TicketBatch::getSeller() {
	// return this->seller;
// }

/**
 * @return float price
 */ 
float TicketBatch::getPrice(){
	// return this->price;
}

/**
 * @return int quantity available
 */ 
int TicketBatch::getQuantityAvailable(){
	this->quantityAvailable;
}

/**
     * @param int quantityAvailable - number of tickets available
     */ 
void TicketBatch::setQuantityAvailable(const int quantityAvailable) {
	this->quantityAvailable = quantityAvailable;
}

