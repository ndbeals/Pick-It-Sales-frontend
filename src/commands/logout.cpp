#include <string>

#include "../userinput.h"
#include "../command.h"
#include "logout.h"
#include "../session.h"

const std::string Logout::CommandName = "logout";
const char Logout::TransactionNumber = 0; // 00;

Logout::Logout( Session* inSession)
{
    userSession = inSession;
    printf("logout constructor\n");
}
Logout::Logout()
{
    printf("logout constructor\n");
}

Logout::~Logout()
{
}

bool Logout::Process()
{
    bool success = getSession()->LogOut();
    printf("Logged out!\n");

    return success;   
}
