#include <iostream>
#include <Serra.h>

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

        if (scelta == 1) {
            float tAcc, tSpegn;
            cout << "Temperatura di accensione: ";
            cin >> tAcc;
            cout << "Temperatura di spegnimento: ";
            cin >> tSpegn;
            //aggiungi alla serra
        } else if (scelta == 2) {
            int hA, mA, hS, mS;
            cout << "Ora e minuti di accensione (es. 8 30): ";
            cin >> hA >> mA;
            cout << "Ora e minuti di spegnimento (es. 18 45): ";
            cin >> hS >> mS;
            //aggiungi alla serra
        } else if (scelta == 3) {
            int hT, mT;
            cout << "Durata timer (ore minuti): ";
            cin >> hT >> mT;
            //aggiungi alla serra
        } else
            cout << "Scelta non valida!\n";

        cout << "Vuoi continuare ad aggiungere impianti? (sì/no): ";
        cin >> risposta;

    } while (risposta == "sì" || risposta == "si" || risposta == "SI" || risposta == "S");
    return 0;
}