#include <string>

#include "../userinput.h"
#include "../command.h"
#include "logout.h"
#include "../session.h"

// Set static members of this class.
const std::string Logout::CommandName = "logout";
const char Logout::TransactionNumber = 0; // 00;

/** Constructor method for Logout, takes a session which is the current session in progress.
 * @param Session* inSession - in progress session.
 */ 
Logout::Logout( Session* inSession)
{
    userSession = inSession;
}

/// Stub constructor (must exist though)
Logout::Logout()
{}

/// Stub deconstructor (must exist though)
Logout::~Logout()
{
}

/** Processes the logout command.
 * 
 * Changes the session state to ended and terminates session.
 * @return Logout success.
 */
bool Logout::Process()
{
    bool success = getSession()->LogOut();
    printf("Logged out!\n");

    return success;   
}
