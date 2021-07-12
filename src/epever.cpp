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
void epever::clean_and_throw_error() const {
    modbus_free(ctx);
    throw std::runtime_error(modbus_strerror(errno));
}

float epever::getBatteryVoltage() const {
    uint16_t dest[16];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x331A, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        return dest[0]*0.01;
    }
}
    

    float epever::getLoadCurrent() const {
        uint16_t dest[16];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x310D, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0]*0.01;
    }
  
}

    float epever::getLoadVoltage() const {
         uint16_t dest[16];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x310C, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0]*0.01;
    }

}

float epever::getLoadPower() const {
         uint16_t dest[2];
       // modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x310E, 2, dest)==-1){
            clean_and_throw_error();
        }else{
            uint32_t result = (dest[0]<<16)+dest[1];
            return result;
    }
}

    float epever::getLoadStatus() const {
        uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x3202, 1, dest)==-1){ 
            clean_and_throw_error();
        }else{
            return dest[0];  //risultato dipende dal bit correggere return
    }
}
    float epever::getChargeCurrent() const {
        uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x3101, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0]; 
        }
    }
    float epever::getArrayVoltage() const {
        uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x3100, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0]; 
        }
    }
    float epever::getArrayPower() const {
        uint16_t dest[2];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x3102, 2, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0]; //aggiustare (2 reg)
    }
    }
    float epever::getArrayStatus() const {
        uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x3201, 1, dest)==-1){ 
            clean_and_throw_error();
        }else{
            return dest[0]; //Va selezionato il bit,correggere 
        }
    }
    float epever::deviceStatus() const {
        uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x3201, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0]; //Va selezionato il bit,correggere 
        }
    }
    float epever::getHeatsinkTemp() const {
        uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x3111, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0];  
        }
    }


    float epever::maxBatteryVoltageToday() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x3302, 1, dest)==-1){ 
        clean_and_throw_error();
    }else{
        return dest[0]*0.01;
    }
}
    float epever::minBatteryVoltageToday() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x3303, 1, dest)==-1){ 
        clean_and_throw_error();
    }else{
        return dest[0]*0.01;
    }
}

    float epever::getBatteryTemp() const {
         uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x3110, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0];  
        }
    }
    
    //----------------------------------------------------------------------------
    float epever::getHighVoltageDisconnect() const {
        uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x9003, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0]*0.01;
        }
    }

    void epever::setHighVoltageDisconnect(float v) {
         //modbus_set_debug(ctx,TRUE);
        if(modbus_write_register(ctx, 0x9003, v*100)==-1){
            clean_and_throw_error();
        }
    }

    float epever::getHighVoltageReconnect() const {
        uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x9005, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0]*0.01;
        }
    }

    void epever::setHighVoltageReconnect(float v)  {
         //modbus_set_debug(ctx,TRUE);
        if(modbus_write_register(ctx, 0x9005, v*100)==-1){
            clean_and_throw_error();
        }
    }

    float epever::getLowVoltageDisconnect() const {
        uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x900D, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0]*0.01;
        }
    }

    void epever::setLowVoltageDisconnect(float v)  {
          //modbus_set_debug(ctx,TRUE);
        if(modbus_write_register(ctx, 0x900D, v*100)==-1){
            clean_and_throw_error();
        }
    }

    float epever::getLowVoltageReconnect() const {
        uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x900A, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0]*0.01;
        }
    }
    
    void epever::setLowVoltageReconnect(float v) {
        //modbus_set_debug(ctx,TRUE);
        if(modbus_write_register(ctx, 0x900A, v*100)==-1){
            clean_and_throw_error();
        }
    }
    float epever::getLVDwarningTimeout() const {return 0;}
    void epever::setLVDwarningTimeout(float v)  {}

    float epever::getArrayCurrent() const {
        uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x3101, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0]*0.01;
        }
    }
    float epever::getBatterySOC() const {
        uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x311A, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0];
        }
    }
    float epever::getBateryStatus() const {
        uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x3200, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0]; //dipende dal bit
        }
    }
    
    float epever::getChargingStatus() const {
        uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x3201, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0]; //dipende dal bit
        }
    }

    float epever::getBatteryCapacity() const{
        uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x9001, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0];
        }
    }
    void epever::setBatteryCapacity(float ah){
        //modbus_set_debug(ctx,TRUE);
        if(modbus_write_register(ctx, 0x9001, ah)==-1){
            clean_and_throw_error();
        }
    }
    float epever::getEqualizeChargingV() const {
        uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x9006, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0]*0.01;
        }
    }
    void epever::setEqualizeChargingV(float v){
        //modbus_set_debug(ctx,TRUE);
        if(modbus_write_register(ctx, 0x9006, v*100)==-1){
            clean_and_throw_error();
        }
    }
    float epever::getBoostChargingV() const{
        uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x9007, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0]*0.01;
        }
    }
    void epever::setBoostChargingV(float v){
        //modbus_set_debug(ctx,TRUE);
        if(modbus_write_register(ctx, 0x9007, v*100)==-1){
            clean_and_throw_error();
        }
    }
    float epever::getFloatChargingV() const{
        uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x9008, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0]*0.01;
        }
    }
    void epever::setFloatChargingV(float v){
        //modbus_set_debug(ctx,TRUE);
        if(modbus_write_register(ctx, 0x9008, v*100)==-1){
            clean_and_throw_error();
        }
    }
    float epever::getBoostReconnectCahargingV() const{
        uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x9009, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0]*0.01;
        }
    }
    void epever::setBoostReconnectCahargingV(float v){
        //modbus_set_debug(ctx,TRUE);
        if(modbus_write_register(ctx, 0x9009, v*100)==-1){
            clean_and_throw_error();
        }
    }
    float epever::getDischargingLimitV() const{
        uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x900E, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0]*0.01;
        }
    }
    void epever::setDischargingLimitV(float v){
        //modbus_set_debug(ctx,TRUE);
        if(modbus_write_register(ctx, 0x900E, v*100)==-1){
            clean_and_throw_error();
        }
    }
    float epever::getChargingLimitV() const{
         uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x9004, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0]*0.01;
        }
    }
    void epever::setChargingLimitV(float v){
        //modbus_set_debug(ctx,TRUE);
        if(modbus_write_register(ctx, 0x9004, v*100)==-1){
            clean_and_throw_error();
        }
    }
    float epever::getBoosDuration() const{
         uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x906B, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0];
        }
    }
    void epever::setBoosDuration(int min){
        //modbus_set_debug(ctx,TRUE);
        if(modbus_write_register(ctx, 0x906B, min)==-1){
            clean_and_throw_error();
        }
    }
    float epever::getEquilibriumDuration() const{
         uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x906C, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0];
        }
    }
    void epever::setEquilibriumDuration(int min){
        //modbus_set_debug(ctx,TRUE);
        if(modbus_write_register(ctx, 0x906C, min)==-1){
            clean_and_throw_error();
        }
    }
    float epever::getBatteryUpTempLimit() const{
         uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x9017, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0]*0.01;
        }
    }
    float epever::getBatteryLwTempLimit() const{
         uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x9018, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0]*0.01;
        }
    }
    float epever::getDeviceOverTemp() const{
         uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x9019, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0]*0.01;
        }
    }
    float epever::getDeviceRecoveryTemp() const{
         uint16_t dest[1];
        //modbus_set_debug(ctx,TRUE);
        if(modbus_read_input_registers(ctx, 0x901A, 1, dest)==-1){
            clean_and_throw_error();
        }else{
            return dest[0]*0.01;
        }
    }
    void epever::setBatteryUpTempLimit(float deg){
        //modbus_set_debug(ctx,TRUE);
        if(modbus_write_register(ctx, 0x90017, deg*100)==-1){
            clean_and_throw_error();
        }
    }
    void epever::setBatteryLwTempLimit(float deg){
        //modbus_set_debug(ctx,TRUE);
        if(modbus_write_register(ctx, 0x9018, deg*100)==-1){
            clean_and_throw_error();
        }
    }
    void epever::setDeviceOverTemp(float deg){
        //modbus_set_debug(ctx,TRUE);
        if(modbus_write_register(ctx, 0x9019, deg*100)==-1){
            clean_and_throw_error();
        }
    }
    void epever::setDeviceRecoveryTemp(float deg){
        //modbus_set_debug(ctx,TRUE);
        if(modbus_write_register(ctx, 0x901A, deg*100)==-1){
            clean_and_throw_error();
        }
    }
    void epever::chargingDeviceOn() const {
        //modbus_set_debug(ctx,TRUE);
        if(modbus_write_bit(ctx,0,0xFF00)==-1){
            clean_and_throw_error();
        }else{
             
        }
    }
    void epever::chargingDeviceOff() const {
        //modbus_set_debug(ctx,TRUE);
        if(modbus_write_bit(ctx,0,0)==-1){
            clean_and_throw_error();
        }else{
             
        }
    }
    void epever::LoadOn(){
        //modbus_set_debug(ctx,TRUE);
        if(modbus_write_bit(ctx,6,0xFF00)==-1){
            clean_and_throw_error();
        }else{
             
        }
    }
    void epever::loadOff(){
        //modbus_set_debug(ctx,TRUE);
        if(modbus_write_bit(ctx,6,0)==-1){
            clean_and_throw_error();
        }else{
             
        }
    }
    void epever::RestoreSystemDefaults(){
        //modbus_set_debug(ctx,TRUE);
        if(modbus_write_bit(ctx,13,0xFF00)==-1){
            clean_and_throw_error();
        }else{
             
        }
    }
    void epever::loadTestModeOn(){
        //modbus_set_debug(ctx,TRUE);
        if(modbus_write_bit(ctx,5,0xFF00)==-1){
            clean_and_throw_error();
        }else{
             
        }
    }
    void epever::loadTestModeOff(){
        //modbus_set_debug(ctx,TRUE);
        if(modbus_write_bit(ctx,5,0)==-1){
            clean_and_throw_error();
        }else{
             
        }
    }