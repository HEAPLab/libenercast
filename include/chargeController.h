#ifndef CHARGECONTROLLER_H
#define CHARGECONTROLLER_H
class chargeController
{
private:
    
public:
    virtual ~chargeController() {}
    virtual int getVolt() const = 0;
};

#endif