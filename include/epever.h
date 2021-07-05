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
    virtual float getControlMode() const override;
    virtual float getHeatsinkTemp() const override;
    virtual float getBatteryTemp() const override;
    virtual float getRegulationVoltage() const override;
    virtual float getAlarmLo() const override;
    virtual float getFault() const override;

    virtual float getHighVoltageDisconnect() const override;
    virtual void setHighVoltageDisconnect(float v) const override;
    virtual float getHighVoltageReconnect() const override;
    virtual void setHighVoltageReconnect(float v) const override;
    virtual void clearFaults() const override;
    virtual float getLoadVoltage() const override;
    virtual float getLoadPower() const override;
    virtual float getLoadStatus() const override; 
    virtual float getArrayVoltage() const override;
    virtual float getArrayPower() const override;
    virtual float getArrayStatus() const override;
    virtual float deviceStatus() const override;
    virtual void chargingDeviceOn() const override;
    virtual void chargingDeviceOff() const override;
    virtual float maxBatteryVoltageToday() const override;
    virtual float minBatteryVoltageToday() const override;






};