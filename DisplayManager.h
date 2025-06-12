//
// Created by Utilisateur on 02/06/2025.
//

#ifndef DISPLAY_H
#define DISPLAY_H
#include <string>
class Display;
using namespace std;
#include "Display.h"
#include <memory>
class DisplayManager {
    private:
        DisplayManager();
    public:
        static  unique_ptr<Display>DisplayInstance;
        template <class TDisplay> static void createInstance();
        static Display *getInstance();

};
unique_ptr<Display> DisplayManager::DisplayInstance = nullptr;

#endif //DISPLAY_H
