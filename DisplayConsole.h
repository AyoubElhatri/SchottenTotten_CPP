//
// Created by Utilisateur on 02/06/2025.
//

#ifndef DISPLAYCONSOLE_H
#define DISPLAYCONSOLE_H
#include "Display.h"
using namespace std;
#include <string>

class DisplayConsole : public Display {
public:
    string takeInput(string message);
};



#endif //DISPLAYCONSOLE_H
