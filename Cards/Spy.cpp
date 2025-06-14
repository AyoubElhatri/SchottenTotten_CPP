#include "Spy.h"
#include <iostream>
using namespace std;
#include "../DisplayManager.h"
void Spy::getEvent(StoneTiles* stoneTiles) {
    DisplayManager::getInstance()->output("What's the color of the card you want to play?");
    int colorInput = atoi(DisplayManager::getInstance()->takeInput().c_str());
    Colors cardColor = static_cast<Colors>(colorInput);
    setColor(cardColor);


}