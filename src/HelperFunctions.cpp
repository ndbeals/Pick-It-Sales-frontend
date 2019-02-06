#include <stdio.h>
#include <stdarg.h>
#include <string>
// void errorPrintf()

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