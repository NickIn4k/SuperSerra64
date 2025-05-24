//Qui vanno dichiarati i metodi e le costanti
#ifndef TIME_H
#define TIME_H

#include <string>
//  Classe per rappresentare un orario (ora e minuti)
class Time {
public:
    int Hour;
    int Minute;

    Time();
    Time(int h, int min);
    Time(const std::string &token);
    std::string getTime() const; // Restituisce l'orario come stringa
    int DifferenzaMin(const Time &other) const; // Calcola la differenza in minuti tra due orari
    Time operator++(int);  // Aumenta minuto per minuto
    bool operator==(const Time &other) const;  
};
#endif //TIME_H