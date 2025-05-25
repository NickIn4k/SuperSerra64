#include "UserInterface.h"
#include "Automatico.h"
#include "Manuale.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

// Logga un messaggio sulla console e nel file di log (solo se errorLevel == 0)
void UserInterface::logMessage(const Time &time, const std::string &message, const int &errorLevel) {
    openFile();         // Assicura che il file sia aperto prima di scrivere
    if (errorLevel == 0) {
        std::string msg = "[" + time.getTime() + "]\t" + message + "\n";
        std::cout << msg;

        if (logFile.is_open())
            logFile << msg << std::endl;    // Scrive anche su file
    } else if (errorLevel == 1)
        std::cerr << "[" << time.getTime() << "]\t" << message << std::endl;
}

// Divide un comando testuale in token, gestendo i nomi dispositivo composti
std::vector<std::string> UserInterface::commandParser(const std::string &command) {
    std::vector<std::string> tokens;
    std::istringstream ss(command);
    std::string token;

    bool isDeviceName = false;
    std::string deviceName;

    while (ss >> token) {
        if (isDeviceName) {
            // Se troviamo "on", "off" o orari, termina il nome del dispositivo
            if (token == "on" || token == "off" || token.find(':') != std::string::npos) {
                if (!deviceName.empty()) {
                    tokens.push_back(deviceName);
                    deviceName.clear();
                }
                isDeviceName = false;
            }
        }
        // Comandi che indicano che il prossimo token sarà un nome composto
        if (token == "set" || token == "rm" || token == "show") {
            tokens.push_back(token);
            isDeviceName = true;
            continue;
        }
        // Ricostruisce nomi di dispositivi con spazi
        if (isDeviceName) {
            if (!deviceName.empty()) {
                deviceName += " ";
            }
            deviceName += token;
        } else {
            tokens.push_back(token);
        }
    }

    if (!deviceName.empty()) {
        tokens.push_back(deviceName);
    }

    return tokens;
}

