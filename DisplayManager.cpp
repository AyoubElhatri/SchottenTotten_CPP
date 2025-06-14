
#include "DisplayManager.h"

#include <stdexcept>
using namespace std;
unique_ptr<Display> DisplayManager::DisplayInstance = nullptr;

Display *DisplayManager::getInstance() {
    if (DisplayInstance) {
        return DisplayInstance.get();
    }
    else {
        throw invalid_argument("Instance not created");
    }
}

