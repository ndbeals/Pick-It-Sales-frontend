#ifndef LOGOUT_H
#define LOGOUT_H

#include "../command.h"
#include "../session.h"

class Logout  : public Command
{
private:
    /* data */
public:
    // Variable Block
    // int testes;
    static const std::string CommandName;

    // Method Block
    // Constructors
    Logout( Session* );
    Logout();
    ~Logout();
    
    std::string GetCommandName() { return CommandName; }

    bool Process();

    int gettest() {return testes;}
};

#endif