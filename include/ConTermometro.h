#ifndef CONTERMOMETRO_H
#define CONTERMOMETRO_H
#include "../include/Impianto.h"
#include "../include/Time.h"

class ConTermometro: public Impianto {
protected:
    float tempAccensione;
    float tempSpegnimento;
public:
    ConTermometro() = default;
    ConTermometro(std::string Nome, Time Accensione, Time Spegnimento);
    std::string Spegni() override;
    std::string Accendi(Time accensione) override;
};
#endif //CONTERMOMETRO_H
