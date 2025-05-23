#include "../include/ConTermometro.h"

ConTermometro::ConTermometro(const std::string &Nome, float tempAccensione, float tempSpegnimento): Impianto(Nome), tempAccensione{tempAccensione}, tempSpegnimento {tempSpegnimento} {
    cont = 20.0;
    ultimoAggiornamento = Time(0,0);
}

std::string ConTermometro::Spegni() {
    this->acceso = false;
    return "Impianto spento con temperatura: " + std::to_string(cont);
}

std::string ConTermometro::Accendi(Time now) {
    this->acceso = true;
    this->ultimaAccensione = now;
    return "Impianto acceso alle ore: " + now.getTime() + " con temperatura: " + std::to_string(cont);
}

void ConTermometro::OnTimeChanged(Time now) {
    int diffMin;
    if(!acceso) {
        cont-=randomFloat(0.01f, 0.05f);
        if(cont<=tempAccensione)
            Accendi(now);
    }
    else {
        diffMin = ultimoAggiornamento.DifferenzaMin(now);
        if(diffMin >= 60)
            cont+=randomFloat(0.75f, 1.0f);
        if(cont >= tempSpegnimento)
            Spegni();
    }
    ultimoAggiornamento = now;
}

// Questo metodo non serve in questa classe => non c'è un timer da resettare!
void ConTermometro::ResetTimers(){}

float ConTermometro::randomFloat(float min, float max) const {
    return min + ((float)rand() /(float)RAND_MAX) * (max - min);
}

