#include <modbus.h>
#include <bitset>
#include <string>
#include "chargeController.h"


/**
 * Class for TriStar TS-45. 
 * Class for the Mppt solar charge controller.
 */
class tristar : public chargeController{
private:
    modbus_t *ctx;
    void clean_and_throw_error() const;

public:

    enum fault_t {
        EXTERNAL_SHORT=0,
        OVERCURRENT=1,
        FET_SHORT=2,
        SOFTWARE=3,
        HVD=4,
        TRISTAR_HOT=5,
        DIP_SWITCH_CHANGED=6,
        SETTING_EDIT=7,
        RESET=8,
        MISWIRE=9,
        RTS_SHORTED=10,
        RTS_DISCCONNECTED=11, 
    };

    /**
     * Tristar class constructor.
     * @param device "/dev/ttyUSB0" 
     */
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

    /**
     * Reports alarms identified by self diagnostics. Each bit corresponds to a specific alarm.
     */
    float getAlarmLo() const;

    /**
     * Reports faults identified by self diagnostics. Each bit corresponds to a specific fault.
     */
    std::bitset<16> getFault() const;
    void clearFaults() const;

    /**
     * Each bit in the bit-field corresponds to an individual DIP switch setting.
     */
    float getDipswitchPos() const;

    /**
     * Reports the mode in which the controller is running.
     * @return 0x00=charge, 0x01=load, 0x02=diversion, 0x03=lighting.
     */
    float getControlMode() const;

    /**
     * Reports the current software state.
     * @return  
     */
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
    /**
     *Time before entering float. 
     Defines the length of time in regulation before dropping down to the float stage. 
     @return seconds
     */
    float getTimeBeforeFloat() const;
    void setTimeBeforeFloat(uint16_t s);
    /**
     *Time before entering float due to low battery.
    If the battery voltage dropped too low during the previous night, this value allows the user to specify a
    longer period of time before entering float stage. 
     */
    float getTimeBeforeFloat_lb() const;
    void setTimeBeforeFloat_lb(uint16_t s);
    //EV_floatlb_trip

    /**
     * Voltage that cancels float.
    Specify the battery voltage that will cancel float for the next charge cycle.
     */
    float getCancelFloatVoltage() const;
    void setCancelFloatVoltage(float v);
    float getEqualizeVoltage() const;
    void setEqualizeVoltage(float v);
    int getDaysBetweenEq() const;

    /**
     * Specify the number of days between equalizations.
     * @param d number of days (0-255)
     */
    void setDaysBetweenEq(uint8_t d); 

    /**
     * Counter that indicates the number of days since the last equalization was administered to the batteries.
     */
    int getDaysLastEq() const;

    /**
     * Counter that indicates the number of days since the last equalization was administered to the batteries.
     * @param d number of days (0-255)
     */
    void setDaysLastEq(uint8_t d); 
    
    void setDiversionPWM();
    void setDiversionOnOff();

    
//Load mode
    virtual float getLowVoltageDisconnect() const override;
    virtual void setLowVoltageDisconnect(float v) override;
    virtual float getLowVoltageReconnect() const override;
    virtual void setLowVoltageReconnect(float v) override;
    //ER_icomp??
    
    /**
     * Defines the period of time to wait before disconnecting the loads, once battery voltage has dropped to
    the Low Voltage Disconnect setpoint.
    @return seconds
     */
    float getLVDwarningTimeout() const;
    
    /**
     * Defines the period of time to wait before disconnecting the loads, once battery voltage has dropped to
    the Low Voltage Disconnect setpoint.
    @param s seconds
     */
    void setLVDwarningTimeout(float s); 

    /**
     * /Disconnect the loads if the battery voltage rises too high.
     */
    float getLoadHVD() const; 
    void setLoadHVD(float v);

    /**
     * Setpoint at which the loads will reconnect after a high voltage condition.
     */
    float getLoadHVR() const; 
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
    
    /**
     * Specifies the number of days between battery service reminders. 
     * Sets an alarm, prompting the user to check his batteries for water, health, etc. 
     * Clear the alarm with the pushbutton, meter, or clearAlarms().
     */
    float getBattServiceInterval() const;
    /**
     * Specifies the number of days between battery service reminders. 
     * Sets an alarm, prompting the user to check his batteries for water, health, etc. 
     * Clear the alarm with the pushbutton, meter, or clearAlarms().
     * @param d number of days (0-255)
     */
    void setBattServiceInterval(uint8_t d);
    float getDaysLastBattService() const;

    /**
     * Reports the number of days since the last battery service reminder.
     * @return number of days 
     */
    float getKWH() const;

//Coils
    /**
     * Trigger manual equalize. Equalize will still timeout if not reset.
     */
    void equalize() const;
    void stopEqualize() const;
    /**
     * Force software into DISCONNECT state. Turns off MOSFETs and waits.
     */
    void disconnect() const;
    void reconnect() const;
    void clearAh_r() const;
    void clearAh() const;
    void clearKwH() const;
    void resetLastBattService() const;
    /**
     * Force the controller to update EEPROM with RAM values. 
     */
    void clearAlarms() const;
    void updateEprom() const;
    /**
     *Force the controller out of LVD in Load and Lighting mode. 
     If Vbatt is still below LVD the load will run for a length of time specified by setLVDwarningTimeout(float v), 
     then return to the LVD state. If Vbatt is above LVD, the load will remain connected. 
     */
    void LVDoverride() const;
    /**
     * Reset control will force a reboot of the processor software. Useful for clearing faults/alarms after
    settings changes, or firmware updates. 
     */
    void reset() const;

};