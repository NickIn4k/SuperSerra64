#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <string>
#include <vector>
#include <fstream>
#include "../include/Time.h"
#include "../include/Serra.h"

class UserInterface{
private:
    static std::ofstream logFile;
    static std::string logFilePath;
    static void openFile();
public:
    static void logMessage(const Time &time, const std::string &message, const int &errorLevel);
    static std::vector<std::string> commandParser(const std::string &command);
    static void processCommand(const std::string &command, const Time &now, Serra &serra);
    static void closeFile();
};
#endif //USERINTERFACE_H
