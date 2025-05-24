#include "Manuale.h"

Manuale::Manuale(const std::string &Nome, Time Accensione, Time Spegnimento): Impianto(Nome), timerAccensione{Accensione}, timerSpegnimento{Spegnimento}{};

std::string Manuale::Spegni() {
    this->acceso = false;
    return "Impianto manuale spento alle ore: " + timerSpegnimento.getTime();
}

std::string Manuale::Accendi(Time now) {
    this->acceso = true;
    this->ultimaAccensione = now;
    return "Impianto manuale acceso alle ore: " + now.getTime();
}

void Manuale::OnTimeChanged(Time now) {
    if(!acceso && now == this->timerAccensione)
        Accendi(now);
    else if(acceso &&  now == this->timerSpegnimento)
        Spegni();
}

void Manuale::ResetTimers() {
    this->timerSpegnimento = Time(0,0);
    this->timerAccensione = Time(0,0);
}