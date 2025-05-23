#ifndef AUTOMATICO_H
#define AUTOMATICO_H
#include <string>
#include "../include/Time.h"
#include "../include/Impianto.h"

class Automatico: public Impianto {
private:
    Time contatore;
protected:
    Time timerSpegnimento;
    Time timerAccensione;
public:
    Automatico() = default;
    Automatico(const std::string &Nome, Time newTimer);
    void SetStop(Time newTimer);
    void SetStart(Time accensione);
    std::string Spegni() override;
    std::string Accendi(Time now) override;
    void OnTimeChanged(Time now) override;
    void ResetTimers() override;
};
#endif //AUTOMATICO_H
