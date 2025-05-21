#include "../include/UserInterface.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

void UserInterface::logMessage(const Time &time, const std::string &message, const int &errorLevel) {
    if (errorLevel == 0)
        std::cout << "[" << time.getTime() << "]\t" << message << std::endl;
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


void UserInterface::processCommand(const std::string &command, const Time &now, Serra serra) {
    logMessage(now, "L'orario attuale è " + now.getTime(), 0);
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
        } else {
            if (tokens.size() < 3) {
                throw std::invalid_argument("Errore: comando 'set' incompleto per dispositivo.");
            }

            const std::string &operation = tokens[2];

            if (operation == "on") {
                //metodo per accendere il dispositivo {deviceName};
            } else if (operation == "off") {
                //metodo per spegnere il dispositivo {deviceName};
            } else {
                Time start{operation};
                if (tokens.size() == 4) {
                    Time stop{tokens[3]};
                    //metodo per settare il timer {start} e {stop} per il dispositivo {deviceName};
                } else {
                    //metodo per settare il timer {start} per il dispositivo {deviceName};
                }

            }
        }

    } else if (action == "rm") {
        if (tokens.size() != 2) {
            throw std::invalid_argument("Errore: comando 'rm' non valido. Usa: rm ${DEVICENAME}");
        }
        //metodo per rimuovere il timer
    } else if (action == "show") {
        if (tokens.size() == 1) {
        serra.StampaStato();
        } else if (tokens.size() == 2) {
            //metodo per mostrare impianto specifico
        } else {
            throw std::invalid_argument("Errore: comando 'show' non valido. Usa: show oppure show ${DEVICENAME}");
        }

    } else if (action == "reset") {
        if (tokens.size() != 2) {
            throw std::invalid_argument("Errore: comando 'reset' non valido.");
        }

        const std::string &resetType = tokens[1];
        if (resetType == "time") {
            serra.ResetTime();
        } else if (resetType == "timers") {
            //metodo per resettare i timer
        } else if (resetType == "all") {
            //metodo per resettare tempo e timer
        } else {
            throw std::invalid_argument(
                    "Errore: opzione 'reset' non valida. Usa: reset time | reset timers | reset all");
        }
    } else {
        throw std::invalid_argument("Errore: comando '" + action + "' non riconosciuto.");
    }
}