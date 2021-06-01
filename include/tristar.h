#include <modbus.h>
#include <string>
#include "chargeController.h"


class tristar : public chargeController{
private:
    modbus_t *ctx;
public:
    tristar(const std::string & device);
    virtual ~tristar();
    virtual int getVolt() const override;
};