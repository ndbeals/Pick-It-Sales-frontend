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
    return false;
}

Command* Command::GetCommand( std::string commandName )
{
    Command *instance;

    if ( commandName == "login" )
    {
        instance = new Login();
    }

    (*instance).val = 5;

    printf("in class: %p\n" , (void *)instance);
    // printf("in class: %p\n" , (void *)*&instance);
    printf("val: %d\n",instance->val);
    return instance;
}