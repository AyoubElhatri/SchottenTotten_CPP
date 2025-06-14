

#ifndef DISPLAY_H
#define DISPLAY_H

using namespace std;
#include <string>

class Display {
public:
    virtual string takeInput() = 0;
    virtual void output(string message) = 0;
    virtual ~Display() = default;
};


#endif