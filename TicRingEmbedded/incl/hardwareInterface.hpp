/*
 * hardwareInterface.hpp
 *
 *  Created on: May 19, 2011
 *      Author: mwdink
 */

#ifndef HARDWAREINTERFACE_HPP_
#define HARDWAREINTERFACE_HPP_
#include <stdint.h>

class HardwareInterface
{
public:
	virtual uint32_t getControlPotValue(void) = 0;
	virtual uint32_t getRotatorPotValue(void) = 0;
    virtual void stopRotation(void) = 0;
	virtual void configureToRotateCW(void) = 0;
	virtual void configureToRotateCCW(void) = 0;
};
#endif /* HARDWAREINTERFACE_HPP_ */
