#include "Impianto.h"

Impianto::Impianto(const std::string &n) : nome{n}, acceso{false} {
    ID = contId++;
    ultimaAccensione = Time(-1,-1); //Prima accensione => condizione di default
};

//Restituisce l'ID dell'impianto
int Impianto::getID() const {
    return this->ID;
}

//Restituisce il nome dell'impianto
std::string Impianto::getNome() const {
    return this->nome;
}

//Var static
int Impianto::contId = 0;