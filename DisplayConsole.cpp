//
// Created by Utilisateur on 02/06/2025.
//

#include "DisplayConsole.h"

#include <iostream>

string DisplayConsole::takeInput(const string &message) {
    string output;
    cout << message << endl;
    cin>>output;
    return output;
}