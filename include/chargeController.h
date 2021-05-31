class chargeController
{
private:
    
public:
    chargeController();
    ~chargeController();
    virtual int getVolt() = 0;
};

chargeController::chargeController()
{
}

chargeController::~chargeController()
{
}
