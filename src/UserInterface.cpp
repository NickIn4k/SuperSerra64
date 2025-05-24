#include "UserInterface.h"
#include "Automatico.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

void UserInterface::logMessage(const Time &time, const std::string &message, const int &errorLevel) {
    openFile();
    if (errorLevel == 0) {
        std::string msg = "[" + time.getTime() + "]\t" + message + "\n";
        std::cout << msg;

        if (logFile.is_open())
            logFile << msg << std::endl;
    }
    else if (errorLevel == 1)
        std::cerr << "[" << time.getTime() << "]\t" << message << std::endl;
}

std::vector<std::string> UserInterface::commandParser(const std::string &command) {
    std::vector<std::string> tokens;
    std::istringstream ss(command);
    std::string token;

    bool isDeviceName = false;
    std::string deviceName;

    while (ss >> token) {
        if (isDeviceName) {
            if (token == "on" || token == "off" || token.find(':') != std::string::npos) {
                if (!deviceName.empty()) {
                    tokens.push_back(deviceName);
                    deviceName.clear();
                }
                isDeviceName = false;
            }
        }

        if (token == "set" || token == "rm" || token == "show") {
            tokens.push_back(token);
            isDeviceName = true;
            continue;
        }

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


void UserInterface::processCommand(const std::string &command, const Time &now, Serra &serra) {
    logMessage(now, "L'orario attuale e' " + now.getTime(), 0);
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
            if (tokens.size() != 3) {
                throw std::invalid_argument("Errore: formato per 'set time' non valido. Usa: set time HH:MM");
            }
            Time time{tokens[2]};
            serra.AggiornaOrario(time);
            logMessage(now, "Aggiornamento orario (minuto per minuto)", 0);
        } else {
            if (tokens.size() < 3) {
                throw std::invalid_argument("Errore: comando 'set' incompleto per dispositivo.");
            }

            const std::string &operation = tokens[2];

            Impianto* imp = serra.getImpianto(deviceName);
            if(!imp)
                throw std::invalid_argument("Errore: l'impianto non esiste!");

            if (operation == "on") {
                logMessage(now, imp->Accendi(now), 0);
            } else if (operation == "off") {
                logMessage(now, imp->Spegni(),0);
            } else {
                Time start{operation};
                Automatico* autoImp = dynamic_cast<Automatico*>(imp);
                if (!autoImp)
                    throw std::invalid_argument(deviceName + " non supporta la programmazione temporale.");

                if (tokens.size() == 4) {
                    Time stop{tokens[3]};
                    autoImp->SetStop(stop);
                    autoImp->SetStart(start);
                    logMessage(now, "Timer di "+ deviceName + " impostati a: "+ start.getTime()+" - " + stop.getTime(), 0);
                } else {
                    autoImp->SetStart(start);
                    logMessage(now, "Timer di accensione di "+ deviceName + " impostato a: "+ start.getTime(), 0);
                }
            }
        }

    } else if (action == "rm") {
        if (tokens.size() != 2) {
            throw std::invalid_argument("Errore: comando 'rm' non valido. Usa: rm ${DEVICENAME}");
        }
        //metodo per rimuovere il timer => Nella consegna non è spiegato.
    } else if (action == "show") {
        if (tokens.size() == 1) {
        logMessage(now, serra.StampaStato(), 0);
        } else if (tokens.size() == 2) {
            const std::string &deviceName = tokens[1];
            logMessage(now, serra.getImpianto(deviceName)->Stampa(), 0);
        } else {
            throw std::invalid_argument("Errore: comando 'show' non valido. Usa: show oppure show ${DEVICENAME}");
        }

    } else if (action == "reset") {
        if (tokens.size() != 2)
            throw std::invalid_argument("Errore: comando 'reset' non valido.");

        const std::string &resetType = tokens[1];
        if (resetType == "time") {
            serra.ResetTime();
            logMessage(now, "Tempo della serra resettato a 00:00", 0);
        } else if (resetType == "timers") {
            logMessage(now,serra.ResetAllTimers(),0);
        } else if (resetType == "all") {
            logMessage(now,serra.ResetAllTimers(),0);
            serra.ResetTime();
            logMessage(now, "Tempo della serra resettato a 00:00", 0);
        } else {
            throw std::invalid_argument(
                    "Errore: opzione 'reset' non valida. Usa: reset time | reset timers | reset all");
        }
    } else {
        throw std::invalid_argument("Errore: comando '" + action + "' non riconosciuto.");
    }
}

void UserInterface::openFile() {
    if (!logFile.is_open()) {
        logFile.open(logFilePath, std::ios::app); //std::ios::app => append del testo
        if (!logFile)
             throw std::invalid_argument("Errore: logFile non valido.");
    }
}

std::ofstream UserInterface::logFile;
std::string UserInterface::logFilePath = "../log/logFile.txt";

void UserInterface::closeFile() {
    if (logFile.is_open())
        logFile.close();
}