#include "../include/Impianto.h"

Impianto::Impianto() {
    ID = 0;
    TipoPianta = "";
    Nome = "";
    Accesso = false;
}
//Accende l’impianto, imposta Accesso a true e salva l’orario di accensione
std::string Impianto::Accendi() {
    Accesso = true;
    ultimaAccensione = Accensione;
    return "[Accensione] L’impianto '" + Nome + "' è stato acceso";
}
//Spegne l’impianto, imposta Accesso a false
std::string Impianto::Spegni() {
    Accesso = false;
    return "[Spegnimento] L’impianto '" + Nome + "' è stato spento";
}
//Restituisce l'ID dell'impianto
int Impianto::getID() {
    return this->ID;
}
