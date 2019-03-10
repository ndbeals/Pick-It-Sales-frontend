#include <string>
#include <map>
#include <iostream>

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

	newfmt = ERROR_PREFIX + newfmt;

	// create a vararg list from the passed varargs
	va_list args;
	// do the print
	va_start(args,fmt);
	vprintf(newfmt.c_str(),args);
	va_end(args);
}

/** A function to check if a given numeric input is in the given range
 * @param float input - user input
 * @param float min - minimum value
 * @param float max - maxium value
 * @return bool - whether or not the input is in the given range
 */
bool inRange( float input , float min , float max )
{
	return ( input >= min && input <= max );
}
/** A function to check if a given numeric input is in the given range
 * @param int input - user input
 * @param int min - minimum value
 * @param int max - maxium value
 * @return bool - whether or not the input is in the given range
 */
bool inRange( int input , int min , int max )
{
	return ( input >= min && input <= max );
}

/** Trim leading and trailing spaces from a string.
 * @param String to trim.
 * @return string - trimmed string value
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

/** Convert a symbolic link to the real file system path
 * @param path the symlink path
 * @return string the real path
 */
std::string readLink( std::string path )
{
	// create a character buffer of PATH_MAX (max length a path can be)
	char buff[PATH_MAX];

	ssize_t length = ::readlink( path.c_str() , buff, sizeof(buff)-1 );

	if (length != -1)
	{
		// null terminate the string because readlink doesn't.
		buff[length] = '\0';
		
		return std::string(buff);
	}
	
	return "";
}

/** Convert a relative path to the full file system path
 * @param path the relative path
 * @return string the real path
 */
std::string getFullPath( std::string path )
{
	// create a character buffer of PATH_MAX (max length a path can be)
	char buff[PATH_MAX];

	char* valid = ::realpath( path.c_str() , buff );

	if (valid != NULL)
	{
		return std::string(buff);
	}

	return "";    
}
