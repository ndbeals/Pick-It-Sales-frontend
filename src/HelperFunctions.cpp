#include <stdio.h>
#include <stdarg.h>
#include <string>
#include "constants.h"

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