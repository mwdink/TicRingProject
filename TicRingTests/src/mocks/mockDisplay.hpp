/*
 * mockDisplay.hpp
 *
 *  Created on: Jun 22, 2011
 *      Author: dinkem1
 */

#ifndef MOCKDISPLAY_HPP_
#define MOCKDISPLAY_HPP_

#include "displayInterface.hpp"

const uint32_t idle = 0x0001;
const uint32_t error = 0x0002;
const uint32_t rotate = 0x0004;
const uint32_t cw = 0x0008;
const uint32_t ccw = 0x0010;

uint32_t mockHeading;
uint32_t mockDisplayMsg;

void setTestHeading(uint32_t heading){mockHeading = heading;}
uint32_t getTestHeading(void){return mockHeading;}

void setDisplayMsg(uint32_t msg){mockDisplayMsg = msg;}
uint32_t getDisplayMsg(void){return mockDisplayMsg;}

class MockDisplay: public DisplayInterface
{
public:
    virtual void initializeDisplay(void){;}
    virtual void displayHeader(void){;}
    virtual void displayError(void){;}
    virtual void displayControlHeading(uint32_t heading){mockHeading = heading;}
    virtual void displayRotatorHeading(uint32_t heading){mockHeading = heading;}
    virtual void displayRotationCW(bool isRotatingCW)
    {
        if(true == isRotatingCW)
        {
            mockDisplayMsg |= cw;
        }
    }
    virtual void displayRotationCCW(bool isRotatingCCW)
    {
        {
            if(true == isRotatingCCW)
            {
                mockDisplayMsg |= ccw;
            }
        }
    }
    virtual void displayRotationMsg(void){mockDisplayMsg |= rotate;}
    virtual void displayIdleMsg(void){mockDisplayMsg |= idle;}
    virtual void displayErrorMsg(void){mockDisplayMsg |= error;}

};
#endif /* MOCKDISPLAY_HPP_ */
