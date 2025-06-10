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
protected:
        Display * DisplayInstance=nullptr;
    public:

        virtual Display * getInstance();
        virtual string takeInput();
        virtual void output(string message);

};


#endif //DISPLAY_H
