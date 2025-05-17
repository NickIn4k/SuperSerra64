//Qui vanno dichiarati i metodi e le costanti
#ifndef SERRA_H
#define SERRA_H

#include <map>
#include <memory>
#include "../include/Impianto.h"
#include "../include/Time.h"

class Serra {
private:
    std::map<int, std::unique_ptr<Impianto>> impianti;
    Time now;
public:
    Serra();
    void AggiornaOrario(int hour, int minute);
    void AggiungiImpianto(std::string n, Time a);
    void RimuoviImpianto(int ID);
    std::string StampaStato() const;
    std::string SpegniImpiantoManuale(int ID);
};
#endif //SERRA_H