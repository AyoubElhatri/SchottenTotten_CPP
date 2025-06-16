#include "ShieldBear.h"

void ShieldBear::getEvent(StoneTiles* stoneTiles) {
    DisplayManager::getInstance()->output("What's the number of the card you want to play? (Only numbers 1, 2 or 3 are allowed)");
    try {
        unsigned int cardNumber = stoi(DisplayManager::getInstance()->takeInput());
        if (cardNumber!=1 && cardNumber!=2 && cardNumber!=3) {
            CustomException Exc02=CustomException(INVALIDNUMBERINPUT);
            throw(Exc02);
        }
        setNumber(cardNumber);
    }
    catch (...) {
        CustomException Exc1=CustomException(INVALIDNUMBERINPUT);//INVALIDNUMBERINPUT defined within CustomException class.
        throw(Exc1);
    }
    DisplayManager::getInstance()->output("What's the color of the card you want to play?");
    try {
        int colorInput = stoi(DisplayManager::getInstance()->takeInput());
        Colors cardColor = static_cast<Colors>(colorInput);
        setColor(cardColor);
    }
    catch (...) {
        CustomException Exc2=CustomException(INVALIDCOLORINPUT);
        throw(Exc2);
    }
}