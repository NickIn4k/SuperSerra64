#include <iostream>
#include <memory>
#include <string>

#include "Serra.h"
#include "ConTermometro.h"
#include "Manuale.h"
#include "Automatico.h"
#include "UserInterface.h"

using std::cout;
using std::cin;

int main() {
    Serra superSerra;
    UserInterface ui;
    std::unique_ptr<Impianto> impianto;
    std::string risposta;

    // Creazione impianti
    do {
        cout << "\n--- MENU CREAZIONE IMPIANTO ---\n"
             << "1. Con Termometro\n"
             << "2. Manuale\n"
             << "3. Automatico\n"
             << "Scegli (1-3): ";
        int scelta;
        cin >> scelta;

        cout << "Nome impianto: ";
        cin.ignore();
        std::string nome;
        cin >> nome;

        if (scelta == 1) {
            float tempAcc, tempSpegn;
            cout << "Temperatura accensione: ";
            cin >> tempAcc;
            cout << "Temperatura spegnimento: ";
            cin >> tempSpegn;
            impianto = std::make_unique<ConTermometro>(nome, tempAcc, tempSpegn);
        }
        else if (scelta == 2) {
            int hStart, mStart, hStop, mStop;
            cout << "Accensione (h : m): ";
            cin >> hStart >> mStart;
            cout << "Spegnimento (h : m): ";
            cin >> hStop >> mStop;
            impianto = std::make_unique<Manuale>(nome, Time(hStart,mStart), Time(hStop,mStop));
        }
        else if (scelta == 3) {
            int hourTimer, minuteTimer;
            cout << "Durata timer (h m): ";
            cin >> hourTimer >> minuteTimer;
            impianto = std::make_unique<Automatico>(nome, Time(hourTimer,minuteTimer));
        }
        superSerra.AggiungiImpianto(std::move(impianto));

        cout << "Vuoi continuare ad aggiungere impianti? (sì/no): ";
        cin >> risposta;
    } while (risposta == "sì" || risposta == "si");

    // Inserimento comandi
    cin.ignore();  // Pulisci possibili linee rimaste
    do {
        cout << "\nInserisci comando: ";
        std::string comando;
        std::getline(cin, comando);
        ui.processCommand(comando, superSerra.getNow(), superSerra);

        cout << "Vuoi terminare il programma? (sì/no): ";
        cin >> risposta;
        cin.ignore();
    } while (risposta == "no" || risposta == "n");

    cout << "Programma terminato.\n";
    return 0;
}