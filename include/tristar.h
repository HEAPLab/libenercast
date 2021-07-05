#include <modbus.h>
#include <string>
#include "chargeController.h"


class tristar : public chargeController{
private:
    modbus_t *ctx;
public:
    tristar(const std::string & device);
    virtual ~tristar();
    virtual float getBatteryVoltage() const override;
    virtual float getLoadVoltage() const override;
    virtual float getArrayVoltage() const override;
    virtual float getChargeCurrent() const override;
    virtual float getLoadCurrent() const override;
    virtual float getHeatsinkTemp() const override;
    virtual float getBatteryTemp() const override;
    virtual float getAmpHour_r() const override; //total amp-hours resetable
    virtual float getAmpHour() const override; //total amp-hours
    virtual float getHourmeter() const override;
    virtual float getAlarmLo() const override;
    virtual float getFault() const override;
    virtual void clearFaults() const override;
    virtual float getDipswitchPos() const override;
    virtual float getControlMode() const override;
    virtual float getControlState() const override; 

//Charge and diversion mode
    virtual float getRegulationVoltage() const override;
    virtual float getHighVoltageDisconnect() const override;
    virtual void setHighVoltageDisconnect(float v) const override;
    virtual float getHighVoltageReconnect() const override;
    virtual void setHighVoltageReconnect(float v) const override;
    /*
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
    
//Load mode
    virtual float getLowVoltageDisconnect() const override;
    virtual void setLowVoltageDisconnect(float v) const override;
    virtual float getLowVoltageReconnect() const override;
    virtual void setLowVoltageReconnect(float v) const override;
    //ER_icomp??
    virtual float getLVDwarningTimeout() const override;
    virtual void setLVDwarningTimeout(float v) const override; 
    
//Common values
    virtual float maxBatteryVoltageToday() const override;
    virtual float minBatteryVoltageToday() const override;
    virtual float getLedV_g_gy() const override;
    virtual void setLedV_g_gy(float v) const override;
    virtual float getLedV_gy_y() const override;
    virtual void setLedV_gy_y(float v) const override;
    virtual float getLedV_y_yr() const override;
    virtual void setLedV_y_yr(float v) const override;
    virtual float getLedV_yr_r() const override;
    virtual void setLedV_yr_r(float v) const override;

  
    virtual float getLoadPower() const override;
    virtual float getLoadStatus() const override; 
    virtual float getArrayPower() const override;
    virtual float getArrayStatus() const override;
    virtual float deviceStatus() const override; 
    virtual void chargingDeviceOn() const override;
    virtual void chargingDeviceOff() const override;






};