#include "Serra.h"

//Costruttore che inizializza il tempo a 0:0
Serra::Serra() : now(0, 0){}

//Richiama il setter della classe Time che gestisce l’avanzamento minuto per minuto
void Serra::AggiornaOrario(Time t) {
    setTime(t.Hour, t.Minute);
}

//DA FINIRE
//Aumento di uno alla volta i minuti => deve fare il check per ogni singolo impianto
void Serra::setTime(int hour, int minute) {
    if(hour > 23 || hour < 0 || minute > 59 || minute < 0)
        throw std::invalid_argument("Invalid time");        //Solleva un'eccezione

    while(now.Hour != hour || now.Minute != minute) {
        now++;
        //Ogni impianto controlla se deve accendersi/spegnersi con OnTimeChanged(now)
        for (auto it = impianti.begin(); it != impianti.end(); ++it) {
            it->second->OnTimeChanged(now);
        }
    }
}

// Aggiunge un nuovo impianto alla mappa usando il suo ID come chiave
void Serra::AggiungiImpianto(std::unique_ptr<Impianto> nuovoImpianto) {
    //unique_ptr non può essere copiato, ma solo spostato (tramite move())
    impianti.insert({nuovoImpianto->getID(), std::move(nuovoImpianto)});
}

// Rimuove un impianto tramite ID; se non trovato, solleva un'eccezione
void Serra::RimuoviImpianto(int ID) {
    //Se l'ID non esiste restituirà 0, altrimenti 1
    if(this->impianti.erase(ID) == 0)
        throw std::invalid_argument("Invalid ID");      //Solleva un'eccezione
}
// Accende un impianto cercandolo per nome; ritorna il messaggio corrispondente
std::string Serra::AccendiImpianto(const std::string& nome) {
    Impianto* imp = getImpianto(nome);
    if (imp == nullptr)
        throw std::invalid_argument("Impianto non trovato");    // Solleva un'eccezione
    return imp->Accendi(now);
}
// Spegne un impianto cercandolo per nome; ritorna il messaggio corrispondente
std::string Serra::SpegniImpianto(const std::string& nome) const {
    Impianto* imp = getImpianto(nome);
    if (imp == nullptr)
        throw std::invalid_argument("Impianto non trovato");    // Solleva un'eccezione
    return imp->Spegni();
}

void Serra::ResetTime() {
    //DEVE SPEGNERE OGNI IMPIANTO ANCORA
    this->now = Time(0,0);
}

// Ricerca di un impianto per nome
Impianto* Serra::getImpianto(const std::string& nome) const {
    for (auto it = impianti.begin(); it != impianti.end(); ++it) {
        const std::unique_ptr<Impianto>& ptr = it->second;
        if (ptr->getNome() == nome)
            return ptr.get();
    }
    return nullptr;
}
// Resetta i timer di tutti gli impianti (per impianti automatici o temporizzati)
std::string Serra::ResetAllTimers() {
    for (auto imp = impianti.begin(); imp != impianti.end(); ++imp)
        imp->second->ResetTimers();
    return "Timer di tutti gli impianti azzerati.";
}

// Ritorna l'orario attuale della serra
Time Serra::getNow() const {
    return this->now;
}

//DA FINIRE
std::string Serra::StampaStato() const {
    std::string msg = "";
    for (auto it = impianti.begin(); it != impianti.end(); ++it)
        msg+= it->second->Stampa() + "\n";
    return msg;
}
