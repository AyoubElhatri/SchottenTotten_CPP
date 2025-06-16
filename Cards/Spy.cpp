#include "Spy.h"
#include <iostream>
using namespace std;
#include "../DisplayManager.h"
void Spy::getEvent(StoneTiles* stoneTiles) {
    DisplayManager::getInstance()->output("What's the color of the card you want to play?");
    try {
        int colorInput = stoi(DisplayManager::getInstance()->takeInput());
        Colors cardColor = static_cast<Colors>(colorInput);
        setColor(cardColor);
    }
    catch (...) {
        CustomException Exc01=CustomException(INVALIDCOLORINPUT);
        throw(Exc01);
    }


}