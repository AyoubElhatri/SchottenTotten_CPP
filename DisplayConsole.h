//
// Created by Utilisateur on 02/06/2025.
//

#ifndef DISPLAYCONSOLE_H
#define DISPLAYCONSOLE_H
#include "Display.h"
#include "DisplayManager.h"
using namespace std;
#include <string>


class DisplayConsole : public Display {
private:
     DisplayConsole();
public:
     virtual string takeInput();
     virtual void output(string message);

};



#endif //DISPLAYCONSOLE_H
