#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <map>
#include "user.h"

/** A Wrapper function for printf that just prepends the ERROR_PREFIX to the output
 * @param Format of the output
 * @param Varaidic arguments to print
 */
void errorPrintf(const char* fmt, ...);

/** A function to check if a given numeric input is in the given range
 * @param float input - user input
 * @param float min - minimum value
 * @param float max - maxium value
 */
bool inRange( float input , float min , float max );
bool inRange( int input , int min , int max );

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