#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include "constants.h"
#include "user.h"
#include "session.h"

// void errorPrintf()

// using namespace std;

void errorPrintf(const char* fmt, ...)
{
    std::string newfmt = std::string(fmt);

    newfmt = ERROR_PREFIX + newfmt;
    // printf("\n\nthe format: %s \n\n",newfmt.c_str());

    va_list args;
    va_start(args,fmt);
    vprintf(newfmt.c_str(),args);
    va_end(args);
}

std::string trim(const std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}


std::map<std::string, class User> readUsersFile( )
{
    std::map<std::string, class User> availableUsers;
    std::string line;
    std::ifstream usersFile ("./CurrentUserAccounts.txt");

    // printf("ok ... %i" , usersFile.is_open() );

    // if ( usersFile.is_open() )
    // {
    // printf("trying to open: %s",USERS_ACCOUNT_FILE);
        while( std::getline( usersFile , line ))
        {
            std::istringstream lineStream(line);
            // printf("read line: %s\n",line);

            std::string name;
            std::string type;
            float balance;

            lineStream >> name >> type >> balance;

            User aUser(name,type,balance);
        
            availableUsers.insert(std::pair<std::string,class User>(name,aUser));
            // Session::AvailableUsers.insert(std::pair<std::string,class User>(name,aUser));
        }
        
    // }

    return availableUsers;
}