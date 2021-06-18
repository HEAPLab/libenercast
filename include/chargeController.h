#ifndef CHARGECONTROLLER_H
#define CHARGECONTROLLER_H
class chargeController
{
private:
    
public:
    virtual ~chargeController() {}
    virtual float getBatteryVoltage() const = 0; //A36
    virtual float getChargeCurrent() const = 0; 
    virtual float getLoadCurrent() const = 0; //A8
    virtual float getHeatsinkTemp() const = 0; // A12
    virtual float getBatteryTemp() const = 0; //A11
    virtual float getRegulationVoltage() const = 0;
    virtual float getAlarmLo() const = 0;
    virtual float getFault() const = 0;
    virtual float getControlMode() const = 0;
    //virtual float getLoadVoltage() const = 0; A7 - 11T
    //virtual float getLoadPower() const = 0; A9/A10
    //virtual float getBatterySoc() const = 0; A13
    //virtual float getBAtteryCurrent() const = 0; A37/A38




    virtual float getVoltageDisconnect() const =0;
    virtual void setVoltageDisconnect(float v) const =0;
    virtual float getVoltageReconnect() const =0;
    virtual void setVoltageReconnect(float v) const =0;
    virtual void clearFaults() const =0;

 };

#endif