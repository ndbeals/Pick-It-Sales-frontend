#ifndef USER_H
#define USER_H


#include <string>
#include <vector>

// #include "ticketbatch.h"


class User
{
private:
    std::string userName;
    std::string userType;

    float userBalance;
public:
    User(/* args */);
    User(std::string, std::string,float);
    ~User();
};




#endif