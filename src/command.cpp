#include <string>

#include "constants.h"
#include "command.h"
#include "commands/login.h"
#include "commands/logout.h"
#include "session.h"

Command::Command(  )
{
    // userSession = &inSession;
    // this->CommandName =
    // printf("parent constructor\n");
    testes=-1;
}

Command::Command( Session* inSession )
{
    userSession = inSession;

    // printf("parent constructor\n");
    testes=-1;
}

Command::~Command()
{
}

bool Command::Process()
{
    printf("%s%s", ERROR_PREFIX, "Not a valid command.\n");
    return false;
}

// int Command::gettest()
// {
//     return 0;
// }

Command* Command::GetCommandNameFromInput( std::string commandName , Session* session )
{
    Command *instance;

    // printf("com num: %d\n",session->num);
    // session->num = 2;
    // printf("com num: %d\n",session->num);


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


    // printf("val: %d\n",instance->val);
    // (*instance).val = 5;

    // printf("in class: %p\n" , (void *)instance);
    // printf("in class: %p\n" , (void *)*&instance);
    return instance;
}