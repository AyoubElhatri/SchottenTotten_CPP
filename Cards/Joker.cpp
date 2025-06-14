

#include "Joker.h"
#include "../DisplayManager.h"


void Joker::getEvent(StoneTiles* stoneTiles) {
    DisplayManager::getInstance()->output("What's the number of the card you want to play?");
    unsigned int cardNumber = atoi(DisplayManager::getInstance()->takeInput().c_str());
    DisplayManager::getInstance()->output("What's the color of the card you want to play?");
    int colorInput = atoi(DisplayManager::getInstance()->takeInput().c_str());
    Colors cardColor = static_cast<Colors>(colorInput);
    setColor(cardColor);
    setNumber(cardNumber);
}
