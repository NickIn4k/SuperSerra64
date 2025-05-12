//Qui vanno dichiarati i metodi e le costanti
#ifndef IMPIANTO_H
#define IMPIANTO_H
#include <string>
#include <time.h>
class Impianto {
private:
    int ID;
    std::string TipoPianta;
    std::string Nome;
    bool Accesso; // true = acceso, false = spento
    Time Accensione;
    Time ultimaAccensione;


public:
    Impianto();
    int getID();
    std::string Accendi();
   virtual std::string Spegni();
    std::string Stampa();
};
#endif //IMPIANTO_H


//spegni è virtuale