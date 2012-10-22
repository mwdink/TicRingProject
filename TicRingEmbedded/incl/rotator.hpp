/*
 * rotator.hpp
 *
 *  Created on: May 11, 2011
 *      Author: mwdink
 */

#ifndef ROTATOR_HPP_
#define ROTATOR_HPP_

#include <stdint.h>
#include "hardwareInterface.hpp"

enum rotationStatus
{
	ROTATE_IDLE,
	ROTATE_CCW,
	ROTATE_CW,
	ROTATE_START,
    ROTATE_ERROR,
	LAST_STATUS
};


class Rotator
{
public:
    Rotator();
    virtual ~Rotator(){;}

    uint32_t getControlPotValue(void);
	uint32_t getRotatorPotValue(void);
	rotationStatus getRotationStatus(void);
    void setRotationStatus(rotationStatus newRotation);
	void startRotation(void);
	void controlRotation(void);
	bool isRotatorBusy(void);
    bool isRotatingCW(void);
    bool isRotatingCCW(void);
    bool checkForProgress(void);
    void rotationError(void);

	void configureHardwareInterface(HardwareInterface *newHardwareInterface);


protected:
	rotationStatus rotation;

	uint32_t lastControlPotValue;  	// variable to store the last value coming from the sensor
	uint32_t lastRotatorPotValue;  	// variable to store the value coming from the sensor
    uint32_t progressSecondCount;   // variable to store the value coming from the sensor
    uint32_t progressRotationValue; // variable to store the value coming from the sensor
	HardwareInterface *pHardwareInterface;

	void configureToRotateCCW(void);
	void configureToRotateCW(void);
	void stopRotation(void);
};


#endif /* ROTATOR_HPP_ */
