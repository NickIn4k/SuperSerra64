#ifndef MANUALE_H
#define MANUALE_H
#include <string>
#include "Time.h"
#include "Impianto.h"

class Manuale: public Impianto {
protected:
    Time timerSpegnimento;
    Time timerAccensione;
public:
    Manuale() = default;
    Manuale(const std::string &Nome, Time Accensione, Time Spegnimento);
    std::string Spegni() override;
    std::string Accendi(Time now) override;
    std::string OnTimeChanged(Time now) override;
    void ResetTimers() override;
    std::string Stampa() const override; // Restituisce le informazioni dell'impianto
};
#endif //MANUALE_H
