#include <string>
#include <map>

#include "../constants.h"
#include "../helperfunctions.h"
#include "../userinput.h"
#include "../command.h"
#include "../session.h"
#include "sell.h"
#include "../user.h"
#include "../transaction.h"
#include "../ticketbatch.h"

// Set static members of this class.
const std::string Sell::CommandName = "sell";
const char Sell::TransactionNumber = 3;

/** Constructor method for Sell, takes a session which is the current session in progress.
 * @param Session* inSession - in progress session.
 */ 
Sell::Sell( Session* inSession )
{
	userSession = inSession;
}


/** Checks if the given ticket amount is a valid amount
 * defined by MIN_TICKETS_FOR_SALE and MAX_TICKETS_FOR_SALE inclusive
 * @param int input - user input
 * @return bool - Valid quantity of tickets for sale
 */
bool Sell::checkTicketAmount( int input )
{
	return inRange( input , MIN_TICKETS_FOR_SALE , MAX_TICKETS_FOR_SALE );
}

/** Processes the sell command.
 * 
 * this entails asking the user for a username to sell as, validating that, and then returning whether the sell was successful. 
 * @return Sell success.
 */
bool Sell::Process()
{
	// Check if the user is an Buy standard user, if they are, exit.
	if ( getSession()->getCurrentUser()->getUserType() == "BS" )
	{
		errorPrintf(SELL_ERROR_WRONG_ACCOUNT);
		return false;
	}
	std::string userName = getSession()->getCurrentUser()->getUserName();

	// Loop continuously until we get a valid input.    
	bool titleSuccess = false;
	while ( !titleSuccess )
	{
		printf( SELL_PROMPT_EVENT_TILE );
		
		// get user cli input
		std::string eventTitle = UserInput::GetStringInput( MIN_EVENTTITLE_LENGTH , MAX_EVENTTITLE_LENGTH , SELL_ERROR_EVENT_TOO_LONG , SELL_ERROR_EVENT_TOO_SHORT);
		// validate the username is valid to use
		if ( checkEventTitleLength( eventTitle ) && (Session::AvailableTickets.find(eventTitle + userName) == Session::AvailableTickets.end()) )
		{
			bool priceSuccess = false;
			while( !priceSuccess){
				printf( SELL_PROMPT_SALE_PRICE );
				float salePrice = UserInput::GetFloatInput(MIN_TICKET_PRICE,MAX_TICKET_PRICE,SELL_ERROR_PRICE_TOO_LOW,SELL_ERROR_PRICE_TOO_HIGH);

				if ( checkSalePrice( salePrice ) )
				{
					bool amountSuccess = false;
					while( !amountSuccess ){
						printf( SELL_PROMPT_NUMBER_TICKETS );
						int ticketAmount = UserInput::GetIntegerInput(MIN_TICKETS_FOR_SALE, MAX_TICKETS_FOR_SALE , SELL_ERROR_MIN_TICKETS , SELL_ERROR_MAX_TICKETS );

						// check if input credit is valid, if so, proceed
						if ( checkTicketAmount( ticketAmount ) ) {
							amountSuccess = priceSuccess = titleSuccess = true; // credit is valid, stop asking for info.
							printf(SELL_PROMPT_SUCCESS);

							TicketBatch newBatch( eventTitle, salePrice , ticketAmount , getSession()->getCurrentUser() );
							Transaction* sell = new Transaction();

							sell->Sell( newBatch , TransactionNumber );
							getSession()->AddTransaction( sell );
						}
					}
				}
			}
		}
		else if ( !(Session::AvailableTickets.find(eventTitle + userName) == Session::AvailableTickets.end()) )
		{
			errorPrintf("You are already selling tickets at this event\n");
		}
		
	}

	return titleSuccess;
}