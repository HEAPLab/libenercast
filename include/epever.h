#include <modbus.h>
#include <string>
#include "chargeController.h"

/**
 * Epever class. 
 * Class for the Mppt solar charge controller.
 */
class epever : public chargeController{
private:
    modbus_t *ctx;
    void clean_and_throw_error() const;
public:

    /**
     * Epever class constructor.
     * @param device "/dev/ttyXRUSB0" 
     */
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
    
    /**
     * The percentage of battery's remaining capacity.
     */
    float getBatterySOC() const; 
    float getBateryStatus() const;
    float getChargingStatus() const;
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
    
    /**
     * @param min minutes
     */
    void setBoosDuration(int min);
    float getEquilibriumDuration() const;
    
    /**
     * @param min minutes
     */
    void setEquilibriumDuration(int min);

    //Laod Parameters

    //Device Paraameters
    float getBatteryUpTempLimit() const;
    float getBatteryLwTempLimit() const;
    float getDeviceOverTemp() const;
    float getDeviceRecoveryTemp() const;
    
    /**
     * @param deg degrees °C
     */
    void setBatteryUpTempLimit(float deg);
   
    /**
     * @param deg degrees °C
     */
    void setBatteryLwTempLimit(float deg);
    
    /**
     * @param deg degrees °C
     */
    void setDeviceOverTemp(float deg);
    
    /**
     * @param deg degrees °C
     */
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