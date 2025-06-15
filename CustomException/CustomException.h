//
// Created by atoum on 14/06/2025.
//

#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H

//All the defines in this particular class refer to the different Exceptions that are existant within this program
#define INVALIDNUMBERINPUT 11 //User enters a wrong number of card that stoi throws. Used in: Joker.cpp
#define INVALIDCOLORINPUT 12 //User enters a wrong color for a card that stoi throws. Used in: Joker.cpp


class CustomException {
private:
    unsigned int ExceptionValue;
public:
    CustomException(unsigned int ExParam){ExceptionValue=ExParam;}
    unsigned int getExceptionValue(){return ExceptionValue;}
    void setExceptionValue(unsigned int value){ExceptionValue = value;}
};



#endif //CUSTOMEXCEPTION_H
