#include "Manuale.h"
// Costruttore: inizializza l'impianto con nome e timer di accensione/spegnimento
Manuale::Manuale(const std::string &Nome, Time Accensione, Time Spegnimento): Impianto(Nome), timerAccensione{Accensione}, timerSpegnimento{Spegnimento}{};

// Spegne l'impianto e ritorna un messaggio con l'orario di spegnimento programmato
std::string Manuale::Spegni() {
    this->acceso = false;
    return "Impianto manuale spento alle ore: " + timerSpegnimento.getTime();
}

// Accende l'impianto e salva l'orario di accensione (now)
std::string Manuale::Accendi(Time now) {
    this->acceso = true;
    this->ultimaAccensione = now;
    return "Impianto manuale acceso alle ore: " + now.getTime();
}
// Controlla se è arrivato il momento di accendere o spegnere l'impianto
// (eseguito ogni minuto dalla serra)
void Manuale::OnTimeChanged(Time now) {
    if(!acceso && now == this->timerAccensione)
        Accendi(now);
    else if(acceso &&  now == this->timerSpegnimento)
        Spegni();
}
// Resetta i timer riportando accensione e spegnimento a 00:00
void Manuale::ResetTimers() {
    this->timerSpegnimento = Time(0,0);
    this->timerAccensione = Time(0,0);
}