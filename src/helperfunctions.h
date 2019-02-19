#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <map>
#include "user.h"

/** A Wrapper function for printf that just prepends the ERROR_PREFIX to the output
 * @param Format of the output
 * @param Varaidic arguments to print
 */
void errorPrintf(const char* fmt, ...);

/** Trim leading and trailing spaces from a string.
 * @param String to trim.
 */
std::string trim(const std::string& str);

std::string readLink( std::string );
std::string getFullPath( std::string );

/** Read the available users file and parse it into a map where the keys are the string names and the values are the user objects.
 * @return map< string , User > of available users.
 */
std::map<std::string,class User> readUsersFile();

#endif