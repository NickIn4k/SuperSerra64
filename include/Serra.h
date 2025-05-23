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
    void AggiornaOrario(Time t);
    void AggiungiImpianto(std::unique_ptr<Impianto> nuovoImpianto);
    void RimuoviImpianto(int ID);
    void setTime(int hour, int minute);
    void ResetTime();
    Time getNow() const;
    std::string StampaStato() const;
    std::string ResetAllTimers();
    Impianto* getImpianto(const std::string& nome) const;
    std::string AccendiImpianto(const std::string& nome);
    std::string SpegniImpianto(const std::string& nome) const;
};
#endif //SERRA_H