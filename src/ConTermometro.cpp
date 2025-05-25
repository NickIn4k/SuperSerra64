#include "ConTermometro.h"

ConTermometro::ConTermometro(const std::string &Nome, float tempAccensione, float tempSpegnimento): Impianto(Nome), tempAccensione{tempAccensione}, tempSpegnimento {tempSpegnimento} {
    tempAttuale = 20.0f;
    ultimoAggiornamento = Time(0,0);
}

std::string ConTermometro::Spegni() {
    this->acceso = false;
    return "Impianto spento con temperatura: " + std::to_string(tempAttuale);
}

std::string ConTermometro::Accendi(Time now) {
    this->acceso = true;
    this->ultimaAccensione = now;
    return "Impianto acceso alle ore: " + now.getTime() + " con temperatura: " + std::to_string(tempAttuale);
}

void ConTermometro::OnTimeChanged(Time now) {
    int diffMin;
    if(!acceso) {
        tempAttuale-=randomFloat(0.01f, 0.05f);
        if(tempAttuale<=tempAccensione)
            Accendi(now);
    }
    else {
        diffMin = ultimoAggiornamento.DifferenzaMin(now);
        if(diffMin >= 60)
            tempAttuale+=randomFloat(0.75f, 1.0f);
        if(tempAttuale >= tempSpegnimento)
            Spegni();
    }
    ultimoAggiornamento = now;
}

// Questo metodo non serve in questa classe => non c'è un timer da resettare!
void ConTermometro::ResetTimers(){}

float ConTermometro::randomFloat(float min, float max) const {
    return min + ((float)rand() /(float)RAND_MAX) * (max - min);
}

