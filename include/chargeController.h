#ifndef CHARGECONTROLLER_H
#define CHARGECONTROLLER_H
class chargeController
{
private:
    
public:
    virtual ~chargeController() {}
    virtual float getHighVoltageDisconnect() const =0;
    virtual void setHighVoltageDisconnect(float v) =0;
    virtual float getHighVoltageReconnect() const =0;
    virtual void setHighVoltageReconnect(float v)  =0;
    
    virtual float getLowVoltageDisconnect() const =0;
    virtual void setLowVoltageDisconnect(float v) =0;
    virtual float getLowVoltageReconnect() const =0;
    virtual void setLowVoltageReconnect(float v) =0;
    virtual float getLVDwarningTimeout() const =0;
    virtual void setLVDwarningTimeout(float v) =0;
    
    //--Array information
    virtual float getChargeCurrent() const = 0; 
    virtual float getArrayVoltage() const = 0;
    //virtual float getArrayPower() const = 0;
    //virtual float getArrayStatus() const = 0;
    
    //--Battery information
    //Battery Voltage
    virtual float getBatteryVoltage() const = 0; //A36
    //Max Voltage Today
    virtual float maxBatteryVoltageToday() const = 0;
    //Min Voltage today
    virtual float minBatteryVoltageToday() const = 0;    
    //Battery Temperature
    virtual float getBatteryTemp() const = 0; //A11
    //Battery SOC
    //virtual float getBatterySoc() const = 0; A13
    //Charging status
    //Battery Status


    //--Load information
    virtual float getLoadCurrent() const = 0; //A8
    virtual float getLoadVoltage() const = 0; 
    //virtual float getLoadPower() const = 0;
    //virtual float getLoadStatus() const = 0; 


    // --Controller Information
    // Device Temperature
    virtual float getHeatsinkTemp() const = 0; // A12
    
    //--Load parameters

    //--Battery parameters

    //Coils
    /*virtual void equalize() const =0;
    virtual void stopEqualize() const =0;
    virtual void disconnect() const =0;
    virtual void reconnect() const =0;
    virtual void clearAh_r() const =0;
    virtual void clearAh() const =0;
    virtual void clearKwH() const =0;
    virtual void resetLastBattService() const =0;
    virtual void clearAlarms() const =0;
    virtual void updateEprom() const =0;
    virtual void LVDoverride() const =0;
    virtual void reset() const =0;*/

        


 };

#endif