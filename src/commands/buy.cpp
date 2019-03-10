#include <string>
#include <map>

#include "../constants.h"
#include "../helperfunctions.h"
#include "../userinput.h"
#include "../command.h"
#include "../session.h"
#include "buy.h"
#include "../user.h"
#include "../transaction.h"
#include "../ticketbatch.h"

// Set static members of this class.
const std::string Buy::CommandName = "buy";
const char Buy::TransactionNumber = 4;

/// Constructor method for Buy, takes a session which is the current session in progress.
Buy::Buy( Session* inSession )
{
	userSession = inSession;
}


/** Processes the buy command.
 * 
 * this entails asking the user for a username to buy as, validating that, and then returning whether the buy was successful. 
 * @return Buy success.
 */
bool Buy::Process()
{
	// Check if the user is an Buy standard user, if they are, exit.
	if ( getSession()->getCurrentUser()->getUserType() == "SS" )
	{
		errorPrintf(BUY_ERROR_WRONG_ACCOUNT);
		return false;
	}

	// Loop continuously until we get a valid input.    
	bool titleSuccess = false;
	while ( !titleSuccess )
	{
		printf( BUY_PROMPT_EVENT_TILE );
		
		// get user cli input
		std::string eventTitle = UserInput::GetStringInput( MIN_EVENTTITLE_LENGTH , MAX_EVENTTITLE_LENGTH , BUY_ERROR_EVENT_TOO_LONG , BUY_ERROR_EVENT_TOO_SHORT);
		// validate the title name is valid to use
		if ( !checkEventTitle( eventTitle ) )
		{
			bool amountSuccess = false;
			while( !amountSuccess ){
				printf( BUY_PROMPT_NUMBER_TICKETS );

				int ticketAmount = 0;
				int max = MAX_TICKETS_TO_BUY;

				if ( getSession()->isAdmin() ){
					max = 100;
					ticketAmount = UserInput::GetIntegerInput(MIN_TICKETS_FOR_SALE, max, BUY_ERROR_MIN_TICKETS , BUY_ERROR_MAX_TICKETS );
				}
				else
				{
					ticketAmount = UserInput::GetIntegerInput(MIN_TICKETS_FOR_SALE, max, BUY_ERROR_MIN_TICKETS , "You may only purchase 4 tickets max.\n" );
				}

				// check if input credit is valid, if so, proceed
				if ( checkTicketAmount( ticketAmount ) ) {

					bool sellerSuccess = false;
					// Ask for the sellers name,
					while( !sellerSuccess){
						printf( BUY_PROMPT_SELLER_NAME );
						std::string sellerName = UserInput::GetStringInput(MIN_USERNAME_LENGTH,MAX_USERNAME_LENGTH);

						if ( validateUserName(sellerName) && sellerName != getSession()->getCurrentUser()->getUserName() )
						{
							if ( checkEventTitle( eventTitle + sellerName ) )
							{
								TicketBatch batch = Session::AvailableTickets[ eventTitle + sellerName ];
								
								if (batch.getQuantityAvailable()>=ticketAmount) {
								
									printf("Cost per Ticket: $%0.2f | Total Cost: $%0.2f\n" , batch.getPrice() , batch.getPrice() * ticketAmount );
									
									bool confirmSuccess = false;
									while( !confirmSuccess ){
										printf(BUY_PROMPT_CONFIRM);
										std::string input = UserInput::GetStringInput(0,10);

										if ( input.compare("y") || input.compare("yes") || input.compare("YES") || input.compare("Yes") ) {
											confirmSuccess = amountSuccess = sellerSuccess = titleSuccess = true; // valid, stop asking for info.
											if (getSession()->getCurrentUser()->getUserBalance() >= (batch.getPrice() * static_cast<float>(ticketAmount)) ) {

												printf(BUY_PROMPT_SUCCESS);

												Transaction* buy = new Transaction();

												buy->BuyTicket( batch , ticketAmount , TransactionNumber );
												getSession()->AddTransaction( buy );
											}
											else
											{
											   errorPrintf("You do not have enough credit to purchase these.\n");
											}
										}
										else if (input.compare("n") || input.compare("no") || input.compare("NO") || input.compare("no") )
										{
											printf("Cancelled transaction.\n");
										}
									}
								}
							}
						}
						else if ( getSession()->getCurrentUser()->getUserName() == sellerName ) {
							errorPrintf("You cannot purchase your own tickets.\n");
							return false;
						}
						
						else 
						{
							errorPrintf("must enter a valid seller's name.\n");
						}
					}
				}
			}
		}
		else
		{
			errorPrintf(BUY_ERROR_WRONG_EVENT);
		}
	}

	return titleSuccess;
}