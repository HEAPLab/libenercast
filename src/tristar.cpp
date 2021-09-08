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

void tristar::clean_and_throw_error() const {
    modbus_free(ctx);
    throw std::runtime_error(modbus_strerror(errno));
}

float tristar::getBatteryVoltage() const {
    uint16_t dest[16];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x0008, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        return dest[0]*96.667/32768;
    }
}

float tristar::getChargeCurrent() const {
    uint16_t dest[16];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x000B, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        return dest[0]*66.667/32768;
    }
}

float tristar::getLoadCurrent() const {
    uint16_t dest[16];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x000C, 1, dest)==-1){
        clean_and_throw_error();
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
        clean_and_throw_error();
    }else{
        return dest[0];
    }
}

float tristar::getHeatsinkTemp() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x000E, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        return dest[0];
    }
}
float tristar::getBatteryTemp() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x000F, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        return dest[0];
    }
}
float tristar::getRegulationVoltage() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x0010, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        //modbus_set_debug(ctx,FALSE);
        return dest[0]*96.667/3276;
    }
}
std::bitset<16> tristar::getFault() const {
    uint16_t dest;
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x0018, 1, &dest)==-1){
        clean_and_throw_error();
    }else{
        //modbus_set_debug(ctx,FALSE);
        std::bitset<16> result=dest;
        return result;
    }
}
float tristar::getAlarmLo() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x0017, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        return dest[0]; 
    }
}
float tristar::getHighVoltageDisconnect() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0xE00B, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        return dest[0]*96.667/32768;
    }
}
void tristar::setHighVoltageDisconnect(float v) { 
    //modbus_set_debug(ctx,TRUE);
    if(modbus_write_register(ctx, 0xE00B, v*32768/96.667)==-1){
        clean_and_throw_error();
    }
    
}
float tristar::getHighVoltageReconnect() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0xE00C, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        return dest[0]*96.667/32768;
    }
}
void tristar::setHighVoltageReconnect(float v)  {
    //modbus_set_debug(ctx,TRUE);
    if(modbus_write_register(ctx, 0xE00C, v*32768/96.667)==-1){
        clean_and_throw_error();
    }
    //modbus_set_debug(ctx,FALSE);
}

void tristar::clearFaults() const {
    //modbus_set_debug(ctx,TRUE);
    if(modbus_write_bit(ctx,0x0014,0xFF00)==-1){
        clean_and_throw_error();
    }
    modbus_set_debug(ctx,FALSE);
}
 
float tristar::getLoadVoltage() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(this->getControlMode()==1||this->getControlMode()==2){ //if load or diversion mode
        if(modbus_read_input_registers(ctx, 0x000A, 1, dest)==-1){ 
            clean_and_throw_error();
        }else{
            return dest[0];
        }
    }else{
        throw std::runtime_error("Charge controller not in load or diversion mode");
    }
}
    float tristar::maxBatteryVoltageToday() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0xE02B, 1, dest)==-1){ 
        clean_and_throw_error();
    }else{
        return dest[0]*96.667/32768;
    }
}
    float tristar::minBatteryVoltageToday() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0xE02C, 1, dest)==-1){ 
        clean_and_throw_error();
    }else{
        return dest[0]*96.667/32768;
    }
}

    float tristar::getHourmeter() const {
    uint16_t dest[2];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x0015, 2, dest)==-1){ 
        clean_and_throw_error();
    }else{
        uint32_t result = (dest[0]<<16)+dest[1];
        return result;
    }
}

    float tristar::getAmpHour_r() const {
        uint16_t dest[2];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x0011, 2, dest)==-1){ 
        clean_and_throw_error();
    }else{
        uint32_t result = (dest[0]<<16)+dest[1];
        return result;
    }
}
    float tristar::getAmpHour() const {
        uint16_t dest[2];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x0013, 2, dest)==-1){ 
        clean_and_throw_error();
    }else{
        uint32_t result = (dest[0]<<16)+dest[1];
        return result;
    }
} 

    float tristar::getControlState() const {
          uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x001B, 1, dest)==-1){ 
        clean_and_throw_error();
    }else{
        return dest[0];
    }
}

