#ifndef COMBINATIONTYPE_H
#define COMBINATIONTYPE_H

enum CombinationType{
    ColorRun = 5,//A run with the cards having the same color.
    nOfAKind = 4,//Cards of the same number but different colors.
    Color = 3,
    Run = 2,
    Sum = 1,
    None
  };



#endif //COMBINATIONTYPE_H
