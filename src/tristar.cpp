
#include "tristar.h"

tristar::tristar(std::string device)
{
    ctx= modbus_new_rtu(device.c_str(), BAUD, PARITY, DATA_BIT, STOP_BIT);
      if (ctx == NULL) {
            std::cout << "Unable to create the libmodbus context" << std::endl;
        }
    modbus_rtu_set_serial_mode(ctx,MODBUS_RTU_RS232);
    modbus_connect(ctx);
}

tristar::~tristar()
{
    modbus_close(ctx);
    modbus_free(ctx);
}

int tristar::getVolt(){
    uint16_t dest[16];
    modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x0008, 1, dest)==-1){
        std::cout<<modbus_strerror(errno)<<std::endl;
        modbus_free(ctx);
    }else{
        std::cout << dest[0] << 'V'<<std::endl;
}
}