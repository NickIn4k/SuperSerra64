#include "../include/Time.h"

//Ciclo => aumenta l'ora di minuto in minuto la logica di accensione/spegnimento sarà in impianto
void Time::setTime(int hour, int minutes) {
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