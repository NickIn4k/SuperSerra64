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
        int scelta;
        do {
            cout << "\n--- MENU CREAZIONE IMPIANTO ---\n"
             << "1. Con Termometro\n"
             << "2. Manuale\n"
             << "3. Automatico\n"
             << "Scegli (1-3): ";

            cin >> scelta;

            if (cin.fail() || scelta < 1 || scelta > 3) {
                cin.clear(); // Ripristina lo stato di cin
                cin.ignore();
            }

        }while(scelta < 1 || scelta > 3 || cin.fail());

        cout << "Nome impianto: ";
        cin.ignore();
        std::string nome;
        cin >> nome;

        if (scelta == 1) {
            float tempAcc, tempSpegn;
            do {
                cout << "Temperatura accensione: ";
                cin >> tempAcc;
                cout << "Temperatura spegnimento: ";
                cin >> tempSpegn;

                if (cin.fail() || tempAcc < 0.0f || tempSpegn > 50.0f) {
                    cin.clear();
                    cin.ignore();
                }
            }while(cin.fail() || (tempAcc < 0.0f || tempSpegn > 50.0f));

            impianto = std::make_unique<ConTermometro>(nome, tempAcc, tempSpegn);
        }
        else if (scelta == 2) {
            int hStart, mStart, hStop, mStop;

            cout << "Accensione (h m): ";
            cin >> hStart >> mStart;
            if (cin.fail() || hStart < 0 || hStart > 23 || mStart < 0 || mStart > 59) {
                cin.clear();
                cin.ignore();
            }
            cout << "Spegnimento (h m): ";
            cin >> hStop >> mStop;
            if (cin.fail() || hStart < 0 || hStart > 23 || mStart < 0 || mStart > 59) {
                cin.clear();
                cin.ignore();
            }

            impianto = std::make_unique<Manuale>(nome, Time(hStart,mStart), Time(hStop,mStop));
        }
        else if (scelta == 3) {
            int hourTimer, minuteTimer;
            cout << "Durata timer (h m): ";
            cin >> hourTimer >> minuteTimer;
            if (cin.fail() || hourTimer < 0 || hourTimer > 23 || minuteTimer < 0 || minuteTimer > 59) {
                cin.clear();
                cin.ignore();
            }
            impianto = std::make_unique<Automatico>(nome, Time(hourTimer,minuteTimer));
        }
        superSerra.AggiungiImpianto(std::move(impianto));

        cout << "Vuoi continuare ad aggiungere impianti? (si'/no): ";
        cin >> risposta;
    } while (risposta == "si'" || risposta == "si");

    // Inserimento comandi
    cin.ignore();  // Pulisci possibili linee rimaste
    do {
        cout << "\nInserisci comando: ";
        std::string comando;
        std::getline(cin, comando);
        ui.processCommand(comando, superSerra.getNow(), superSerra);
    } while (true);

    return 0;
}