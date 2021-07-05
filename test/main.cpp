#include "chargeController.h"
#include "tristar.h"
#include "epever.h"
#include <iostream>
int main(int argc, char const *argv[])
{
    chargeController *device = new tristar("/dev/ttyUSB0");
    //chargeController *deviceE = new epever("/dev/ttyXRUSB0");
  
    float battVoltage = device->getBatteryVoltage();
    std::cout<<"battery Voltage Tristar: "<<battVoltage<<std::endl;

    //float hourmeter = device->getHourmeter();
    //std::cout<<"hourmeter: "<<hourmeter<<std::endl;


    //float battVoltageE = deviceE->getBatteryVoltage();
    //std::cout<<"battery Voltage Epever: "<<battVoltageE<<std::endl;

   /* float solarCurrent = device->getChargeCurrent();
    std::cout<<"charge/solar current: " <<solarCurrent<<std::endl;

    float loadCurrent = device->getLoadCurrent();
    std::cout<<"Load current: "<<loadCurrent<<std::endl;

    float loadCurrentE = deviceE->getLoadCurrent();
    std::cout<<"Load current: "<<loadCurrentE<<std::endl;

    int heatsinkTemp = device->getHeatsinkTemp();
    std::cout<<"heatsink temp: "<<heatsinkTemp<<std::endl;

    int batteryTemp = device->getBatteryTemp();
    std::cout<<"battery temperature: "<<batteryTemp<<std::endl;

    int regulationVoltage = device->getRegulationVoltage();
    std::cout<<"Regulation/Target voltage: "<<regulationVoltage<<std::endl;*/

    int fault = device->getFault();
    std::cout<<"fault: "<<fault<<std::endl;

    /*int alarm = device->getAlarmLo();
    std::cout<<"alarm: "<<alarm<<std::endl;

    float voltageDisconnect = device->getVoltageDisconnect();
    std::cout<<"voltage disconnect: "<<voltageDisconnect<<std::endl; 
    
    float voltageRec = device->getVoltageReconnect();
    std::cout<<"voltage reconnect: "<<voltageRec<<std::endl;

    device->setVoltageReconnect(13.008);

    voltageRec = device->getVoltageReconnect();
    std::cout<<"voltage reconnect: "<<voltageRec<<std::endl;*/

    // float minBatteryV = device->minBatteryVoltageToday();
    // std::cout<<"Min Battery Today: "<<minBatteryV<<std::endl;
    
    // float maxBatteryV = device->maxBatteryVoltageToday();
    // std::cout<<"Max Battery Voltage Today : "<<maxBatteryV<<std::endl;

    // device->clearFaults();
    // fault = device->getFault();
    // std::cout<<"fault: "<<fault<<std::endl;

    float controlMode = device->getControlMode();
    std::cout<<"control mode: "<<controlMode<<std::endl;


    float controlState = device->getControlState();
    std::cout<<"control State: "<<controlState<<std::endl;
    
    return 0;
}
