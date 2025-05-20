#include <iostream>
#include <Serra.h>
#include "../include/ConTermometro.h"
#include "../include/Manuale.h"
#include "../include/Automatico.h"

using std::cout, std::cin, std::string;

int main() {
    Serra SuperSerra;
    string risposta;
    do {
        cout << "\n--- MENU CREAZIONE IMPIANTO ---\n";
        cout << "1. Con Termometro\n";
        cout << "2. Manuale\n";
        cout << "3. Automatico\n";
        cout << "Scegli il tipo di impianto (1-3): ";
        int scelta;
        cin >> scelta;

        string nome;
        cout << "Inserisci il nome dell'impianto: ";
        cin.ignore(); // pulisce il buffer
        getline(std::cin, nome);

        std::unique_ptr<Impianto> impianto;

        if (scelta == 1) {
            float tAcc, tSpegn;
            cout << "Temperatura di accensione: ";
            cin >> tAcc;
            cout << "Temperatura di spegnimento: ";
            cin >> tSpegn;
            //aggiungi alla serra
            impianto = std::make_unique<ConTermometro>(nome, tAcc, tSpegn);
            SuperSerra.AggiungiImpianto(std::move(impianto));
        } else if (scelta == 2) {
            int hA, mA, hS, mS;
            cout << "Ora e minuti di accensione (es. 8 30): ";
            cin >> hA >> mA;
            cout << "Ora e minuti di spegnimento (es. 18 45): ";
            cin >> hS >> mS;
            //aggiungi alla serra
            Time accensione(hA, mA);
            Time spegnimento(hS, mS);
            impianto = std::make_unique<Manuale>(nome, accensione, spegnimento);
            SuperSerra.AggiungiImpianto(std::move(impianto));
        } else if (scelta == 3) {
            int hT, mT;
            cout << "Durata timer (ore minuti): ";
            cin >> hT >> mT;
            //aggiungi alla serra
            Time durata(hT, mT);
            impianto = std::make_unique<Automatico>(nome, durata);
            SuperSerra.AggiungiImpianto(std::move(impianto));
        } else
            cout << "Scelta non valida!\n";

        cout << "Vuoi continuare ad aggiungere impianti? (sì/no): ";
        cin >> risposta;

    } while (risposta == "sì" || risposta == "si" || risposta == "SI" || risposta == "S");
    return 0;
}