/*****************************************************************************/
/* controlHardware.cpp

!PURPOSE:
    contains hardware specific implementation.
    stuff in here is generally not testable

!SUBSYSTEM:

!DEPENDENCIES, LIMITATIONS & DESIGN NOTES:

!REVISION:
    $File:  $
    $Change:  $
    $Revision:  $
    $DateTime:  $
    $Author:    $

Copyright (c) 2011 - All rights reserved.
***************************************************************************/
#include <stdint.h>
#include <WProgram.h>
#include "controlHardware.hpp"

#define CONTROL_POT A4
#define ROTATOR_POT A5
#define CW_PIN	9
#define CCW_PIN	8

uint32_t compenstateCW(uint32_t value);
uint32_t compenstateCCW(uint32_t value);


/*!Function     ControlHardware::ControlHardware
*   \return     uint32_t
*   \par Purpose
*/
ControlHardware::ControlHardware():
controlPotSensePin(CONTROL_POT),
rotatorPotSensePin(ROTATOR_POT),
CWRelayPin(CW_PIN),
CCWRelayPin(CCW_PIN)
{
    pinMode(CW_PIN, OUTPUT);
    pinMode(CCW_PIN, OUTPUT);
    stopRotation();
}

/*!Function     ControlHardware::stopRotation
*   \return     void
*   \par Purpose
*/
void
ControlHardware::stopRotation(void)
{
	digitalWrite(CW_PIN, LOW);
	digitalWrite(CCW_PIN, LOW);
}

/*!Function     ControlHardware::configureToRotateCW
*   \return     void
*   \par Purpose
*/
void
ControlHardware::configureToRotateCW(void)
{
	digitalWrite(CW_PIN, LOW);
	digitalWrite(CCW_PIN, HIGH);
}


/*!Function     ControlHardware::rotateCCW
*   \return     void
*   \par Purpose
*/
void
ControlHardware::configureToRotateCCW(void)
{
	digitalWrite(CW_PIN, HIGH);
	digitalWrite(CCW_PIN, LOW);
}


/*!Function     ControlHardware::getControlPotValue
*   \return     uint32_t
*   \par Purpose
*/
uint32_t
ControlHardware::getControlPotValue(void)
{
	return analogRead(controlPotSensePin);
}

/*!Function     ControlHardware::getRotatorPotValue
*   \return     uint32_t
*   \par Purpose
*/
uint32_t
ControlHardware::getRotatorPotValue(void)
{
	uint32_t rotatorPotValue = analogRead(rotatorPotSensePin);

	if(rotatorPotValue < 516)
	{
		rotatorPotValue -= compenstateCW(rotatorPotValue);
	}
	else
	{
		rotatorPotValue += compenstateCCW(rotatorPotValue);
	}
	return rotatorPotValue;

	//	return analogRead(rotatorPotSensePin);
}

uint32_t
compenstateCW(uint32_t value)
{
	uint32_t compensation = 0;

	if(value < 185)
	{
		compensation = 105;
	}
	else if(value < 250)
	{
		compensation = 85;
	}
	else if(value < 310)
	{
		compensation = 65;
	}
	else if(value < 380)
	{
		compensation = 45;
	}
	else if(value < 450)
	{
		compensation = 25;
	}
	return compensation;
}

uint32_t
compenstateCCW(uint32_t value)
{
	uint32_t compensation = 0;

	if(value > 845)
	{
		compensation = 105;
	}
	else if(value > 780)
	{
		compensation = 85;
	}
	else if(value > 710)
	{
		compensation = 65;
	}
	else if(value > 650)
	{
		compensation = 45;
	}
	else if(value > 580)
	{
		compensation = 25;
	}
	return compensation;
}
