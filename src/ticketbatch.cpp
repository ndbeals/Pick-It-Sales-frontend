#include <iostream>
#include <string>
#include <fstream>
#include <string>

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
 * Locate tickets matching the given criteria 
 */ 
TicketBatch TicketBatch::find(const std::string eventTitle, const int numberOfTickets, const std::string sellerName) {
	TicketBatch ticket;

	// find TicketBatch obj
	// if found, set TicketBatch obj

	
	// return TicketBatch obj
	return ticket;
}

std::string TicketBatch::getEventTitle() {
	return this->eventTitle;
}

User TicketBatch::getSeller() {
	// return this->seller;
}

double TicketBatch::getPrice(){
	// return this->price;
}

int TicketBatch::getQuantityAvailable(){
	this->quantityAvailable;
}

/**
 * Sets quantity of tickets available for purchase
 */ 
void TicketBatch::setQuantityAvailable(const int quantityAvailable) {
	this->quantityAvailable = quantityAvailable;
}

