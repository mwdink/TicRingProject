/*
 * mockHardware.hpp
 *
 *  Created on: Jun 21, 2011
 *      Author: dinkem1
 */

#define LONG_VALUE1     0x1234
#define LONG_VALUE2     0x5678
#define LONG_VALUE3     0x9abc

namespace mockHardware
{


class MockHardware: public HardwareInterface
{
public:
    uint32_t getControlPotValue(void){return testControlValue;}
    uint32_t getRotatorPotValue(void){return testRotatorValue;}
    void stopRotation(void){testValue = LONG_VALUE3;}
    void configureToRotateCW(void){testValue = LONG_VALUE1;}
    void configureToRotateCCW(void){testValue = LONG_VALUE2;}

    void setControlPotValue(uint32_t newValue){testControlValue = newValue;}
    void setRotatorPotValue(uint32_t newValue){testRotatorValue = newValue;}
    uint32_t getTestValue(void){return testValue;}
    void clearTestValue(void){testValue = 0;}


private:
    uint32_t testValue;
    uint32_t testControlValue;
    uint32_t testRotatorValue;
};

}
