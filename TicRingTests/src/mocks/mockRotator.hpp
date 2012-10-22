/*
 * mockRotator.hpp
 *
 *  Created on: Jun 21, 2011
 *      Author: dinkem1
 */

namespace mockRotator
{

class MockRotator : public Rotator
{
public:
    rotationStatus getRotation(void){return rotation;}
    void setRotation(rotationStatus newRotation){rotation = newRotation;}
    uint32_t getLastControlPotValue(void){return lastControlPotValue;}
    void setLastControlPotValue(uint32_t newValue){lastControlPotValue = newValue;}
    uint32_t getLastRotatorPotValue(void){return lastRotatorPotValue;}
    uint32_t getProgressSecondCount(void){return progressSecondCount;}
    uint32_t getProgressRotationValue(void){return progressRotationValue;}
    HardwareInterface *getHardwareInterface(void){return pHardwareInterface;}
    void testAccessToConfigureToRotateCCW(void){configureToRotateCCW();}
    void testAccessToConfigureToRotateCW(void){configureToRotateCW();}
    void testAccessToStopRotation(void){stopRotation();}
};

}