// Esegue un comando interpretando i token e interagendo con Serra
void UserInterface::processCommand(const std::string &command, const Time &now, Serra &serra) {
    logMessage(now, "Orario del comando: " + now.getTime(), 0);
    std::vector<std::string> tokens = commandParser(command);

    if (tokens.empty()) {
        throw std::invalid_argument("Errore: comando vuoto.");
    }

    const std::string &action = tokens[0];

    if (action == "set") {
        if (tokens.size() < 2) {
            throw std::invalid_argument("Errore: comando 'set' incompleto.");
        }

        const std::string &deviceName = tokens[1];

        if (deviceName == "time") {
            // Comando: set time HH:MM
            if (tokens.size() != 3) {
                throw std::invalid_argument("Errore: formato per 'set time' non valido. Usa: set time HH:MM");
            }
            Time time{tokens[2]};
            serra.AggiornaOrario(time);    // Simula avanzamento minuto per minuto
            logMessage(now, "Aggiornamento orario (minuto per minuto)", 0);
        } else {
            // Comando: set <device> on/off oppure programmazione oraria
            if (tokens.size() < 3) {
                throw std::invalid_argument("Errore: comando 'set' incompleto per dispositivo.");
            }

            const std::string &operation = tokens[2];

            Impianto *imp = serra.getImpianto(deviceName);
            if (!imp)
                throw std::invalid_argument("Errore: l'impianto non esiste!");

            if (operation == "on") {
                logMessage(now, imp->Accendi(now), 0);
            } else if (operation == "off") {
                logMessage(now, imp->Spegni(), 0);
            } else {
                // Comando con timer: set <device> HH:MM oppure HH:MM HH:MM
                Time start{operation};
                Automatico *autoImp = dynamic_cast<Automatico *>(imp);
                Manuale *manImp = dynamic_cast<Manuale *>(imp);
                if (!autoImp && !manImp)
                    throw std::invalid_argument(deviceName + " non supporta la programmazione temporale.");

                if (tokens.size() == 4) {
                    Time stop{tokens[3]};
                    if(autoImp) {
                        autoImp->SetTimerStop(stop);
                        autoImp->SetStart(start);
                    }
                    else if (manImp) {
                        manImp->SetStart(start);
                        manImp->SetStop(stop);
                    }
                    logMessage(
                        now, "Timer di " + deviceName + " impostati a: " + start.getTime() + " - " + stop.getTime(), 0);
                } else {
                    autoImp->SetStart(start);
                    logMessage(now, "Timer di accensione di " + deviceName + " impostato a: " + start.getTime(), 0);
                }
            }
        }
    } else if (action == "rm") {
        // Rimozione di un impianto tramite ID
        if (tokens.size() != 2) {
            throw std::invalid_argument("Errore: comando 'rm' non valido. Usa: rm ${DEVICENAME}");
        }
        try{
            const int &deviceID = std::stoi(tokens[1]);
            serra.RimuoviImpianto(deviceID);
        }
        catch(const std::invalid_argument&) {
            throw std::invalid_argument("Errore: ID inesistente");
        }
    } else if (action == "show") {
        // Visualizzazione stato globale o di un singolo impianto
        if (tokens.size() == 1) {
            std::istringstream stream(serra.StampaStato());
            std::string line;
            while (std::getline(stream, line)) {
                logMessage(now, line, 0);
            }
        } else if (tokens.size() == 2) {
            const std::string &deviceName = tokens[1];
            logMessage(now, serra.getImpianto(deviceName)->Stampa(), 0);
        } else {
            throw std::invalid_argument("Errore: comando 'show' non valido. Usa: show oppure show ${DEVICENAME}");
        }
    } else if (action == "reset") {
        // Gestione dei reset: orario, timer o entrambi
        if (tokens.size() != 2)
            throw std::invalid_argument("Errore: comando 'reset' non valido.");

        const std::string &resetType = tokens[1];
        if (resetType == "time") {
            serra.ResetTime();
            logMessage(now, "Tempo della serra resettato a 00:00", 0);
        } else if (resetType == "timers") {
            logMessage(now, serra.ResetAllTimers(), 0);
        } else if (resetType == "all") {
            logMessage(now, serra.ResetAllTimers(), 0);
            serra.ResetTime();
            logMessage(now, "Tempo della serra resettato a 00:00", 0);
        } else {
            throw std::invalid_argument(
                "Errore: opzione 'reset' non valida. Usa: reset time | reset timers | reset all");
        }
    } else if (action == "help") {
        // Stampa i comandi disponibili
        const std::string commands = R"(Comandi disponibili:
        set <NOME> on              - Accende l'impianto manuale
        set <NOME> off             - Spegne l'impianto manuale
        set <NOME> <START>         - Imposta l'orario di accensione di un impianto automatico
        set <NOME> <START> <STOP>  - Imposta accensione e spegnimento di impianti temporizzati (<STOP> in nell'automatico e' il timer)
        rm <ID>                    - Rimuove l'impianto
        show                       - Mostra lo stato e consumo di tutti gli impianti
        show <NOME>                - Mostra lo stato e i dettagli di un impianto
        set time <HH:MM>           - Imposta l'orario attuale della serra
        reset time                 - Resetta l'orario a [00:00] e spegne tutti gli impianti
        reset timers               - Rimuove tutti i timer mantenendo lo stato attuale
        reset all                  - Resetta orario, timer e spegne tutti gli impianti
        exit                       - Termina l'esecuzione
        help                       - Mostra tutti i comandi possibili
        )";
        logMessage(now, commands, 0);
    } else if(action == "exit") {
        // Chiude il programma e il file di log
        logMessage(now, "Uscita dal programma.", 0);
        closeFile();    // Forzare la chiusura file
        std::exit(EXIT_SUCCESS);    // Esecuzione terminata
    }else {
        throw std::invalid_argument("Errore: comando '" + action + "' non riconosciuto.");
    }
}

// Apre il file di log in modalità append (mantiene i messaggi precedenti)
void UserInterface::openFile() {
    if (!logFile.is_open()) {
        logFile.open(logFilePath, std::ios::app); //std::ios::app => append del testo
        if (!logFile)
            throw std::invalid_argument("Errore: logFile non valido.");
    }
}

// Inizializzazione variabili statiche
std::ofstream UserInterface::logFile;
std::string UserInterface::logFilePath = "../log/logFile.txt";

// Chiude il file di log, se aperto
void UserInterface::closeFile() {
    if (logFile.is_open())
        logFile.close();
}
