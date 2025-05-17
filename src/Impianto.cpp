#include "../include/Impianto.h"

Impianto::Impianto() = default;

Impianto::Impianto(std::string n, Time a) : nome{n}, accensione{a} {
    acceso = false;
    ID = contId++;
    ultimaAccensione = Time(-1,-1); //Prima accensione => cond di default
};

//Accende l’impianto, imposta Accesso a true e salva l’orario di accensione
std::string Impianto::Accendi() {
    acceso = true;
    ultimaAccensione = accensione;
    return "[Accensione] L’impianto '" + nome + "' è stato acceso";
}
//Spegne l’impianto, imposta Accesso a false
std::string Impianto::Spegni() {
    acceso = false;
    return "[Spegnimento] L’impianto '" + nome + "' è stato spento";
}
//Restituisce l'ID dell'impianto
int Impianto::getID() {
    return this->ID;
}
//Restituisce una stringa con le info principali dell’impianto
std::string Impianto::Stampa() {
    std::string stato = acceso ? "ACCESO" : "SPENTO";

    return "Impianto: " + nome + "\n"
         + "ID: " + std::to_string(ID) + "\n"
         + "Stato: " + stato + "\n"
         + "Ultima accensione: " + ultimaAccensione.getTime();
}

//Var static
int Impianto::contId = 0;