#include "../include/Serra.h"

//Costruttore che inizializza il tempo a 0:0
Serra::Serra() : now(0, 0){}

//Richiama il setter della classe Time che gestisce l’avanzamento minuto per minuto
void Serra::AggiornaOrario(int hour, int minute) {
    now.setTime(hour, minute);
}

void Serra::RimuoviImpianto(int ID) {
    //Se l'ID non esiste restituirà 0, altrimenti 1
    if(this->impianti.erase(ID) == 0) {
        throw std::invalid_argument("Invalid ID");      ////Solleva un'eccezione
    }
}