float tristar::getArrayVoltage() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(this->getControlMode()==0){
        if(modbus_read_input_registers(ctx, 0x000A, 1, dest)==-1){ 
            clean_and_throw_error();
        }else{
            return dest[0];
        }
    }else{
        throw std::runtime_error("Charge controller not in solar mode");
    }
}

float tristar::getDipswitchPos() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0x0019, 1, dest)==-1){ 
        clean_and_throw_error();
    }else{
        return dest[0];
    }
}
    
float tristar::getLowVoltageDisconnect() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0xE00F, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        return dest[0]*96.667/32768;
    }
}
void tristar::setLowVoltageDisconnect(float v) {
    //modbus_set_debug(ctx,TRUE);
    if(modbus_write_register(ctx, 0xE00F, v*32768/96.667)==-1){
        clean_and_throw_error();
    }
}
float tristar::getLowVoltageReconnect() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0xE010, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        return dest[0]*96.667/32768;
    }
}
void tristar::setLowVoltageReconnect(float v) {
    //modbus_set_debug(ctx,TRUE);
    if(modbus_write_register(ctx, 0xE010, v*32768/96.667)==-1){
        clean_and_throw_error();
    }
}

float tristar::getLVDwarningTimeout() const {
     uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0xE014, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        return dest[0]*0.1;
    }
}
void tristar::setLVDwarningTimeout(float s) {
      //modbus_set_debug(ctx,TRUE);
    if(modbus_write_register(ctx, 0xE014, s*0.1)==-1){
        clean_and_throw_error();
    }
}


float tristar::getLedV_g_gy() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0xE01B, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        return dest[0]*96.667/32768;
    }
}

void tristar::setLedV_g_gy(float v) {
    //modbus_set_debug(ctx,TRUE);
    if(modbus_write_register(ctx, 0xE01B, v*32768/96.667)==-1){
        clean_and_throw_error();
    }
}
float tristar::getLedV_gy_y() const{
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0xE01C, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        return dest[0]*96.667/32768;
    }
}
void tristar::setLedV_gy_y(float v)  {
    //modbus_set_debug(ctx,TRUE);
    if(modbus_write_register(ctx, 0xE01C, v*32768/96.667)==-1){
        clean_and_throw_error();
    }
}
float tristar::getLedV_y_yr() const{
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0xE01D, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        return dest[0]*96.667/32768;
    }
}
void tristar::setLedV_y_yr(float v) {
    //modbus_set_debug(ctx,TRUE);
    if(modbus_write_register(ctx, 0xE01D, v*32768/96.667)==-1){
        clean_and_throw_error();
    }
}
float tristar::getLedV_yr_r() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0xE01E, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        return dest[0]*96.667/32768;
    }
}
void tristar::setLedV_yr_r(float v) {
    //modbus_set_debug(ctx,TRUE);
    if(modbus_write_register(ctx, 0xE01E, v*32768/96.667)==-1){
        clean_and_throw_error();
    }
} 

