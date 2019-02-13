#include <string>
#include "user.h"

User::User(/* args */)
{
}
User::User(std::string userName , std::string userType , float balance)
{
    this->userName = userName;
    this->userType = userType;

    this->userBalance = balance;
    printf("user constructed %s %s %f\n" ,this->userName.c_str(), this->userType.c_str() , this->userBalance);
}

User::~User()
{
}

