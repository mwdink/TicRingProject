/*
 * displayInterface.hpp
 *
 *  Created on: Jun 17, 2011
 *      Author: dinkem1
 */

#ifndef DISPLAYINTERFACE_HPP_
#define DISPLAYINTERFACE_HPP_
#include <stdint.h>

class DisplayInterface
{
public:
    virtual void initializeDisplay(void) = 0;
	virtual void displayHeader(void) = 0;
	virtual void displayControlHeading(uint32_t heading) = 0;
	virtual void displayRotatorHeading(uint32_t heading) = 0;
    virtual void displayRotationCW(bool isRotatingCW) = 0;
    virtual void displayRotationCCW(bool isRotatingCCW) = 0;
    virtual void displayRotationMsg(void) = 0;
    virtual void displayIdleMsg(void) = 0;
    virtual void displayErrorMsg(void) = 0;
};

#endif /* DISPLAYINTERFACE_HPP_ */
