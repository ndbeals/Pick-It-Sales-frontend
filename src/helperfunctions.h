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
 * @return bool - whether or not the input is in the given range
 */
bool inRange( float input , float min , float max );
/** A function to check if a given numeric input is in the given range
 * @param int input - user input
 * @param int min - minimum value
 * @param int max - maxium value
 * @return bool - whether or not the input is in the given range
 */
bool inRange( int input , int min , int max );

/** Trim leading and trailing spaces from a string.
 * @param String to trim.
 */
std::string trim(const std::string& str);

/** Convert a symbolic link to the real file system path
 * @param path the symlink path
 * @return string the real path
 */
std::string readLink( std::string );

/** Convert a relative path to the full file system path
 * @param path the relative path
 * @return string the real path
 */
std::string getFullPath( std::string );

#endif