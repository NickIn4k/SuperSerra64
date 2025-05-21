#include "../include/Manuale.h"

Manuale::Manuale(const std::string &Nome, Time Accensione, Time Spegnimento): Impianto(Nome), accensione{Accensione}, spegnimento{Spegnimento}{};

std::string Manuale::Spegni() override {
    this->acceso = false;
    return "Impianto manuale spento alle ore: " + spegnimento.getTime();
}

std::string Manuale::Accendi(Time now) override{
    this->acceso = true;
    this->ultimaAccensione = now;
    return "Impianto manuale acceso alle ore: " + now.getTime();
}

void Manuale::OnTimeChanged(Time now) {
    if(!acceso && now == this->accensione)
        Accendi(now);
    else if(acceso &&  now == this->spegnimento)
        Spegni();
}