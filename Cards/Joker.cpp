#include "Joker.h"


void Joker::getEvent(StoneTiles* stoneTiles) {
    DisplayManager::getInstance()->output("What's the number of the card you want to play?");
    try {
        unsigned int cardNumber = stoi(DisplayManager::getInstance()->takeInput());
        setNumber(cardNumber);
    }
    catch (...) {
        throw(invalid_argument("Invalid number input. Please choose a correct number."));
    }
    DisplayManager::getInstance()->output("What's the color of the Joker you want to play? (red, green...)");
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
