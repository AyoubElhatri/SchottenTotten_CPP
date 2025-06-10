//
// Created by Utilisateur on 02/06/2025.
//

#ifndef DISPLAY_H
#define DISPLAY_H
#include <string>
using namespace std;

class Display {
    private:
        Display();

    public:

        virtual Display * getInstance();
        virtual string takeInput();

};


#endif //DISPLAY_H
