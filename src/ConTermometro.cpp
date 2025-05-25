#include "ConTermometro.h"
// Costruttore: inizializza nome impianto e soglie di accensione/spegnimento
ConTermometro::ConTermometro(const std::string &Nome, float tempAccensione, float tempSpegnimento): Impianto(Nome), tempAccensione{tempAccensione}, tempSpegnimento {tempSpegnimento} {
    tempAttuale = 20.0f;                     // temperatura iniziale
    ultimoAggiornamento = Time(0,0);   // inizializza orario dell'ultimo aggiornamento
}

// Spegne l’impianto e restituisce un messaggio con la temperatura attuale
std::string ConTermometro::Spegni() {
    this->acceso = false;     // Imposta stato su spento
    return "Impianto spento con temperatura: " + std::to_string(tempAttuale);
}

// Accende l’impianto e salva l’orario di accensione, restituendo un messaggio
std::string ConTermometro::Accendi(Time now) {
    this->acceso = true;
    this->ultimaAccensione = now;
    return "Impianto acceso alle ore: " + now.getTime() + " con temperatura: " + std::to_string(tempAttuale);
}

// Metodo chiamato quando cambia l'orario per aggiornare lo stato in base alla temperatura
void ConTermometro::OnTimeChanged(Time now) {
    int diffMin;
    if(!acceso) {
        // Se spento, la temperatura scende leggermente
        tempAttuale-=randomFloat(0.01f, 0.05f);

        // Se la temperatura scende sotto la soglia, accendi l’impianto
        if(tempAttuale<=tempAccensione)
            Accendi(now);
    }
    else {
        // Se acceso, verifica quanto tempo è passato dall’ultimo aggiornamento
        diffMin = ultimoAggiornamento.DifferenzaMin(now);
        // Dopo almeno 60 minuti, aumenta la temperatura
        if(diffMin >= 60)
            tempAttuale+=randomFloat(0.75f, 1.0f);
        // Se la temperatura supera la soglia, spegni l’impianto
        if(tempAttuale >= tempSpegnimento)
            Spegni();
    }

    // Aggiorna l’orario dell’ultima modifica
    ultimoAggiornamento = now;
}

// Questo metodo non serve in questa classe => non c'è un timer da resettare!
void ConTermometro::ResetTimers(){}

// Genera un numero casuale tra min e max
float ConTermometro::randomFloat(float min, float max) const {
    return min + ((float)rand() /(float)RAND_MAX) * (max - min);
}

