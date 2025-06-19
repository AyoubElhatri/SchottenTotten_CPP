#include "ShieldBear.h"

void ShieldBear::getEvent(StoneTiles* stoneTiles) {
    DisplayManager::getInstance()->output("What's the number of the ShieldBearer you want to play? (Only numbers 1, 2 or 3 are allowed)");
    try {
        unsigned int cardNumber = stoi(DisplayManager::getInstance()->takeInput());
        if (cardNumber!=1 && cardNumber!=2 && cardNumber!=3) {
            throw(invalid_argument("Invalid card number"));
        }
        setNumber(cardNumber);
    }
    catch (...) {
        throw(invalid_argument("Invalid number input. Please choose a correct number."));
    }
    DisplayManager::getInstance()->output("What's the color of the ShieldBearer you want to play?");
    try {
        string strcolorInput = DisplayManager::getInstance()->takeInput();
        int colorInput=makeColor(strcolorInput);
        Colors cardColor = static_cast<Colors>(colorInput);
        setColor(cardColor);
    }
    catch (...) {
        throw invalid_argument("Invalid input for color.");
    }
}