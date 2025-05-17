//Qui vanno dichiarati i metodi e le costanti
#ifndef IMPIANTO_H
#define IMPIANTO_H
#include <string>
#include "../include/Time.h"

class Impianto {
private:
    static int contId;
    int ID;
    std::string nome;
    bool acceso; // true = acceso, false = spento
    Time accensione;
    Time ultimaAccensione;

public:
    Impianto();
    Impianto(std::string Nome, Time Accensione);
    int getID();
    std::string Accendi();
    virtual std::string Spegni() = 0;
    std::string Stampa();
};
#endif //IMPIANTO_H


//spegni è virtuale