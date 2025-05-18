#include "../include/Automatico.h"

Automatico::Automatico(const std::string &Nome, Time newTimer): Impianto(Nome), timerSpegnimento{newTimer} {};

void Automatico::SetTimer(Time newTimer) {
    this->timerSpegnimento = newTimer;
}

void Automatico::SetStart(Time accensione) {
    this->accensione = accensione;
}

std::string Automatico::Spegni() override {
    contatore++;
    if(this->contatore== this->timerSpegnimento) {
        this->contatore = Time(0,0);
        acceso = false;
        return "Impianto spento automaticamente";
    }
    return "";
}

std::string Automatico::Accendi(Time now) override{
    if(this->accensione == now) {
        this->acceso = true;
        this->ultimaAccensione = now;
        return "Impianto acceso alle ore: " + now.getTime();
    }
    return "";
}