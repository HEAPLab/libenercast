#include <iostream>
#include "tristar.h"

#define BAUD 9600
#define PARITY 'N'
#define DATA_BIT 8
#define STOP_BIT 2

tristar::tristar(const std::string &device)
{
    ctx= modbus_new_rtu(device.c_str(), BAUD, PARITY, DATA_BIT, STOP_BIT);
    if (ctx == NULL) {
        std::cout << "Unable to create the libmodbus context" << std::endl;
    }
    modbus_set_slave(ctx, 1);
    modbus_rtu_set_serial_mode(ctx,MODBUS_RTU_RS232);
    modbus_connect(ctx);
}

tristar::~tristar()
{
    modbus_close(ctx);
    modbus_free(ctx);
}

int tristar::getVolt() const {
    uint16_t dest[16];
    modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x0008, 1, dest)==-1){
        std::cout<<modbus_strerror(errno)<<std::endl;
        modbus_free(ctx);
    }else{
        std::cout << dest[0] << 'V'<<std::endl;
        
    }
}