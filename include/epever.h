#include <modbus.h>
#include <string>
#include "chargeController.h"


class epever : public chargeController{
private:
    modbus_t *ctx;
    void clean_and_throw_error() const;
public:
    epever(const std::string & device);
    virtual ~epever();

    //Real time data
    virtual float getArrayCurrent() const;
    virtual float getArrayVoltage() const override;
    float getArrayPower() const;
    float getArrayStatus() const;
    virtual float getBatteryVoltage() const override;
    virtual float getChargeCurrent() const override;
    virtual float maxBatteryVoltageToday() const override;
    virtual float minBatteryVoltageToday() const override;
    virtual float getBatteryTemp() const override;
    virtual float getBatterySOC() const; 
    virtual float getBateryStatus() const;
    virtual float getChargingStatus() const;
    virtual float getLoadCurrent() const override;
    virtual float getLoadVoltage() const override;
    float getLoadPower() const;
    float getLoadStatus() const; 
    virtual float getHeatsinkTemp() const override;
    float deviceStatus() const;
    // ? realTimeClock() const;

    //Battery Parameters
    virtual float getHighVoltageDisconnect() const override;
    virtual void setHighVoltageDisconnect(float v)  override;
    virtual float getHighVoltageReconnect() const override;
    virtual void setHighVoltageReconnect(float v)  override;
    virtual float getLowVoltageDisconnect() const override;
    virtual void setLowVoltageDisconnect(float v)  override;
    virtual float getLowVoltageReconnect() const override;
    virtual void setLowVoltageReconnect(float v)  override;    
    virtual float getLVDwarningTimeout() const override; //
    virtual void setLVDwarningTimeout(float v) override; //
    float getBatteryCapacity() const;
    void setBatteryCapacity(float ah);
    float getEqualizeChargingV() const;
    void setEqualizeChargingV(float v);
    float getBoostChargingV() const;
    void setBoostChargingV(float v);
    float getFloatChargingV() const;
    void setFloatChargingV(float v);
    float getBoostReconnectCahargingV() const;
    void setBoostReconnectCahargingV(float v);
    float getDischargingLimitV() const;
    void setDischargingLimitV(float v);
    float getChargingLimitV() const;
    void setChargingLimitV(float v);
    float getBoosDuration() const;
    void setBoosDuration(int min);
    float getEquilibriumDuration() const;
    void setEquilibriumDuration(int min);

    //Laod Parameters

    //Device Paraameters
    float getBatteryUpTempLimit() const;
    float getBatteryLwTempLimit() const;
    float getDeviceOverTemp() const;
    float getDeviceRecoveryTemp() const;
    void setBatteryUpTempLimit(float deg);
    void setBatteryLwTempLimit(float deg);
    void setDeviceOverTemp(float deg);
    void setDeviceRecoveryTemp(float deg);

    //switching values
    void chargingDeviceOn() const;
    void chargingDeviceOff() const;
    void LoadOn();
    void loadOff();
    void RestoreSystemDefaults();
    void loadTestModeOn();
    void loadTestModeOff();




    
    






};