//
// Created by Utilisateur on 12/06/2025.
//

#ifndef DISPLAY_H
#define DISPLAY_H

using namespace std;
#include <string>

class Display {
private:
    Display();
public:
    virtual string takeInput();
    virtual void output(string message);
};


#endif //DISPLAY_H
