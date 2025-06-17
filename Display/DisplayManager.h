#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H
#include <memory>
#include "Display.h"

class DisplayManager {
    private:
        DisplayManager();
    public:
        static std::unique_ptr<Display> DisplayInstance;
    template <class TDisplay> static void createInstance() {
        DisplayInstance = std::make_unique<TDisplay>();
    };
    static Display* getInstance();
};




#endif