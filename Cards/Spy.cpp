#include "Spy.h"
#include <iostream>
using namespace std;
#include "../Display/DisplayManager.h"
void Spy::getEvent(StoneTiles* stoneTiles) {
    DisplayManager::getInstance()->output("What's the color of the Spy you want to play?");
    try {
        string strcolorInput = DisplayManager::getInstance()->takeInput();
        int colorInput=getColor(strcolorInput);
        Colors cardColor = static_cast<Colors>(colorInput);
        setColor(cardColor);
    }
    catch (...) {
        throw invalid_argument("Invalid input for color.");
    }


}