//--
float tristar::getRegulationVoltage_25() const {
  uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0xE000, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        //modbus_set_debug(ctx,FALSE);
        return dest[0]*96.667/3276;
    }
}
void tristar::setRegulationVoltage_25(float v) {
  //modbus_set_debug(ctx,TRUE);
    if(modbus_write_register(ctx, 0xE000, v*32768/96.667)==-1){
        clean_and_throw_error();
    }
}
void tristar::setFloatVoltage(float v) {
  //modbus_set_debug(ctx,TRUE);
    if(modbus_write_register(ctx, 0xE001, v*32768/96.667)==-1){
        clean_and_throw_error();
    }
}
float tristar::getFloatVoltage() const {
  uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0xE001, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        //modbus_set_debug(ctx,FALSE);
        return dest[0]*96.667/3276;
    }
}
float tristar::getTimeBeforeFloat() const {
  uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0xE002, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        //modbus_set_debug(ctx,FALSE);
        return dest[0];
    }
}
void tristar::setTimeBeforeFloat(uint16_t s) {
  //modbus_set_debug(ctx,TRUE);
    if(modbus_write_register(ctx, 0xE002, s)==-1){
        clean_and_throw_error();
    }
}
float tristar::getTimeBeforeFloat_lb() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0xE003, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        //modbus_set_debug(ctx,FALSE);
        return dest[0];
    }
}
void tristar::setTimeBeforeFloat_lb(uint16_t s) {
  //modbus_set_debug(ctx,TRUE);
    if(modbus_write_register(ctx, 0xE003, s)==-1){
        clean_and_throw_error();
    }
}
//EV_floatlb_trip
float tristar::getCancelFloatVoltage() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0xE005, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        //modbus_set_debug(ctx,FALSE);
        return dest[0]*96.667/3276;
    }
}
void tristar::setCancelFloatVoltage(float v) {
    //modbus_set_debug(ctx,TRUE);
    if(modbus_write_register(ctx, 0xE005, v*32768/96.667)==-1){
        clean_and_throw_error();
    }
}
float tristar::getEqualizeVoltage() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0xE006, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        //modbus_set_debug(ctx,FALSE);
        return dest[0]*96.667/3276;
    }
}
void tristar::setEqualizeVoltage(float v) {
    //modbus_set_debug(ctx,TRUE);
    if(modbus_write_register(ctx, 0xE006, v*32768/96.667)==-1){
        clean_and_throw_error();
    }
}
int tristar::getDaysBetweenEq() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0xE007, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        //modbus_set_debug(ctx,FALSE);
        return dest[0];
    }
}
void tristar::setDaysBetweenEq(uint8_t d) { 
    //modbus_set_debug(ctx,TRUE);
    if(modbus_write_register(ctx, 0xE007, d)==-1){
        clean_and_throw_error();
    }
}
int tristar::getDaysLastEq() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0xE00D, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        //modbus_set_debug(ctx,FALSE);
        return dest[0];
    }
}
void tristar::setDaysLastEq(uint8_t d) { 
    //modbus_set_debug(ctx,TRUE);
    if(modbus_write_register(ctx, 0xE00D, d)==-1){
        clean_and_throw_error();
    }
}
void tristar::setDiversionPWM() {
    //modbus_set_debug(ctx,TRUE);
    if(modbus_write_register(ctx, 0xE00D, 0)==-1){
        clean_and_throw_error();
    }
}
void tristar::setDiversionOnOff() {
    //modbus_set_debug(ctx,TRUE);
    if(modbus_write_register(ctx, 0xE042, 1)==-1){
        clean_and_throw_error();
    }
}

float tristar::getLoadHVD() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0xE011, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        return dest[0]*96.667/32768;
    }
}
void tristar::setLoadHVD(float v) {
    //modbus_set_debug(ctx,TRUE);
    if(modbus_write_register(ctx, 0xE011, v*32768/96.667)==-1){
        clean_and_throw_error();
    }

}
float tristar::getLoadHVR() const {
    uint16_t dest[1];
    //modbus_set_debug(ctx,TRUE);
    if(modbus_read_input_registers(ctx, 0xE012, 1, dest)==-1){
        clean_and_throw_error();
    }else{
        return dest[0]*96.667/32768;
    }
}
void tristar::setLoadHVR(float v) {
    //modbus_set_debug(ctx,TRUE);
    if(modbus_write_register(ctx, 0xE012, v*32768/96.667)==-1){
        clean_and_throw_error();
    }
    //modbus_set_debug(ctx,FALSE);
}
float tristar::getBattServiceInterval() const {
  uint16_t dest[1];
  //modbus_set_debug(ctx,TRUE);
  if(modbus_read_input_registers(ctx, 0xE022, 1, dest)==-1){
      clean_and_throw_error();
  }else{
      //modbus_set_debug(ctx,FALSE);
      return dest[0];
  }
}
void tristar::setBattServiceInterval(uint8_t d) {
  //modbus_set_debug(ctx,TRUE);
  if(modbus_write_register(ctx, 0xE022, d)==-1){
      clean_and_throw_error();
  }
  //modbus_set_debug(ctx,FALSE);
}
float tristar::getDaysLastBattService() const {
  uint16_t dest[1];
  //modbus_set_debug(ctx,TRUE);
  if(modbus_read_input_registers(ctx, 0xE023, 1, dest)==-1){
      clean_and_throw_error();
  }else{
      //modbus_set_debug(ctx,FALSE);
      return dest[0];
  }
}
float tristar::getKWH() const {
  uint16_t dest[1];
  //modbus_set_debug(ctx,TRUE);
  if(modbus_read_input_registers(ctx, 0xE02C, 1, dest)==-1){
      clean_and_throw_error();
  }else{
      //modbus_set_debug(ctx,FALSE);
      return dest[0];
  }
}

