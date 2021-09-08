#include "chargeController.h"
#include "tristar.h"
#include "epever.h"
#include <bitset>
#include <iostream>
int main(int argc, char const *argv[])
{
    std::cout<<"Epever:"<<std::endl;

    epever *deviceE = new epever("/dev/ttyXRUSB0");

    float battVoltageE = deviceE->getBatteryVoltage();
    std::cout<<"Battery Voltage: "<<battVoltageE<<std::endl;

    float loadCurrentE = deviceE->getLoadCurrent();
    std::cout<<"Load current: "<<loadCurrentE<<std::endl;

    std::cout<<"Max battery voltage today: "<<deviceE->maxBatteryVoltageToday()<<std::endl;

    if(deviceE->getDischargingEquipmentStatus(deviceE->LOAD_ON))std::cout<<"LOAD ON"<<std::endl;

    std::cout<<"heatsink temp"<<deviceE->getHeatsinkTemp()<<std::endl;

    if(deviceE->getChargingEquipmentStatus(deviceE->IS_CHARGING))std::cout<<"Charging normal"<<std::endl;
    
    if(deviceE->getBatteryStatus(deviceE->ALL_OK))std::cout<<"Battery Status OK"<<std::endl;    
    if(deviceE->getBatteryStatus(deviceE->VOLTAGE_NORMAL))std::cout<<"Battery voltage ok"<<std::endl;
    if(deviceE->getBatteryStatus(deviceE->OVER_VOLTAGE))std::cout<<"Battery over voltage"<<std::endl;
    if(deviceE->getBatteryStatus(deviceE->UNDER_VOLTAGE))std::cout<<"Battery under voltage"<<std::endl;

    return 0;
}
