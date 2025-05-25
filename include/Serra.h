//Qui vanno dichiarati i metodi e le costanti
#ifndef SERRA_H
#define SERRA_H

#include <map>
#include <memory>
#include "Impianto.h"
#include "Time.h"

// Classe Serra: gestisce un insieme di impianti e l'orario corrente
class Serra {
private:
    std::map<int, std::unique_ptr<Impianto>> impianti;
    Time now;
public:
    Serra();
    void AggiornaOrario(Time t); // Imposta un nuovo orario
    void AggiungiImpianto(std::unique_ptr<Impianto> nuovoImpianto); // Aggiunge un nuovo impianto
    void RimuoviImpianto(int ID);       // Rimuove impianto tramite ID
    void setTime(int hour, int minute); // Imposta orario direttamente con ore e minuti
    void ResetTime();                   // Reimposta l'orario a zero (00:00)
    Time getNow() const;               // Restituisce l'orario attuale
    std::string StampaStato() const;   // Restituisce stato completo di tutti gli impianti
    std::string ResetAllTimers();      // Resetta i timer di tutti gli impianti
    Impianto* getImpianto(const std::string& nome) const; // Restituisce puntatore all'impianto con il nome indicato
    std::string AccendiImpianto(const std::string& nome); // Accende impianto per nome
    std::string SpegniImpianto(const std::string& nome) const; // Spegne impianto per nome
};
#endif //SERRA_H