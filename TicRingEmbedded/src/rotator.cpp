/*
 * rotator.cpp
 *
 *  Created on: May 11, 2011
 *      Author: mwdink
 */
#include <stdio.h>
#include <wiring.h>
#include "rotator.hpp"
#include "controlHardware.hpp"



/*!Function     Rotator::Rotator
*   \par Purpose
*   			Constructor
*/
Rotator::Rotator():
rotation(ROTATE_IDLE),
lastControlPotValue(1000),
lastRotatorPotValue(1000),
progressSecondCount(0),
pHardwareInterface(0)
{;}


/*!Function     Rotator::getControlPotValue
*   \return     uint32_t
*   \par Purpose
*               obtain the control pot value from the hardware
*/
uint32_t
Rotator::getControlPotValue(void)
{
    lastControlPotValue = 0;
    static uint32_t ControlPotValue = 0;
    if(pHardwareInterface)
    {
        lastControlPotValue = pHardwareInterface->getControlPotValue();
//        if(lastControlPotValue != ControlPotValue)
//        {
//        	ControlPotValue = lastControlPotValue;
//        	printf("ControlPotValue: %ld\n", lastControlPotValue);
//        }
    }
	return lastControlPotValue;
}

/*!Function     Rotator::getRotatorPotValue
*   \return     uint32_t
*   \par Purpose
*               obtain the rotator pot value from the hardware
*/
uint32_t
Rotator::getRotatorPotValue(void)
{
    lastRotatorPotValue = 0;
    static uint32_t RotatorPotValue = 0;
    if(pHardwareInterface)
    {
        lastRotatorPotValue = pHardwareInterface->getRotatorPotValue();
//        if(lastRotatorPotValue != RotatorPotValue)
//        {
//        	RotatorPotValue = lastRotatorPotValue;
//    		printf("RotatorPotValue: %ld\n", lastRotatorPotValue);
//        }
    }
    return lastRotatorPotValue;
}


/*!Function     Rotator::setRotationStatus
*   \return     void
*   \par Purpose
*/
void
Rotator::setRotationStatus(rotationStatus newRotation)
{
    rotation = newRotation;
}


/*!Function     Rotator::getRotationStatus
*   \return     rotationStatus
*   \par Purpose
*/
rotationStatus
Rotator::getRotationStatus(void)
{
    if(rotation < LAST_STATUS)
    {
        return rotation;
    }
    else
    {
        return ROTATE_ERROR;
    }
}


/*!Function     Rotator::startRotation
*   \return     void
*   \par Purpose
*/
void
Rotator::startRotation(void)
{
	if((ROTATE_IDLE == rotation) || (ROTATE_ERROR == rotation))
	{
        rotation = ROTATE_START;
		progressSecondCount = (millis()/1000) + 5; /* five seconds from now */
		progressRotationValue = getRotatorPotValue();
	}
	else
	{
        progressSecondCount = 0;
        progressRotationValue = 0;
	}
}



/*!Function     Rotator::controlRotation
*   \return     void
*   \par Purpose
*/
void
Rotator::controlRotation(void)
{
	if(ROTATE_START == rotation)
	{
	    if(getControlPotValue() > (getRotatorPotValue() + 5))
		{
			configureToRotateCCW();
		}
		else if(getControlPotValue() < (getRotatorPotValue() - 5))
		{
			configureToRotateCW();
		}
		else
		{
            rotation = ROTATE_IDLE;
		}
	}
	else
	{
		if(ROTATE_CCW == rotation)
		{
			//check for progress
			printf("CCW: %ld, %ld\n", getControlPotValue(), getRotatorPotValue());
			//check for progress
			if(getControlPotValue() <= getRotatorPotValue())
			{
				stopRotation();
			}
		}
		else if(ROTATE_CW == rotation)
		{
			//check for progress
			printf("CW: %ld, %ld\n", getControlPotValue(), getRotatorPotValue());

			if(getControlPotValue() >= getRotatorPotValue())
			{
				stopRotation();
			}
		}
	}
}



/*!Function     Rotator::configureToRotateCCW
*   \return     void
*   \par Purpose
*/
void
Rotator::configureToRotateCCW(void)
{
	if(pHardwareInterface)
	{
		pHardwareInterface->configureToRotateCCW();
	    rotation = ROTATE_CCW;
	}
	else
	{
        rotation = ROTATE_ERROR;
	}
}

/*!Function     Rotator::configureToRotateCW
*   \return     void
*   \par Purpose
*/
void
Rotator::configureToRotateCW(void)
{
	if(pHardwareInterface)
	{
		pHardwareInterface->configureToRotateCW();
	    rotation = ROTATE_CW;
	}
	else
	{
        rotation = ROTATE_ERROR;
	}
}

/*!Function     Rotator::stopRotation
*   \return     void
*   \par Purpose
*/
void
Rotator::stopRotation(void)
{
	if(pHardwareInterface)
	{
		pHardwareInterface->stopRotation();
	    rotation = ROTATE_IDLE;
	}
	else
	{
        rotation = ROTATE_ERROR;
	}
}


/*!Function     Rotator::rotationError
*   \return     void
*   \par Purpose
*/
void
Rotator::rotationError(void)
{
    //printf("rotationError\n");
    stopRotation();
    rotation = ROTATE_ERROR;
}



/*!Function     Rotator::configureHardwareInterface
*   \return     void
*   \par Purpose
*/
void
Rotator::configureHardwareInterface(HardwareInterface *newHardwareInterface)
{
	pHardwareInterface = newHardwareInterface;
}


/*!Function     Rotator::isRotatorBusy
*   \return     bool_t   (true/false)
*   \par Purpose
*/
bool
Rotator::isRotatorBusy(void)
{
    return  (rotation == ROTATE_IDLE) ? false:true;
}


/*!Function     Rotator::isRotatingCW
*   \return     bool_t   (true/false)
*   \par Purpose
*/
bool
Rotator::isRotatingCW(void)
{
    return  (rotation == ROTATE_CW) ? true:false;
}


/*!Function     Rotator::isRotatingCCW
*   \return     bool_t   (true/false)
*   \par Purpose
*/
bool
Rotator::isRotatingCCW(void)
{
    return  (rotation == ROTATE_CCW) ? true:false;
}

/*!Function     Rotator::checkForProgress
*   \return     void
*   \par Purpose
*/
bool
Rotator::checkForProgress(void)
{
    bool rotatingOk = true;

    if((ROTATE_CCW == rotation) || (ROTATE_CW == rotation))
    {
        uint32_t currentRotatorPosition = getRotatorPotValue();
        /* check every 5 seconds */
        if(progressSecondCount  <  (millis()/1000))
        {
            if((currentRotatorPosition > (progressRotationValue - 3)) &&
                    (currentRotatorPosition < (progressRotationValue + 3)))
            {
                //printf(">>>>>>>>>>>> NO MOVEMENT <<<<<<<<<<<<<<<<\n");
                /* error condition - pot isn't updating but rotator is */
                rotatingOk = false;
                rotationError();
            }
            else /* setup for next five seconds */
            {
                progressSecondCount = (millis()/1000) + 5;
                progressRotationValue = getRotatorPotValue();
            }
        }
    }
    return rotatingOk;
}
