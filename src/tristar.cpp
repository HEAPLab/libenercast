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

//Voltage measured directly at the battery connection on the TriStar, filtered.
float tristar::getBatteryVoltage() const {
    uint16_t dest[16];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x0008, 1, dest)==-1){
        std::cout<<modbus_strerror(errno)<<std::endl;
        modbus_free(ctx);
    }else{
        return dest[0]*96.667/32768;
    }
}

//Slow filtered charging current value as measured by on-board shunts.
float tristar::getChargeCurrent() const {
    uint16_t dest[16];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x000B, 1, dest)==-1){
        std::cout<<modbus_strerror(errno)<<std::endl;
        modbus_free(ctx);
    }else{
        return dest[0]*66.667/32768;
    }
}

//Slow filtered load current value as measured by on-board shunts.
float tristar::getLoadCurrent() const {
    uint16_t dest[16];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x000C, 1, dest)==-1){
        std::cout<<modbus_strerror(errno)<<std::endl;
        modbus_free(ctx);
    }else{
        return dest[0]*316.67/32768;
    }
}
//Reports the mode in which the controller is running.
//0x00=charge
//0x01=load 
//0x02=diversion 
//0x03=lighting
float tristar::getControlMode() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x001A, 1, dest)==-1){
        std::cout<<modbus_strerror(errno)<<std::endl;
        modbus_free(ctx);
    }else{
        return dest[0];
    }
}

float tristar::getHeatsinkTemp() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x000E, 1, dest)==-1){
        std::cout<<modbus_strerror(errno)<<std::endl;
        modbus_free(ctx);
    }else{
        return dest[0];
    }
}
float tristar::getBatteryTemp() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x000F, 1, dest)==-1){
        std::cout<<modbus_strerror(errno)<<std::endl;
        modbus_free(ctx);
    }else{
        return dest[0];
    }
}
//Regulation Voltage. Target voltage to which the battery will be charged.
float tristar::getRegulationVoltage() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x0010, 1, dest)==-1){
        std::cout<<modbus_strerror(errno)<<std::endl;
        modbus_free(ctx);
    }else{
        //modbus_set_debug(ctx,FALSE);
        return dest[0]*96.667/3276;
    }
}
float tristar::getFault() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x0018, 1, dest)==-1){
        std::cout<<modbus_strerror(errno)<<std::endl;
        modbus_free(ctx);
    }else{
        //modbus_set_debug(ctx,FALSE);
        return dest[0]; // or read which is the error and return error number/name 
    }
}
float tristar::getAlarmLo() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x0017, 1, dest)==-1){
        std::cout<<modbus_strerror(errno)<<std::endl;
        modbus_free(ctx);
    }else{
        return dest[0]; // or read which is the error and return error number/name 
    }
}
float tristar::getVoltageDisconnect() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0xE00B, 1, dest)==-1){
        std::cout<<modbus_strerror(errno)<<std::endl;
        modbus_free(ctx);
    }else{
        return dest[0]*96.667/32768;
    }
}
void tristar::setVoltageDisconnect(float v) const { 
    //modbus_set_debug(ctx,TRUE);
    if(modbus_write_register(ctx, 0xE00B, v*32768/96.667)==-1){
        std::cout<<modbus_strerror(errno)<<std::endl;
        modbus_free(ctx);
    }
    
}
float tristar::getVoltageReconnect() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0xE00C, 1, dest)==-1){
        std::cout<<modbus_strerror(errno)<<std::endl;
        modbus_free(ctx);
    }else{
        return dest[0]*96.667/32768;
    }
}
void tristar::setVoltageReconnect(float v) const {
    //modbus_set_debug(ctx,TRUE);
    if(modbus_write_register(ctx, 0xE00C, v*32768/96.667)==-1){
        std::cout<<modbus_strerror(errno)<<std::endl;
        modbus_free(ctx);
    }
    //modbus_set_debug(ctx,FALSE);
}

void tristar::clearFaults() const {
    modbus_set_debug(ctx,TRUE);
    if(modbus_write_bit(ctx, 0x0014, 1)==-1){
        std::cout<<modbus_strerror(errno)<<std::endl;
        modbus_free(ctx);
    }
    modbus_set_debug(ctx,FALSE);
}
