#include "Manuale.h"
// Costruttore: inizializza l'impianto con nome e timer di accensione/spegnimento
Manuale::Manuale(const std::string &Nome, Time Accensione, Time Spegnimento): Impianto(Nome), timerAccensione{Accensione}, timerSpegnimento{Spegnimento}{};

// Spegne l'impianto e ritorna un messaggio con l'orario di spegnimento programmato
std::string Manuale::Spegni() {
    this->acceso = false;
    return "Impianto manuale " + this->nome + " spento";
}

// Accende l'impianto e salva l'orario di accensione (now)
std::string Manuale::Accendi(Time now) {
    this->acceso = true;
    this->ultimaAccensione = now;
    return "Impianto manuale " + this->nome + " acceso";
}

// Controlla se è arrivato il momento di accendere o spegnere l'impianto
// (eseguito ogni minuto dalla serra)
std::string Manuale::OnTimeChanged(Time now) {
    if(!acceso && now == this->timerAccensione)
        return Accendi(now);
    if(acceso &&  now == this->timerSpegnimento)
        return Spegni();
    return "";
}

// Resetta i timer riportando accensione e spegnimento a 00:00
void Manuale::ResetTimers() {
    this->timerSpegnimento = Time(0,0);
    this->timerAccensione = Time(0,0);
}

std::string Manuale::Stampa() const {
    std::string stato = acceso ? "ACCESO" : "SPENTO";
    return "Impianto: " + nome +", ID: " + std::to_string(ID) + ", Stato: " + stato + ", Orario accensione: " + timerAccensione.getTime()+ ", Orario spegnimento: " + timerSpegnimento.getTime() + ", Ultima accensione: " + ultimaAccensione.getTime();
}

void Manuale::SetStart(Time start) {
    this->timerAccensione = start;
}

void Manuale::SetStop(Time stop) {
    this->timerSpegnimento = stop;
}