#include "chargeController.h"
#include "tristar.h"
#include "epever.h"
#include <iostream>
int main(int argc, char const *argv[])
{
       std::cout<<"Tristar:"<<std::endl;
    tristar *device = new tristar("/dev/ttyUSB0");
    
    float battVoltage = device->getBatteryVoltage();
    std::cout<<"Battery Voltage: "<<battVoltage<<std::endl;

    /*float hourmeter = device->getHourmeter();
    std::cout<<"hourmeter: "<<hourmeter<<std::endl;

    float solarCurrent = device->getChargeCurrent();
    std::cout<<"charge/solar current: " <<solarCurrent<<std::endl;

    float loadCurrent = device->getLoadCurrent();
    std::cout<<"Load current: "<<loadCurrent<<std::endl;

    int heatsinkTemp = device->getHeatsinkTemp();
    std::cout<<"heatsink temp: "<<heatsinkTemp<<std::endl;

    int batteryTemp = device->getBatteryTemp();
    std::cout<<"battery temperature: "<<batteryTemp<<std::endl;

    int regulationVoltage = device->getRegulationVoltage();
    std::cout<<"Regulation/Target voltage: "<<regulationVoltage<<std::endl;

    int fault = device->getFault();
    std::cout<<"fault: "<<fault<<std::endl;

    int alarm = device->getAlarmLo();
    std::cout<<"alarm: "<<alarm<<std::endl;

    float voltageDisconnect = device->getHighVoltageDisconnect();
    std::cout<<"voltage disconnect: "<<voltageDisconnect<<std::endl; 
    
    float voltageRec = device->getHighVoltageReconnect();
    std::cout<<"voltage reconnect: "<<voltageRec<<std::endl;

    device->setHighVoltageReconnect(13.008);

    voltageRec = device->getHighVoltageReconnect();
    std::cout<<"voltage reconnect: "<<voltageRec<<std::endl;

    float minBatteryV = device->minBatteryVoltageToday();
    std::cout<<"Min Battery Today: "<<minBatteryV<<std::endl;
    
    float maxBatteryV = device->maxBatteryVoltageToday();
    std::cout<<"Max Battery Voltage Today : "<<maxBatteryV<<std::endl;

    device->clearFaults();
    int fault = device->getFault();
    std::cout<<"fault: "<<fault<<std::endl;

    float controlMode = device->getControlMode();
    std::cout<<"control mode: "<<controlMode<<std::endl; 


    float controlState = device->getControlState();
    std::cout<<"control State: "<<controlState<<std::endl;
    
    device->disconnect(); 
    std::cout<<"disconnected"<<std::endl;

    battVoltage = device->getBatteryVoltage();
    std::cout<<"battery Voltage Tristar: "<<battVoltage<<std::endl;
    controlState = device->getControlState();
    std::cout<<"control State: "<<controlState<<std::endl;
    
    device->reconnect();
    std::cout<<"reconnected"<<std::endl;

    controlState = device->getControlState();
    std::cout<<"control State: "<<controlState<<std::endl;*/
    
    
    //-----epever
    std::cout<<std::endl;
    std::cout<<"Epever:"<<std::endl;

    chargeController *deviceE = new epever("/dev/ttyXRUSB0");

    float battVoltageE = deviceE->getBatteryVoltage();
    std::cout<<"Battery Voltage: "<<battVoltageE<<std::endl;

    float loadCurrentE = deviceE->getLoadCurrent();
    std::cout<<"Load current: "<<loadCurrentE<<std::endl;

    std::cout<<"Max battery voltage today: "<<deviceE->maxBatteryVoltageToday()<<std::endl;

    
    return 0;
}
