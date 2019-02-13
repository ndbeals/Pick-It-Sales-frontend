#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <map>
#include "user.h"

// #include <string>

void errorPrintf(const char* fmt, ...);

std::string trim(const std::string& str);

std::map<std::string,class User> readUsersFile();
#endif