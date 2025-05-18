#include "../include/Automatico.h"

Automatico::Automatico(const std::string &Nome, Time newTimer): Impianto(Nome), timerSpegnimento{newTimer} {};

void Automatico::SetTimer(Time newTimer) {
    this->timerSpegnimento = newTimer;
}

void Automatico::SetStart(Time accensione) {
    this->accensione = accensione;
}

std::string Automatico::Spegni() override {
    this->contatore = Time(0,0);
    acceso = false;
    return "Impianto spento automaticamente";
}

std::string Automatico::Accendi(Time now) override{
    this->acceso = true;
    this->ultimaAccensione = now;
    return "Impianto acceso alle ore: " + now.getTime();
}

void Automatico::ChangeTime(Time now) override {
    if(!acceso && now == this->accensione)
        Accendi(now);
    else{
        contatore++;
        if(this->contatore == this->timerSpegnimento)
            Spegni();
    }
}
