#include <iostream>
#include <modbus.h>
#include <string>

#define BAUD 9600
#define PARITY 'N'
#define DATA_BIT 8
#define STOP_BIT 2

class tristar : public chargeController
{
private:
    modbus_t *ctx;
public:
    tristar(std::string device);
    ~tristar();
    int getVolt()
};