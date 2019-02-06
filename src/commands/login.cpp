#include <string>

#include "../userinput.h"
#include "../command.h"
#include "login.h"



Login::Login(/* args */)
{
}

Login::~Login()
{
}


bool Login::Process()
{
    printf("Enter a username: ");

    std::string username = UserInput::GetStringInput();


    printf("\n\nYou entered: %s\n",username.c_str());
}