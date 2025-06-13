#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H
#include <string>
#include <memory>
#include "Display.h" // Inclure la définition complète de Display

class DisplayManager {
    private:
        DisplayManager();
    public:
        static std::unique_ptr<Display> DisplayInstance;
        template <class TDisplay> static void createInstance();
        static Display* getInstance();
};

#endif