#include "chargeController.h"
#include "tristar.h"
int main(int argc, char const *argv[])
{
    chargeController *device = new tristar("/dev/ttyUSB0");
    device->getVolt();
    return 0;
}
