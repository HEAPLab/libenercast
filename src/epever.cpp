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
    modbus_connect(ctx);
}

epever::~epever()
{
    modbus_close(ctx);
    modbus_free(ctx);
}