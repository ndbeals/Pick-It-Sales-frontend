#include <string>
#include <map>

#include "../constants.h"
#include "../helperfunctions.h"
#include "../userinput.h"
#include "../command.h"
#include "../session.h"
#include "addcredit.h"
#include "../user.h"
#include "../transaction.h"
#include "../ticketbatch.h"

// Set static members of this class.
const std::string AddCredit::CommandName = "addcredit";
const char AddCredit::TransactionNumber = 6;

/// Constructor method for AddCredit, takes a session which is the current session in progress.
AddCredit::AddCredit( Session* inSession )
{
	userSession = inSession;
}

/** Processes the addCredit command.
 * 
 * this entails asking the user for a username to addCredit as, validating that, and then returning whether the addCredit was successful. 
 * @return AddCredit success.
 */
bool AddCredit::Process()
{
	// Loop continuously until we get a valid input.    
	User* creditUser = getSession()->getCurrentUser();
	bool userSuccess = !getSession()->isAdmin(); //set this var to false if we admin, forcing us to ask for a username
	
	while( !userSuccess ){
		printf(ADDCREDIT_PROMPT_USERNAME);
		std::string userName = UserInput::GetStringInput(MIN_USERNAME_LENGTH,MAX_USERNAME_LENGTH);

		if ( validateUserName(userName) ) {
			userSuccess = true;
			creditUser = GetUserByName( userName );
		}
		else
		{
			errorPrintf(ADDCREDIT_ERROR_USERNAME);
		}
		
	}

	bool amountSuccess = false;
	while( !amountSuccess )
	{
		printf(ADDCREDIT_PROMPT_AMOUNT);
		float amount = UserInput::GetFloatInput(MIN_CREDIT+0.005f,MAX_ADD_CREDIT,ADDCREDIT_ERROR_AMOUNT_NEG,ADDCREDIT_ERROR_AMOUNT_MAX);

		if ( inRange(amount, MIN_CREDIT+0.005f, MAX_ADD_CREDIT) )
		{
			amountSuccess = true;

			if ( (creditUser->getUserBalance() + amount) <= MAX_CREDIT ) {
				amountSuccess = userSuccess = true;

				printf(ADDCREDIT_PROMPT_SUCCESS);

				Transaction* addCredit = new Transaction();
				
				addCredit->AddCredit( creditUser , amount , TransactionNumber);
				getSession()->AddTransaction(addCredit);
			}
			else
			{
				errorPrintf(ADDCREDIT_ERROR_USER_AT_MAX);
			}
		}
	}

	return amountSuccess;
}