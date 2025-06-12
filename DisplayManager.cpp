/*

#include "DisplayManager.h"
#include "Display.h"

#include <stdexcept>
using namespace std;

Display *DisplayManager::getInstance() {
    if (DisplayInstance) {
        return DisplayInstance.get();
    }
    else {
        throw invalid_argument("Instance not created");
    }
}

template <class TDisplay> static void createInstance() {
    DisplayManager::DisplayInstance = make_unique<TDisplay>();
};*/
