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
    virtual float getHighVoltageDisconnect() const =0;
    virtual void setHighVoltageDisconnect(float v) const =0;
    virtual float getHighVoltageReconnect() const =0;
    virtual void setHighVoltageReconnect(float v) const =0;
    virtual void clearFaults() const =0;
    
    virtual float getHourmeter() const =0;
    virtual float getAmpHour_r() const =0; //total amp-hours resetable
    virtual float getAmpHour() const = 0; //total amp-hours
    virtual float getControlState() const =0; 
    virtual float getDipswitchPos() const =0;
    virtual float getLowVoltageDisconnect() const =0;
    virtual void setLowVoltageDisconnect(float v) const =0;
    virtual float getLowVoltageReconnect() const =0;
    virtual void setLowVoltageReconnect(float v) const =0;
    virtual float getLVDwarningTimeout() const =0;
    virtual void setLVDwarningTimeout(float v) const =0;
    virtual float getLedV_g_gy() const =0;
    virtual void setLedV_g_gy(float v) const =0;
    virtual float getLedV_gy_y() const =0;
    virtual void setLedV_gy_y(float v) const =0;
    virtual float getLedV_y_yr() const =0;
    virtual void setLedV_y_yr(float v) const =0;
    virtual float getLedV_yr_r() const =0;
    virtual void setLedV_yr_r(float v) const =0; 


    /*//Tristar ex
    virtual float getRegulationVoltage() const = 0;
    virtual void setRegulationVoltage() const = 0;
    virtual void setFloatVoltage() const = 0;
    virtual float getFloatVoltage() const = 0;
    virtual float getTimeBeforeFloat() const = 0;
    virtual void setTimeBeforeFloat() const = 0;
    virtual float getTimeBeforeFloat_lb() const = 0;
    virtual void setTimeBeforeFloat_lb() const = 0;
    //EV_floatlb_trip
    virtual float getCancelFloatVoltage() const =0;
    virtual void setCancelFloatVoltaget() const=0;
    virtual float getEqualizeVoltage() const =0;
    virtual void setEqualizeVoltage() const =0;
    virtual int getDaysBetweenEq() const = 0;
    virtual void setDaysBetweenEq() const =0;
    virtual int getDaysLastEq() const = 0;
    virtual void setDaysLastEq() const =0;
    */


    
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
    //Device time (9013  min, sec)(9014  day, hour)(9015 year, month)
    virtual void chargingDeviceOn() const = 0;
    virtual void chargingDeviceOff() const = 0;

    //--Load parameters

    //--Battery parameters

    


 };

#endif