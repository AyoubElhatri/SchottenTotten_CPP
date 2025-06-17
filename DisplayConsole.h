

#ifndef DISPLAYCONSOLE_H
#define DISPLAYCONSOLE_H
#include "Display.h"
#include "DisplayManager.h"
using namespace std;
#include <string>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"


class DisplayConsole : public Display {
public:
     DisplayConsole() = default;

     virtual string takeInput();
     virtual void output(string message);

};



#endif