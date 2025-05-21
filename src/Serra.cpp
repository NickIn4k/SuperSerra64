#include "../include/Serra.h"

//Costruttore che inizializza il tempo a 0:0
Serra::Serra() : now(0, 0){}

//Richiama il setter della classe Time che gestisce l’avanzamento minuto per minuto
void Serra::AggiornaOrario(Time t) {
    setTime(t.Hour, t.Minute);
}

//Aumento di uno alla volta i minuti => deve fare il check per ogni singolo impianto
void Serra::setTime(int hour, int minute) {
    if(hour > 23 || hour < 0 || minute > 59 || minute < 0)
        throw std::invalid_argument("Invalid time");        //Solleva un'eccezione

    while(now.Hour != hour || now.Minute != minute) {
        now++;
        //CHECK PER OGNI SINGOLO IMPIANTO CON IL METODO OnTimeChanged(now)
        for (auto it = impianti.begin(); it != impianti.end(); ++it) {
            it->second->OnTimeChanged(now);
        }
    }
}

void Serra::AggiungiImpianto(std::unique_ptr<Impianto> nuovoImpianto) {
    //unique_ptr non può essere copiato, ma solo spostato (tramite move())
    impianti.insert({nuovoImpianto->getID(), std::move(nuovoImpianto)});
}

void Serra::RimuoviImpianto(int ID) {
    //Se l'ID non esiste restituirà 0, altrimenti 1
    if(this->impianti.erase(ID) == 0) {
        throw std::invalid_argument("Invalid ID");      //Solleva un'eccezione
    }
}

std::string Serra::SpegniImpianto(int ID) {

}

void Serra::ResetTime() {
    this->now = Time(0,0);
}

//Ricerca di un impianto per nome
Impianto* Serra::getImpianto(std::string nome) const {
    for (auto it = impianti.begin(); it != impianti.end(); ++it) {
        const std::unique_ptr<Impianto>& ptr = it->second;
        if (ptr->getNome() == nome) {
            return ptr.get();
        }
    }
    return nullptr;
}