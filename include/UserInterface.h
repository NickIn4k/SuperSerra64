#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "../include/Time.h"

class UserInterface{
public:
    static void logMessage(const Time &time, const std::string &message, const int &errorLevel);
    static std::vector<std::string> commandParser(const std::string &command);
    static void processCommand(const std::string &command);
};
#endif //USERINTERFACE_H
