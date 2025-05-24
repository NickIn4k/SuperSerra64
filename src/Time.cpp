#include "../include/Time.h"
#include <stdexcept>

#define MAX_H 24
#define MIN 0
#define MAX_M 60

//getTime per l'output su comando
std::string Time::getTime() const {
    return std::to_string(this->Hour) + ":" + std::to_string(this->Minute);;
}

//Operator di incremento postfisso => obj++
Time Time::operator++(int) {
    Time temp = *this;
    this->Minute++;

    if(this->Minute >= 60) {        //Caso hh:59
        this->Hour++;
        this->Minute = 0;
        if(this->Hour >= 24)        //Caso 00:00
            this->Hour = 0;
    }

    return temp;
}

//Operator di uguaglianza
bool Time::operator==(const Time &other) const {
    return this->Hour == other.Hour && this->Minute == other.Minute;
}

int Time::DifferenzaMin(const Time &other) const {
    Time tmp = *this;
    int differenza = 0;
    while (!(tmp == other)) {
        tmp++;
        differenza++;
    }
    return differenza;
}

Time::Time() = default;

Time::Time(int h, int min) : Hour{h}, Minute{min}{};

// Costruttore da stringa formato HH:MM o H:M
Time::Time(const std::string &token) {
    auto pos = token.find(':');

    if (pos == std::string::npos)
        throw std::invalid_argument("Formato orario non valido: usare HH:MM");

    std::string hours = token.substr(0, pos);
    std::string minutes = token.substr(pos + 1);
    int h, m;
    h = std::stoi(hours);
    m = std::stoi(minutes);

    if (h < MIN || h > MAX_H || m < MIN || m > MAX_M)
        throw std::invalid_argument("Valori orari fuori range: 0 <= HH <24, 0 <= MM < 60");

    this->Hour = h;
    this->Minute = m;
}
