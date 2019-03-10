#include <string>
#include <map>

#include "../constants.h"
#include "../helperfunctions.h"
#include "../userinput.h"
#include "../command.h"
#include "../session.h"
#include "delete.h"
#include "../user.h"
#include "../transaction.h"
#include "../ticketbatch.h"

// Set static members of this class.
const std::string Delete::CommandName = "delete";
const char Delete::TransactionNumber = 2;

/// Constructor method for Delete, takes a session which is the current session in progress.
Delete::Delete( Session* inSession )
{
	userSession = inSession;
}

/** Processes the delete command.
 * 
 * this entails asking the user for a username to delete as, validating that, and then returning whether the delete was successful. 
 * @return Delete success.
 */
bool Delete::Process()
{
	// Check if the user is an Delete standard user, if they are, exit.
	if ( !getSession()->isAdmin() )
	{
		errorPrintf(DELETE_ERROR_ADMIN_ONLY);
		return false;
	}

	bool nameSuccess = false;
	// Ask for the deleters name,
	while( !nameSuccess){
		printf( DELETE_PROMPT_NAME );
		std::string deleteName = UserInput::GetStringInput(MIN_USERNAME_LENGTH,MAX_USERNAME_LENGTH);

		if ( validateUserName(deleteName) && deleteName != getSession()->getCurrentUser()->getUserName() )
		{
			nameSuccess = true;
			printf( DELETE_PROMPT_SUCCESS );

			Transaction* del = new Transaction();

			del->Delete( GetUserByName( deleteName ) , TransactionNumber );
			getSession()->AddTransaction( del );
		}
		else if ( getSession()->getCurrentUser()->getUserName() == deleteName ) {
			errorPrintf(DELETE_ERROR_CANT_DELETE_SELF);
		}
		else 
		{
			errorPrintf(DELETE_ERROR_USER_NOT_EXISTS);
		}
	}

	return nameSuccess;
}