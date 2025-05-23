//Qui vanno dichiarati i metodi e le costanti
#ifndef IMPIANTO_H
#define IMPIANTO_H
#include <string>
#include "../include/Time.h"

class Impianto {
protected:
    static int contId;
    int ID;
    std::string nome;
    bool acceso; //True = acceso, false = spento
    Time ultimaAccensione;
public:
    Impianto() = default;
    explicit Impianto(const std::string &Nome);
    int getID() const;
    std::string getNome() const;
    virtual std::string Accendi(Time accensione) = 0;
    virtual std::string Spegni() = 0;
    virtual void OnTimeChanged(Time now) = 0;
    virtual void ResetTimers() = 0;
    std::string Stampa() const;
    virtual ~Impianto() = default;
};
#endif //IMPIANTO_H