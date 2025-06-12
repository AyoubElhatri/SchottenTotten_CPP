//
// Created by Utilisateur on 10/06/2025.
//

#include "Joker.h"
#include "../DisplayManager.h"


void Joker::getEvent() {
    Display *display = nullptr;
    display=display->getInstance();

    display->output("Choose the value of the Joker");
    int value = atoi(display->takeInput());


}
