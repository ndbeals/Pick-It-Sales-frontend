#include <string>

#include "../userinput.h"
#include "../command.h"
#include "logout.h"
#include "../session.h"

const std::string Logout::CommandName = "logout";


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
    // if ( userSession->isLoggedIn() )
    // {
    getSession()->LogOut();

    printf("Logged out!\n");
    // }
    
    printf("logout process\n");
    testes=1;
}
