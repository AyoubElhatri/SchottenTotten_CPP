#include "Joker.h"
#include "../DisplayManager.h"

void Joker::getEvent(StoneTiles* stoneTiles) {
    DisplayManager::getInstance()->output("What's the number of the card you want to play?");
    try {
        unsigned int cardNumber = stoi(DisplayManager::getInstance()->takeInput());
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
