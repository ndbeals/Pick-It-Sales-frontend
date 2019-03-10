#include <string>
#include <mutex>

#include "helperfunctions.h"
#include "constants.h"
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
    // printf("%s%s", ERROR_PREFIX, "Not a valid command.\n");
    errorPrintf(ERROR_COMMAND);
    return false;
}

bool Command::validateUserName( std::string input )
{
    if ( Session::AvailableUsers.find(input) == Session::AvailableUsers.end() )
    {
        // not found
        return false;
    }
    return true;
}

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