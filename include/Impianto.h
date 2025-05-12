//Qui vanno dichiarati i metodi e le costanti
#ifndef IMPIANTO_H
#define IMPIANTO_H
#include <string>
class Impianto {
private:
    int ID;


public:
    Impianto();
    int getID();
    std::string getName();
};
#endif //IMPIANTO_H


//spegni è virtuale