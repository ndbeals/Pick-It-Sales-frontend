#include <string>
#include <map>

#include "helperfunctions.h"
#include "constants.h"
#include "ticketbatch.h"
#include "command.h"
#include "commands/login.h"
#include "commands/logout.h"
#include "commands/create.h"
#include "commands/sell.h"
#include "commands/buy.h"
#include "commands/delete.h"
#include "commands/refund.h"
#include "commands/addcredit.h"
#include "session.h"

/// Stub constructor (must exist though)
Command::Command(  )
{}

/** Constructor method for Command, takes a session which is the current session in progress.
 * @param Session* inSession - in progress session.
 */
Command::Command( Session* inSession )
{
	userSession = inSession;
}

/// Stub deconstructor (must exist though)
Command::~Command()
{}

/** Processes the command
 * 
 * this is the function declaration that'll be overwritten by each child to implement their specific functionality.
 * @return bool - whether or not the Login was successful.
 */
bool Command::Process()
{
	errorPrintf(ERROR_COMMAND);
	return false;
}

/** Validates that the user input is a valid username. 
 * @param user input.
 * @return Valid user name or not.
 */
bool Command::validateUserName( std::string input )
{
	if ( Session::AvailableUsers.find(input) == Session::AvailableUsers.end() )
	{
		// not found
		return false;
	}
	return true;
}

/** Checks if the given ticket count is a valid amount
 * defined by MIN_TICKETS and MAX_SELL_TICKERS inclusive
 * @param int input - the ticket count
 * @return bool - count valid or not
 */
bool Command::checkTicketAmount( int input )
{
    if ( getSession()->isAdmin() ){
        return inRange( input , MIN_TICKETS_FOR_SALE , MAX_TICKETS_FOR_SALE );
    }
    else
    {
        return inRange( input , MIN_TICKETS_FOR_SALE , MAX_TICKETS_TO_BUY );
    }
}

/** Checks if the given sale price is valid or not
 * @param float price - sale price
 * @return bool - Valid price?.
 */
bool Command::checkSalePrice( float price )
{
    return inRange( price, MIN_TICKET_PRICE, MAX_TICKET_PRICE );
}

/** Checks if the given name is a name that's already being used.
 * @param user input.
 * @return Valid user name or not.
 */
bool Command::checkEventTitle( std::string input )
{
    for(std::map<std::string,class TicketBatch>::iterator iter = Session::AvailableTickets.begin(); iter != Session::AvailableTickets.end(); ++iter)
    {
        std::string key = iter->first;
        std::string val = iter->second.getEventTitle();
        if ( val == input || key == input ) {
            return true;
        }
    }
	
    return false;
}

/** Checks if the given name is of valid length defined by 
 * MIN_EVENTTITLE_LENGTH and MAX_EVENTTITLE_LENGTH inclusive
 * @param string input - user input
 * @return bool - Valid length or not.
 */
bool Command::checkEventTitleLength( std::string input )
{
    return (input.length() >= MIN_EVENTTITLE_LENGTH && input.length() <= MAX_EVENTTITLE_LENGTH);
}

/** Returns a user object
 * @return User Object
 */
User* Command::GetUserByName( std::string input )
{
	if ( validateUserName( input ) ) {
		return &Session::AvailableUsers[input];
	}
	return NULL;
}

/** Factory function to create commands.
 * @param string commandName - name of command
 * @param Session* session - current session
 * @return New Command.
 */
Command* Command::GetCommandNameFromInput( std::string commandName , Session* session )
{
	Command *instance;

	if ( commandName == "login" )
	{
		instance = new Login( session );
	}
	else if ( commandName == "logout" )
	{
		instance = new Logout( session );
	}
	else if ( commandName == "create" )
	{
		instance = new Create( session );
	}
	else if ( commandName == "sell" )
	{
		instance = new Sell( session );
	}
	else if ( commandName == "buy" )
	{
		instance = new Buy( session );
	}
	else if ( commandName == "delete" )
	{
		instance = new Delete( session );
	}
	else if ( commandName == "refund" )
	{
		instance = new Refund( session );
	}
	else if ( commandName == "addcredit" )
	{
		instance = new AddCredit( session );
	}
	else
	{
		instance = new Command( session );
	}

	return instance;
}