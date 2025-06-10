#ifndef CARDS_H
#define CARDS_H



class Cards {
    public:
    virtual ~Cards() = default;

    virtual unsigned int getNumber() const = 0;
        virtual std::string getColor() const = 0;
        virtual void getEvent()=0;
};



#endif //CARDS_H
