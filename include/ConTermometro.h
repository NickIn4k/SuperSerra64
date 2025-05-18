#ifndef CONTERMOMETRO_H
#define CONTERMOMETRO_H
#include "../include/Impianto.h"
#include "../include/Time.h"

class ConTermometro: public Impianto {
private:
    float cont;
    Time ultimoAggiornamento;
protected:
    float tempAccensione;
    float tempSpegnimento;
    float randomFloat(float min, float max);
public:
    ConTermometro() = default;
    ConTermometro(const std::string &Nome, float tempAccensione, float tempSpegnimento);
    std::string Spegni() override;
    std::string Accendi(Time accensione) override;
    void ChangeTime(Time now) override;
};
#endif //CONTERMOMETRO_H
