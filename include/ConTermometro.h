#ifndef CONTERMOMETRO_H
#define CONTERMOMETRO_H
#include "Impianto.h"
#include "Time.h"

class ConTermometro: public Impianto {
private:
    float tempAttuale;
    Time ultimoAggiornamento;
protected:
    float tempAccensione;
    float tempSpegnimento;
    float randomFloat(float min, float max) const;
public:
    ConTermometro() = default;
    ConTermometro(const std::string &Nome, float tempAccensione, float tempSpegnimento);
    std::string Spegni() override;
    std::string Accendi(Time accensione) override;
    std::string OnTimeChanged(Time now) override;
    void ResetTimers() override;
};
#endif //CONTERMOMETRO_H
