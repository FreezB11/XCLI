/*
    this aint ur normal utils
    just to reduce a lot of typings
*/
#ifndef _UTILS_H
#define _UTILS_H

#include <ctime>
#include <chrono>
#include <iostream>
#include <iomanip>
// int = 4 bytes = 32 bits
// char = 1 byte = 8 bits
typedef char            int8;
typedef short           int16;
typedef int             int32;
typedef long long       int64;

auto now = std::chrono::system_clock::now();
std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

// Convert to a readable format
std::tm* localTime = std::localtime(&currentTime);
    
// LOGGING
 #define log(x) std::cout << x << std::endl;
 #define tlog(x) std::cout << "[" << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << "] "<< message << std::endl;


#endif