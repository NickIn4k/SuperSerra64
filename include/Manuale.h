#ifndef MANUALE_H
#define MANUALE_H
#include <string>
#include "../include/Time.h"
#include "../include/Impianto.h"

class Manuale: public Impianto {
protected:
    Time spegnimento;
    Time accensione;
public:
    Manuale() = default;
    Manuale(const std::string &Nome, Time Accensione, Time Spegnimento);
    std::string Spegni() override;
    std::string Accendi(Time now) override;
    void OnTimeChanged(Time now) override;
    void ResetTimers(); //Da implementare
};
#endif //MANUALE_H
