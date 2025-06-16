//
// Created by atoum on 14/06/2025.
//

#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H

//All the defines in this particular class refer to the different Exceptions that are existant within this program
#define NOEXCEPTIONINDICATED 0 //Used for the default constructor of this class, preferrably not to use. Used in: CustomException.h

#define INVALIDNUMBERINPUT 10 //User enters a wrong number of card that stoi throws. Used in: Joker.cpp, ShieldBear.cpp
#define INVALIDCOLORINPUT 11 //User enters a wrong color for a card that stoi throws. Used in: Joker.cpp, ShieldBear.cpp
#define INCOMPLETESET 20 //User asks to evaluateCombination while the set is not full. Used in: Set.cpp


class CustomException {
private:
    unsigned int ExceptionValue;
public:
    CustomException(){ExceptionValue=NOEXCEPTIONINDICATED;}
    CustomException(unsigned int ExParam){ExceptionValue=ExParam;}
    unsigned int getExceptionValue(){return ExceptionValue;}
    void setExceptionValue(unsigned int value){ExceptionValue = value;}
};



#endif //CUSTOMEXCEPTION_H
