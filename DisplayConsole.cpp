//
// Created by Utilisateur on 02/06/2025.
//

#include "DisplayConsole.h"
#include "DisplayManager.h"
#include <iostream>

string DisplayConsole::takeInput() {
    string output;
    cin>>output;
    return output;
}



void DisplayConsole::output(string message) {
    cout << message << endl;
}
