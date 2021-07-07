#include <modbus.h>
#include <string>
#include "chargeController.h"


class epever : public chargeController{
private:
    modbus_t *ctx;
public:
    epever(const std::string & device);
    virtual ~epever();
    virtual float getBatteryVoltage() const override;
    virtual float getChargeCurrent() const override;
    virtual float getLoadCurrent() const override;
    virtual float getHeatsinkTemp() const override;
    virtual float getBatteryTemp() const override;
    virtual float getHighVoltageDisconnect() const override;
    virtual void setHighVoltageDisconnect(float v)  override;
    virtual float getHighVoltageReconnect() const override;
    virtual void setHighVoltageReconnect(float v)  override;
    virtual float getLoadVoltage() const override;
    virtual float maxBatteryVoltageToday() const override;
    virtual float minBatteryVoltageToday() const override;
    virtual float getArrayVoltage() const override;

    //fare
    virtual float getLowVoltageDisconnect() const override;
    virtual void setLowVoltageDisconnect(float v)  override;
    virtual float getLowVoltageReconnect() const override;
    virtual void setLowVoltageReconnect(float v)  override;
    virtual float getLVDwarningTimeout() const override;
    virtual void setLVDwarningTimeout(float v) override; 


    float getLoadPower() const;
    float getLoadStatus() const; 
    float getArrayPower() const;
    float getArrayStatus() const;
    float deviceStatus() const;
    void chargingDeviceOn() const;
    void chargingDeviceOff() const;

    
    






};