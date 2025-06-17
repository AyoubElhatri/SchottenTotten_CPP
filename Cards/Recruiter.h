//
// Created by El hatri ayoub on 14/06/2025.
//

#ifndef RECRUITER_H
#define RECRUITER_H
#include <iostream>
#include <ostream>
#include "RusesCards.h"
using namespace std;

class Recruiter : public RusesCards {
public:
    Recruiter(){cardName = "Recruiter";};
    void getEvent(StoneTiles* stoneTiles);
};





#endif //RECRUITER_H
