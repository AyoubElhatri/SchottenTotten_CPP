#include "DisplayConsole.h"
#include <iostream>
string DisplayConsole::takeInput() {
    string output;
    cin>>output;
    return output;
}



void DisplayConsole::output(string message) {
    cout << message << endl;
}