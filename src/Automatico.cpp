#include "Automatico.h"

// Costruttore: inizializza il nome dell’impianto e il timer di spegnimento
Automatico::Automatico(const std::string &Nome, Time newTimer): Impianto(Nome), timerSpegnimento{newTimer} {};

// Imposta un nuovo tempo per lo spegnimento automatico
void Automatico::SetStop(Time newTimer) {
    this->timerSpegnimento = newTimer;
}

// Imposta l'orario in cui l'impianto deve accendersi automaticamente
void Automatico::SetStart(Time accensione) {
    this->orarioAccensione = accensione;
}

// Spegne l’impianto, azzera il contatore e restituisce un messaggio
std::string Automatico::Spegni() {
    this->contMin = Time(0,0);
    acceso = false;
    return "Impianto automatico " + this->nome + " spento";
}

// Accende l’impianto, salva l'orario di accensione e restituisce un messaggio
std::string Automatico::Accendi(Time now) {
    this->acceso = true;
    this->ultimaAccensione = now;
    return "Impianto acceso " + this->nome;
}

// Metodo chiamato ad ogni variazione dell’orario, controlla se è il momento di accendere o spegnere l’impianto
std::string Automatico::OnTimeChanged(Time now) {
    if(!acceso && now == this->orarioAccensione)
        return Accendi(now);

    this->contMin++;
    if(this->contMin == this->timerSpegnimento)
        return Spegni();

    return "";
}
// Reimposta entrambi i timer (accensione e spegnimento) a 00:00
void Automatico::ResetTimers() {
    this->timerSpegnimento = Time(0,0);
    this->orarioAccensione = Time(0,0);
}

