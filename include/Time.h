//Qui vanno dichiarati i metodi e le costanti
#ifndef TIME_H
#define TIME_H

#include <string>

class Time {
private:
    int hour;
    int minute;
public:
    Time();
    Time(int h, int min);
    void setTime(int hour, int minutes);
    std::string getTime() const;
    int DifferenzaMin(const Time &other) const;
    Time operator++(int);
    bool operator==(const Time &other) const;
};
#endif //TIME_H