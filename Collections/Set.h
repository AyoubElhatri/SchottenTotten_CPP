//
// Created by atoum on 03/06/2025.
//

#ifndef SET_H
#define SET_H
#include <vector>
#include <algorithm>
#include <memory>
#include "../Cards/Cards.h"
using namespace std;

class Set {
 public:
  vector<unique_ptr<Cards>> SetOfCards;
};



#endif //SET_H
