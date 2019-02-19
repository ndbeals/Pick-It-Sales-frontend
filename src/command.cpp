#include <string>
#include <mutex>

#include "helperfunctions.h"
#include "constants.h"
#include "command.h"
#include "commands/login.h"
#include "commands/logout.h"
#include "session.h"

/// Stub constructor (must exist though)
Command::Command(  )
{}

/// Constructor method for Command, takes a session which is the current session in progress.
/// @param Current, in progress session.
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
 * @return Login success.
 */
bool Command::Process()
{
    // printf("%s%s", ERROR_PREFIX, "Not a valid command.\n");
    errorPrintf(ERROR_COMMAND);
    return false;
}

/** Factory function to create commands.
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
    else
    {
        instance = new Command( session );
    }

    return instance;
}