#ifndef LOGIN_H
#define LOGIN_H

// #include <map>

// class Command;
#include "../command.h"

class Login : public Command
{
private:
    /* data */
    // bool va
    bool validateInput( std::string );
public:
    int val;
    Login(/* args */);
    ~Login();

    bool Process();
};


#endif