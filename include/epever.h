#include <modbus.h>
#include <string>
#include "chargeController.h"


class epever : public chargeController{
private:
    modbus_t *ctx;
public:
    epever(const std::string & device);
    virtual ~epever();
}