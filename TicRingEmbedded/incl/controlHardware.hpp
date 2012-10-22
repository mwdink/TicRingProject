/*
 * controlHardware.hpp
 *
 *  Created on: May 19, 2011
 *      Author: mwdink
 */

#ifndef CONTROLHARDWARE_HPP_
#define CONTROLHARDWARE_HPP_

#include "hardwareInterface.hpp"





class ControlHardware: public HardwareInterface
{
public:
	ControlHardware();
    virtual ~ControlHardware(){;}

	uint32_t getControlPotValue(void);
    uint32_t getRotatorPotValue(void);

	void stopRotation(void);
	void configureToRotateCW(void);
	void configureToRotateCCW(void);

private:
	uint32_t controlPotSensePin;   	//hardware pin for the control potentiometer (input)
	uint32_t rotatorPotSensePin;   	//hardware pin for the rotator potentiometer (input)
	uint32_t CWRelayPin;    		//hardware pin for the rotator potentiometer (input)
	uint32_t CCWRelayPin;    		//hardware pin for the rotator potentiometer (input)
	uint32_t startPin;    			//hardware pin for the rotator potentiometer (input)
};


#endif /* CONTROLHARDWARE_HPP_ */
