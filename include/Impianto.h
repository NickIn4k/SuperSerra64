//Qui vanno dichiarati i metodi e le costanti
#ifndef IMPIANTO_H
#define IMPIANTO_H
#include <string>
#include "Time.h"

class Impianto {
protected:
    static int contId;               // Contatore statico per assegnare ID univoci
    int ID;                         // Identificatore univoco dell'impianto
    std::string nome;              // Nome dell'impianto
    bool acceso;                  //Stato dell'impianto: true = acceso, false = spento
    Time ultimaAccensione;       // Ora dell'ultima accensione
public:
    Impianto() = default;
    explicit Impianto(const std::string &Nome);
    int getID() const;                              //Restituisce l'ID
    std::string getNome() const;                    // Restituisce il nome
    virtual std::string Accendi(Time accensione) = 0; // Accende l'impianto
    virtual std::string Spegni() = 0;                // Spegne l'impianto
    virtual void OnTimeChanged(Time now) = 0;       // Aggiornamento periodico con il tempo corrente
    virtual void ResetTimers() = 0;                // Reset dei timer interni
    std::string Stampa() const;                   // Restituisce le informazioni dell'impianto

    virtual ~Impianto() = default;             // Distruttore virtuale
};
#endif //IMPIANTO_H