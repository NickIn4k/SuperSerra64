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
    Serra superSerra;       // Oggetto principale che gestisce tutti gli impianti
    UserInterface ui;       // Gestione interazione con utente e log
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

            // Controllo input non valido
            if (cin.fail() || scelta < 1 || scelta > 3) {
                cin.clear(); // Ripristina lo stato di cin
                cin.ignore(); // Scarta input errato
            }

        }while(scelta < 1 || scelta > 3 || cin.fail());

        cout << "Nome impianto: ";
        cin.ignore();           // Per evitare problemi con getline/cin
        std::string nome;
        cin >> nome;
// Impianto con Termometro
        if (scelta == 1) {
            float tempAcc, tempSpegn;
            do {
                cout << "Temperatura accensione in C: ";
                cin >> tempAcc;
                cout << "Temperatura spegnimento in C: ";
                cin >> tempSpegn;
                // Controlla valori validi per temperatura
                if (cin.fail() || tempAcc < 0.0f || tempSpegn > 50.0f) {
                    cin.clear();
                    cin.ignore();
                }
                else
                    impianto = std::make_unique<ConTermometro>(nome, tempAcc, tempSpegn);
            }while(cin.fail() || (tempAcc < 0.0f || tempSpegn > 50.0f));
        }
//Impianto manuale
        else if (scelta == 2) {
            int hStart, mStart, hStop, mStop;
            do {
                cout << "Accensione (ore e minuti separati da uno spazio): ";
                cin >> hStart >> mStart;
                cout << "Spegnimento (ore e minuti separati da uno spazio): ";
                cin >> hStop >> mStop;
                // Validazione orari inseriti
                if (cin.fail() || hStart < 0 || hStart > 23 || mStart < 0 || mStart > 59) {
                    cin.clear();
                    cin.ignore();
                }
                else
                    impianto = std::make_unique<Manuale>(nome, Time(hStart,mStart), Time(hStop,mStop));
            }while(cin.fail() || hStart < 0 || hStart > 23 || mStart < 0 || mStart > 59);
        }
//Impianto automatico
        else if (scelta == 3) {
            int hourTimer, minuteTimer;
            do {
                cout << "Durata timer (ore e minuti separati da uno spazio): ";
                cin >> hourTimer >> minuteTimer;
                if (cin.fail() || hourTimer < 0 || hourTimer > 23 || minuteTimer < 0 || minuteTimer > 59) {
                    cin.clear();
                    cin.ignore();
                }
                else
                    impianto = std::make_unique<Automatico>(nome, Time(hourTimer,minuteTimer));
            }while(cin.fail() || hourTimer < 0 || hourTimer > 23 || minuteTimer < 0 || minuteTimer > 59);
        }
        // Aggiunta impianto creato alla serra
        superSerra.AggiungiImpianto(std::move(impianto));

        cout << "Vuoi continuare ad aggiungere impianti? (si'/no): ";
        cin >> risposta;
    } while (risposta == "si'" || risposta == "si");

    // Ciclo di inserimento comandi dall'utente
    cin.ignore();  // Pulisci possibili linee rimaste
    do {
        cout << "\nInserisci comando: ";
        std::string comando;
        std::getline(cin, comando);
        // Processa il comando tramite l'interfaccia utente
        ui.processCommand(comando, superSerra.getNow(), superSerra);
    } while (true);

    return 0;
}