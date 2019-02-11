#ifndef LOGIN_H
#define LOGIN_H

// #include <map>

// class Command;
#include "../command.h"
#include "../session.h"

class Login : public Command
{
private:
    /* data */
    // bool va
    bool validateInput( std::string );

public:
    static const std::string CommandName;
    static const char TransactionNumber;

    int val; 
    Login( Session* );
    Login();
    ~Login();

    bool Process();

    std::string GetCommandName() { return CommandName; }

    int gettest() {return testes;}
};


#endif