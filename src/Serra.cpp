#include "../include/Serra.h"

//Costruttore che inizializza il tempo a 0:0
Serra::Serra() : now(0, 0){}

//Richiama il setter della classe Time che gestisce l’avanzamento minuto per minuto
void Serra::AggiornaOrario(int hour, int minute) {
    now.setTime(hour, minute);
}

void Serra::AggiungiImpianto(std::string n, Time a) {
    std::unique_ptr<Impianto> nuovoImpianto = std::make_unique<Impianto>(n, a);
    //unique_ptr non può essere copiato, ma solo spostato (tramite move())
    impianti.insert({nuovoImpianto->getID(), std::move(nuovoImpianto)});
}

void Serra::RimuoviImpianto(int ID) {
    //Se l'ID non esiste restituirà 0, altrimenti 1
    if(this->impianti.erase(ID) == 0) {
        throw std::invalid_argument("Invalid ID");      //Solleva un'eccezione
    }
}

std::string Serra::SpegniImpiantoManuale(int ID) {

}