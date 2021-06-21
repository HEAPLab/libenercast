#ifndef CHARGECONTROLLER_H
#define CHARGECONTROLLER_H
class chargeController
{
private:
    
public:
    virtual ~chargeController() {}
    virtual float getRegulationVoltage() const = 0;
    virtual float getAlarmLo() const = 0;
    virtual float getFault() const = 0;
    virtual float getControlMode() const = 0;
    virtual float getVoltageDisconnect() const =0;
    virtual void setVoltageDisconnect(float v) const =0;
    virtual float getVoltageReconnect() const =0;
    virtual void setVoltageReconnect(float v) const =0;
    virtual void clearFaults() const =0;

    
    //--Array information
    //Array current
    virtual float getChargeCurrent() const = 0; 
    //Array Voltage
    virtual float getArrayVoltage() const = 0;
    //Array Power
    virtual float getArrayPower() const = 0;
    //Array Status
    virtual float getArrayStatus() const = 0;
    
    //--Battery information
    //Battery Voltage
    virtual float getBatteryVoltage() const = 0; //A36
    //Max Voltage Today
    //Min Voltage today
    //Battery Temperature
    virtual float getBatteryTemp() const = 0; //A11
    //Battery SOC
    //virtual float getBatterySoc() const = 0; A13
    //Charging status
    //Battery Status


    //--Load information
    //Load Current
    virtual float getLoadCurrent() const = 0; //A8
    //Load Voltage
    virtual float getLoadVoltage() const = 0; 
    //Load Power
    virtual float getLoadPower() const = 0;
    //Load Status
    virtual float getLoadStatus() const = 0; 


    // --Controller Information
    // Device Temperature
    virtual float getHeatsinkTemp() const = 0; // A12
    // Device status
    virtual float deviceStatus() const = 0;
    // Real time clock
    // virtual float getDeviceTime const = 0; 0x9013-9015
    // virtual void setDeviceTime const = 0; 0x9013-9015
    // Battery upper temperature limit (9017)
    // Battery lower temperature limit (9018)
    // Device over temperature (9019)
    // Device recovery temperature (9063)

    //--Load parameters

    //--Battery parameters

    


 };

#endif