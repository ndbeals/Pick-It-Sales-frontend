#include <string>

#include "command.h"
#include "commands/login.h"

Command::Command(/* args */)
{
}

Command::~Command()
{
}

bool Command::Process()
{
    printf("command process parent\n");
    return false;
}

Command* Command::GetCommand( std::string commandName )
{
    Command *instance;

    if ( commandName == "login" )
    {
        instance = new Login();
    }
    // else if ( commandName == "" )
    // {

    // }
    else
    {
        instance = new Command();
    }


    // printf("val: %d\n",instance->val);
    // (*instance).val = 5;

    // printf("in class: %p\n" , (void *)instance);
    // printf("in class: %p\n" , (void *)*&instance);
    return instance;
}