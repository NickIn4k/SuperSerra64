#include "../include/Time.h"
#include <stdexcept>

#define MAX_H 24
#define MIN 0
#define MAX_M 60

//Ciclo => aumenta l'ora di minuto in minuto la logica di accensione/spegnimento sarà in impianto
void Time::setTime(int hour, int minutes) {
    if(hour > MAX_H || hour < MIN || minutes > MAX_M || minutes < MIN)
        throw std::invalid_argument("Invalid time");        //Solleva un'eccezione
    while(this->hour != hour || this->minute != minutes)
        (*this)++;
}

//getTime per l'output su comando
std::string Time::getTime() const {
    return std::to_string(this->hour) + ":" + std::to_string(this->minute);;
}

//Operator di incremento postfisso => obj++
Time Time::operator++(int) {
    Time temp = *this;
    this->minute++;

    if(this->minute >= 60) {        //Caso hh:59
        this->hour++;
        this->minute = 0;
        if(this->hour >= 24)        //Caso 00:00
            this->hour = 0;
    }

    return temp;
}

//Operator di uguaglianza
bool Time::operator==(const Time &other) const {
    return this->hour == other.hour && this->minute == other.minute;
}

Time::Time() = default;

Time::Time(int h, int min) : hour{h}, minute{min}{};