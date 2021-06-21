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
    virtual float getChargeCurrent() const override;
    virtual float getLoadCurrent() const override;
    virtual float getControlMode() const override;
    virtual float getHeatsinkTemp() const override;
    virtual float getBatteryTemp() const override;
    virtual float getRegulationVoltage() const override;
    virtual float getAlarmLo() const override;
    virtual float getFault() const override;

    virtual float getVoltageDisconnect() const override;
    virtual void setVoltageDisconnect(float v) const override;
    virtual float getVoltageReconnect() const override;
    virtual void setVoltageReconnect(float v) const override;
    virtual void clearFaults() const override;
    virtual float getLoadVoltage() const override;
    virtual float getLoadPower() const override;
    virtual float getLoadStatus() const override; 
    virtual float getArrayVoltage() const override;
    virtual float getArrayPower() const override;
    virtual float getArrayStatus() const override;
    virtual float deviceStatus() const override; 




};