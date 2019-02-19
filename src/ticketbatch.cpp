#include <iostream>
#include <string>
#include <fstream>
#include <string>

#include "user.h"
#include "ticketbatch.h"

TicketBatch::TicketBatch() {
	this->price = 0;
	this->quantityAvailable = 0;
}

TicketBatch::TicketBatch(std::string eventTitle, double price, int quantityAvailable) {
	this->eventTitle = eventTitle;
	this->price = price;
	this->quantityAvailable = quantityAvailable;
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
User TicketBatch::getSeller() {
	// return this->seller;
}

/**
 * @return double price
 */ 
double TicketBatch::getPrice(){
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