//Coils
void tristar::equalize() const {
  //modbus_set_debug(ctx,TRUE);
    if(modbus_write_bit(ctx,0x0000,0xFF00)==-1){
        clean_and_throw_error();
    }
    //modbus_set_debug(ctx,FALSE);
}
void tristar::stopEqualize() const {
    //modbus_set_debug(ctx,TRUE);
    if(modbus_write_bit(ctx,0x0000,0)==-1){
        clean_and_throw_error();
    }
    //modbus_set_debug(ctx,FALSE);
}
void tristar::disconnect() const {
    //modbus_set_debug(ctx,TRUE);
    if(modbus_write_bit(ctx,0x0001,0xFF00)==-1){
        clean_and_throw_error();
    }
    //modbus_set_debug(ctx,FALSE);
}
void tristar::reconnect() const {
    //modbus_set_debug(ctx,TRUE);
    if(modbus_write_bit(ctx,0x0001,0x0000)==-1){
        clean_and_throw_error();
    }
    //modbus_set_debug(ctx,FALSE);
}
void tristar::clearAh_r() const {
    //modbus_set_debug(ctx,TRUE);
    if(modbus_write_bit(ctx,0x0010,0xFF00)==-1){
        clean_and_throw_error();
    }
    //modbus_set_debug(ctx,FALSE);
}
void tristar::clearAh() const {
  //modbus_set_debug(ctx,TRUE);
    if(modbus_write_bit(ctx,0x0011,0xFF00)==-1){
        clean_and_throw_error();
    }
    //modbus_set_debug(ctx,FALSE);
}
void tristar::clearKwH() const {
  //modbus_set_debug(ctx,TRUE);
    if(modbus_write_bit(ctx,0x0012,0xFF00)==-1){
        clean_and_throw_error();
    }
    //modbus_set_debug(ctx,FALSE);
}
void tristar::resetLastBattService() const {
  //modbus_set_debug(ctx,TRUE);
    if(modbus_write_bit(ctx,0x0013,0xFF00)==-1){
        clean_and_throw_error();
    }
    //modbus_set_debug(ctx,FALSE);
}
void tristar::clearAlarms() const {
  //modbus_set_debug(ctx,TRUE);
    if(modbus_write_bit(ctx,0x0015,0xFF00)==-1){
        clean_and_throw_error();
    }
    //modbus_set_debug(ctx,FALSE);
}
void tristar::updateEprom() const {
  //modbus_set_debug(ctx,TRUE);
    if(modbus_write_bit(ctx,0x0016,0xFF00)==-1){
        clean_and_throw_error();
    }
    //modbus_set_debug(ctx,FALSE);
}
void tristar::LVDoverride() const {
  //modbus_set_debug(ctx,TRUE);
    if(modbus_write_bit(ctx,0x0017,0xFF00)==-1){
        clean_and_throw_error();
    }
    //modbus_set_debug(ctx,FALSE);
}
void tristar::reset() const {
  //modbus_set_debug(ctx,TRUE);
    if(modbus_write_bit(ctx,0x00FF,0xFF00)==-1){
        clean_and_throw_error();
    }
    //modbus_set_debug(ctx,FALSE);
}

