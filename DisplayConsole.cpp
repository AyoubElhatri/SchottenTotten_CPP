//
// Created by Utilisateur on 02/06/2025.
//

#include "DisplayConsole.h"
#include "Display.h"
#include <iostream>

string DisplayConsole::takeInput() {
    string output;
    cin>>output;
    return output;
}

Display * DisplayConsole::getInstance() {
    if (DisplayInstance==nullptr) {
        DisplayInstance= new DisplayConsole();

    }
    return DisplayInstance;
}
