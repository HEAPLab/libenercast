#include <iostream>
#include "epever.h"

#define BAUD 115200
#define PARITY 'N'
#define DATA_BIT 8
#define STOP_BIT 1

epever::epever(const std::string &device)
{
    ctx= modbus_new_rtu(device.c_str(), BAUD, PARITY, DATA_BIT, STOP_BIT);
    if (ctx == NULL) {
        std::cout << "Unable to create the libmodbus context" << std::endl;
    }
    modbus_set_slave(ctx, 1);
    modbus_rtu_set_serial_mode(ctx,MODBUS_RTU_RS485);
    //modbus_connect(ctx);
      if (modbus_connect(ctx) == -1) {
        std::cout << "Connection failed" << std::endl;
        modbus_free(ctx);
    }
}

epever::~epever()
{
    modbus_close(ctx);
    modbus_free(ctx);
}

float epever::getBatteryVoltage() const {
    uint16_t dest[16];
    modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x331A, 1, dest)==-1){
        std::cout << "failed" << std::endl;
        std::cout<<modbus_strerror(errno)<<std::endl;
        modbus_free(ctx);
    }else{
        return dest[0];
    }
}
    float epever::getChargeCurrent() const {return 0;};

    float epever::getLoadCurrent() const {
    uint16_t dest[16];
    modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x310D, 1, dest)==-1){
        std::cout<<modbus_strerror(errno)<<std::endl;
        modbus_free(ctx);
    }else{
        return dest[0];
    }
}
    float epever::getControlMode() const {return 0;};
    float epever::getHeatsinkTemp() const {return 0;};
    float epever::getBatteryTemp() const {return 0;};
    float epever::getRegulationVoltage() const {return 0;};
    float epever::getAlarmLo() const {return 0;};
    float epever::getFault() const {return 0;};

    float epever::getVoltageDisconnect() const {return 0;};
    void epever::setVoltageDisconnect(float v) const {};
    float epever::getVoltageReconnect() const {return 0;};
    void epever::setVoltageReconnect(float v) const {};
    void epever::clearFaults() const {};
