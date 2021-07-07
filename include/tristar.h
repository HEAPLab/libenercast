#include <modbus.h>
#include <string>
#include "chargeController.h"


class tristar : public chargeController{
private:
    modbus_t *ctx;
    void clean_and_throw_error() const;

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
    
    float getAmpHour_r() const; //total amp-hours resetable
    float getAmpHour() const; //total amp-hours
    float getHourmeter() const;
    float getAlarmLo() const;
    float getFault() const;
    void clearFaults() const;
    float getDipswitchPos() const;
    float getControlMode() const;
    float getControlState() const; 

//Charge and diversion mode
    float getRegulationVoltage() const;
    virtual float getHighVoltageDisconnect() const override;
    virtual void setHighVoltageDisconnect(float v)  override;
    virtual float getHighVoltageReconnect() const override;
    virtual void setHighVoltageReconnect(float v)  override;
    float getRegulationVoltage_25() const;

    void setRegulationVoltage_25(float v);
    void setFloatVoltage(float v);
    float getFloatVoltage() const;
    float getTimeBeforeFloat() const;
    void setTimeBeforeFloat(unsigned short int s);
    float getTimeBeforeFloat_lb() const;
    void setTimeBeforeFloat_lb(unsigned short int s);
    //EV_floatlb_trip
    float getCancelFloatVoltage() const;
    void setCancelFloatVoltage(float v);
    float getEqualizeVoltage() const;
    void setEqualizeVoltage(float v);
    int getDaysBetweenEq() const;
    void setDaysBetweenEq(uint8_t d); // try unsigned char
    int getDaysLastEq() const;
    void setDaysLastEq(uint8_t d); // try unsigned char
    void setDiversionPWM();
    void setDiversionOnOff();

    
//Load mode
    virtual float getLowVoltageDisconnect() const override;
    virtual void setLowVoltageDisconnect(float v) override;
    virtual float getLowVoltageReconnect() const override;
    virtual void setLowVoltageReconnect(float v) override;
    //ER_icomp??
    virtual float getLVDwarningTimeout() const override;
    virtual void setLVDwarningTimeout(float v) override; 

    float getLoadHVD() const; //Disconnect the loads if the battery voltage rises too high.
    void setLoadHVD(float v);
    float getLoadHVR() const; //Setpoint at which the loads will reconnect after a high voltage condition.
    void setLoadHVR(float v);
    
//Common values
    virtual float maxBatteryVoltageToday() const override;
    virtual float minBatteryVoltageToday() const override;
    float getLedV_g_gy() const;
    void setLedV_g_gy(float v);
    float getLedV_gy_y() const;
    void setLedV_gy_y(float v);
    float getLedV_y_yr() const;
    void setLedV_y_yr(float v);
    float getLedV_yr_r() const;
    void setLedV_yr_r(float v);
    float getBattServiceInterval() const;
    void setBattServiceInterval(int d); // try unsigned char (0-255)
    float getDaysLastBattService() const;
    float getKWH() const;

//Coils
    void equalize() const;
    void stopEqualize() const;
    void disconnect() const;
    void reconnect() const;
    void clearAh_r() const;
    void clearAh() const;
    void clearKwH() const;
    void resetLastBattService() const;
    void clearAlarms() const;
    void updateEprom() const;
    void LVDoverride() const;
    void reset() const;

};