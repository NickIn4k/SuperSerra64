//Qui vanno dichiarati i metodi e le costanti
#ifndef TIME_H
#define TIME_H

#include <string>

class Time {
private:
    int hour;
    int minute;
public:
    void setTime(int hour, int minutes);
    std::string getTime() const;
    //Operator ++ come fare
};
#endif //TIME_H