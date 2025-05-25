#ifndef AUTOMATICO_H
#define AUTOMATICO_H
#include <string>
#include "Time.h"
#include "Impianto.h"

class Automatico: public Impianto {
private:
    Time contMin;
protected:
    Time timerSpegnimento;  // Il timer per lo spegnimento
    Time orarioAccensione;  // L'ora di accensione
public:
    Automatico() = default;
    Automatico(const std::string &Nome, Time newTimer);
    void SetStop(Time newTimer);
    void SetStart(Time accensione);
    std::string Spegni() override;
    std::string Accendi(Time now) override;
    std::string OnTimeChanged(Time now) override;
    void ResetTimers() override;
    std::string Stampa() const override; // Restituisce le informazioni dell'impianto

};
#endif //AUTOMATICO_H
