

#ifndef DISPLAYCONSOLE_H
#define DISPLAYCONSOLE_H
#include "Display.h"
#include "DisplayManager.h"
using namespace std;
#include <string>


class DisplayConsole : public Display {
public:
     DisplayConsole() = default;

     virtual string takeInput();
     virtual void output(string message);

};



#endif