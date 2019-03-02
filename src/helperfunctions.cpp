#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdarg.h>

#include "constants.h"
#include "user.h"
#include "session.h"

/** \file
 * Helper Functions provides some useful, static functions that're helpful to have or don't have a better place to go.
 */

/** A Wrapper function for printf that just prepends the ERROR_PREFIX to the output
 * @param Format of the output
 * @param Varaidic arguments to print
 */
void errorPrintf(const char* fmt, ...)
{
    std::string newfmt = std::string(fmt);

    // printf("??? '%s'",newfmt.c_str());

    newfmt = ERROR_PREFIX + newfmt;

    // create a vararg list from the passed varargs
    va_list args;
    // do the print
    va_start(args,fmt);
    vprintf(newfmt.c_str(),args);
    va_end(args);
}

/** Trim leading and trailing spaces from a string.
 * @param String to trim.
 */
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

std::string readLink( std::string path )
{
    // create a character buffer of PATH_MAX (max length a path can be)
    char buff[PATH_MAX];

    // printf("passed path: %s \n",path.c_str());

    ssize_t length = ::readlink( path.c_str() , buff, sizeof(buff)-1 );

    // printf("passed path: %s len: %d \n",buff,length);
    
    if (length != -1)
    {
        // null terminate the string because readlink doesn't.
        buff[length] = '\0';
        
        return std::string(buff);
    }
}

std::string getFullPath( std::string path )
{
    // create a character buffer of PATH_MAX (max length a path can be)
    char buff[PATH_MAX];

    // printf("passed path: %s \n",path.c_str());

    char* valid = ::realpath( path.c_str() , buff );

    // printf("passed path: %s len: %d \n",buff,length);
    if (valid != NULL)
    {
        return std::string(buff);
    }
    // else
    // {
        // throw std::invalid_argument("invalid path was passed");
    // }
    
}


/** Read the available users file and parse it into a map where the keys are the string names and the values are the user objects.
 * @return map< string , User > of available users.
 */
std::map<std::string, class User> readUsersFile()
{
    std::map<std::string, class User> availableUsers;
    std::string line;
    std::ifstream usersFile (Session::UserAccountFile);

    if ( usersFile.is_open() )
    {
        while( std::getline( usersFile , line ))
        {
            // create a stringstream of each line
            std::istringstream lineStream(line);

            // three variables used to populate the user object
            std::string name;
            std::string type;
            float balance;

            // read from the line stream
            lineStream >> name >> type >> balance;

            // printf("read in type: %s \n",type.c_str());

            // create the user and insert them into the availableusers map
            User aUser(name,type,balance);
            availableUsers.insert(std::pair<std::string,class User>(name,aUser));
        }
    }

    return availableUsers;
}

