#include "../include/Automatico.h"

Automatico::Automatico(const std::string &Nome, Time newTimer): Impianto(Nome), timerSpegnimento{newTimer} {};

void Automatico::SetTimer(Time newTimer) {
    this->timerSpegnimento = newTimer;
}

void Automatico::SetStart(Time accensione) {
    this->timerAccensione = accensione;
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

void Automatico::OnTimeChanged(Time now) override {
    if(!acceso && now == this->timerAccensione)
        Accendi(now);
    else{
        contatore++;
        if(this->contatore == this->timerSpegnimento)
            Spegni();
    }
}

void Automatico::ResetTimers() {
    this->timerSpegnimento = Time(0,0);
    this->timerAccensione = Time(0,0);
}

