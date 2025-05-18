#include "../include/Manuale.h"

Manuale::Manuale(const std::string &Nome, Time Accensione, Time Spegnimento): Impianto(Nome), accensione{Accensione}, spegnimento{Spegnimento}, contatore{accensione} {};

std::string Manuale::Spegni() override {
    contatore++;
    if(contatore == spegnimento) {
        this->acceso = false;
        contatore = accensione;
        return "Impianto spento manualmente alle ore: " + spegnimento.getTime();
    }
    return "";
}

std::string Manuale::Accendi(Time now) override{
    if(this->accensione == now) {
        this->acceso = true;
        this->ultimaAccensione = now;
        return "Impianto acceso alle ore: " + now.getTime();
    }
    return "";
}