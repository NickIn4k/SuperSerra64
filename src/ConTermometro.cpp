#include "ConTermometro.h"

// Costruttore: inizializza nome impianto e soglie di accensione/spegnimento
ConTermometro::ConTermometro(const std::string &Nome, float tempAccensione, float tempSpegnimento): Impianto(Nome), tempAccensione{tempAccensione}, tempSpegnimento {tempSpegnimento} {
    tempAttuale = 28.0f;                     // temperatura iniziale
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
    return "Impianto " + this->nome + " acceso con temperatura: " + std::to_string(tempAttuale);
}

// Metodo chiamato quando cambia l'orario per aggiornare lo stato in base alla temperatura
std::string ConTermometro::OnTimeChanged(Time now) {
    // Calcola minuti passati dall'ultimo aggiornamento
    int diffMin = ultimoAggiornamento.DifferenzaMin(now);
    if (diffMin >= 0) {
        if (!acceso) {
            // Impianto spento: ogni minuto diminuisce
            tempAttuale -= randomFloat(0.01f, 0.05f);

            // Aggiornamento
            ultimoAggiornamento = now;

            if (tempAttuale < tempAccensione)
                return Accendi(now);
        } else {
            // Impianto acceso: ogni 60 minuti aumenta
            if (diffMin >= 60) {
                tempAttuale += randomFloat(0.75f, 1.0f);

                // Se supera la soglia massima, spegni
                if (tempAttuale >= tempSpegnimento)
                    return Spegni();

                // Reset
                ultimoAggiornamento = now;
            }
        }
    }

    return "";
}
// Questo metodo non serve in questa classe => non c'è un timer da resettare!
void ConTermometro::ResetTimers(){}

// Genera un numero casuale tra min e max
float ConTermometro::randomFloat(float min, float max) const {
    return min + ((float)rand() /(float)RAND_MAX) * (max - min);
}

std::string ConTermometro::Stampa() const {
    std::string stato = acceso ? "ACCESO" : "SPENTO";
    return "Impianto: " + nome +", ID: " + std::to_string(ID) + ", Stato: " + stato + ", Temperatura di accensione: " + std::to_string(tempAccensione) + ", Temperatura di spegnimento: " + std::to_string(tempSpegnimento) + ", Temperatura attuale: " + std::to_string(tempAttuale) + ", Ultima accensione: " + ultimaAccensione.getTime();
}