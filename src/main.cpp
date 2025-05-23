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
using std::string;

int main() {
    Serra superSerra;
    UserInterface ui;
    std::unique_ptr<Impianto> impianto;
    string risposta;

    // 1) Ciclo di creazione impianti
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
        string nome;
        std::getline(cin, nome);

        if (scelta == 1) {
            float tempAcc, tempSpegn;
            cout << "Temperatura accensione: "; cin >> tempAcc;
            cout << "Temperatura spegnimento: "; cin >> tempSpegn;
            impianto = std::make_unique<ConTermometro>(nome, tempAcc, tempSpegn);
        }
        else if (scelta == 2) {
            int hStart, mStart, hStop, mStop;
            cout << "Accensione (h m): "; cin >> hStart >> mStart;
            cout << "Spegnimento (h m): "; cin >> hStop >> mStop;
            impianto = std::make_unique<Manuale>(nome, Time(hStart,mStart), Time(hStop,mStop));
        }
        else if (scelta == 3) {
            int hT, mT;
            cout << "Durata timer (h m): "; cin >> hT >> mT;
            impianto = std::make_unique<Automatico>(nome, Time(hT,mT));
        }
        superSerra.AggiungiImpianto(std::move(impianto));

        cout << "Vuoi continuare ad aggiungere impianti? (sì/no): ";
        cin >> risposta;
    } while (risposta == "sì" || risposta == "si");

    // 2) Ciclo di inserimento comandi
    cin.ignore();  // pulisci il newline rimasto
    do {
        cout << "\nInserisci comando: ";
        string comando;
        std::getline(cin, comando);
        ui.processCommand(comando, superSerra.getNow(), superSerra);

        cout << "Vuoi terminare il programma? (sì/no): ";
        cin >> risposta;
        cin.ignore();
    } while (risposta == "no" || risposta == "n");

    cout << "Programma terminato.\n";
    return 0;
}