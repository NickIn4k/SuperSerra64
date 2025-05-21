//Qui vanno dichiarati i metodi e le costanti
#ifndef TIME_H
#define TIME_H

#include <string>

class Time {
public:
    int Hour;
    int Minute;

    Time();
    Time(int h, int min);
    Time(const std::string &token);
    std::string getTime() const;
    int DifferenzaMin(const Time &other) const;
    Time operator++(int);
    bool operator==(const Time &other) const;
};
#endif //TIME_H