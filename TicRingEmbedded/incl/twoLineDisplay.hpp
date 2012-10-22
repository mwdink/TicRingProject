/*
 * display.hpp
 *
 *  Created on: Jun 16, 2011
 *      Author: dinkem1
 */

#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

#include <LiquidCrystal.h>
#include "displayInterface.hpp"

class TwoLineDisplay: public DisplayInterface
{
public:
	TwoLineDisplay();
    virtual ~TwoLineDisplay(){;}

    virtual void initializeDisplay(void);
    virtual void displayHeader(void);
    virtual void displayError(void);
    virtual void displayControlHeading(uint32_t heading);
    virtual void displayRotatorHeading(uint32_t heading);
    virtual void displayRotationCW(bool isRotatingCW);
    virtual void displayRotationCCW(bool isRotatingCCW);
    virtual void displayRotationMsg(void);
    virtual void displayIdleMsg(void);
    virtual void displayErrorMsg(void);

protected:
	LiquidCrystal *pLcdInterface;
    //uint8_t lastStatusDisplayed;

private:

};


#endif /* DISPLAY_HPP_ */
