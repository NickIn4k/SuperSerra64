#include "../include/Impianto.h"

Impianto::Impianto(const std::string &n) : nome{n}, acceso{false} {
    ID = contId++;
    ultimaAccensione = Time(-1,-1); //Prima accensione => condizione di default
};

//Restituisce l'ID dell'impianto
int Impianto::getID() const {
    return this->ID;
}

//Restituisce una stringa con le info principali dell’impianto
std::string Impianto::Stampa() const{
    std::string stato = acceso ? "ACCESO" : "SPENTO";

    return "Impianto: " + nome + "\n"
         + "ID: " + std::to_string(ID) + "\n"
         + "Stato: " + stato + "\n"
         + "Ultima accensione: " + ultimaAccensione.getTime();
}

//Var static
int Impianto::contId = 0;