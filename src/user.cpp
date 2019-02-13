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


// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <string>
// #include <vector>
// #include <algorithm>
// #include <cstdio>

// #include "constants.h"
// #include "helperfunctions.h"
// #include "ticketbatch.h"
// #include "transaction.h"
// #include "userinput.h"

// User::User()
// {
    
// }

// User::~User()
// {

// }
