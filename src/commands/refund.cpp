#include <string>
#include <map>

#include "../constants.h"
#include "../helperfunctions.h"
#include "../userinput.h"
#include "../command.h"
#include "../session.h"
#include "refund.h"
#include "../user.h"
#include "../transaction.h"
#include "../ticketbatch.h"

// Set static members of this class.
const std::string Refund::CommandName = "refund";
const char Refund::TransactionNumber = 5;

/// Constructor method for Refund, takes a session which is the current session in progress.
Refund::Refund( Session* inSession )
{
	userSession = inSession;
}

/** Processes the refund command.
 * 
 * this entails asking the user for a username to refund as, validating that, and then returning whether the refund was successful. 
 * @return Refund success.
 */
bool Refund::Process()
{
	// Check if the user is an Refund standard user, if they are, exit.
	if ( !getSession()->isAdmin() )
	{
		errorPrintf(REFUND_ERROR_ADMIN_ONLY);
		return false;
	}

	// Loop continuously until we get a valid input.    
	bool buyerSuccess = false;
	while ( !buyerSuccess )
	{
		printf( REFUND_PROMPT_BUYER );
		
		// get user cli input
		std::string buyerName = UserInput::GetStringInput(MIN_USERNAME_LENGTH,MAX_USERNAME_LENGTH);
		// validate the buyer name is valid to use
		if ( validateUserName( buyerName ) )
		{
			bool sellerSuccess = false;
			// Ask for the sellers name,
			while( !sellerSuccess){
				printf( REFUND_PROMPT_SELLER );
				std::string sellerName = UserInput::GetStringInput(MIN_USERNAME_LENGTH,MAX_USERNAME_LENGTH);

				if ( validateUserName(sellerName) )
				{
					bool amountSuccess = false;
					while( !amountSuccess ){
						printf(REFUND_PROMPT_AMOUNT);
						float amount = UserInput::GetFloatInput(MIN_CREDIT,MAX_CREDIT,REFUND_ERROR_AMOUNT_NEG);

						User* buyer = GetUserByName( buyerName );
						User* seller = GetUserByName( sellerName );

						if ( seller->getUserBalance() >= amount && inRange(amount,MIN_CREDIT,MAX_CREDIT) ) {
							amountSuccess = sellerSuccess = buyerSuccess = true; // valid, stop asking for info.
							printf(REFUND_PROMPT_SUCCESS);

							Transaction* refund = new Transaction();

							refund->Refund( buyer , seller , amount , TransactionNumber );
							getSession()->AddTransaction( refund );
						}
						else if (seller->getUserBalance() < amount)
						{
							errorPrintf(REFUND_ERROR_NOT_ENOUGH_BALANCE);
						}
					}
				}   
				else 
				{
					errorPrintf(REFUND_ERROR_SELLER_NAME);
				}
			}
		}
		else
		{
			errorPrintf(REFUND_ERROR_BUYER_NAME);
		}
	}

	return buyerSuccess;
}