#ifndef LOGIN_H
#define LOGIN_H

// class Command;
#include "../command.h"

class Login : public Command
{
private:
    /* data */
public:
    int val;
    Login(/* args */);
    ~Login();

    bool Process();
};


#endif