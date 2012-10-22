 /*****************************************************************************/
/* twoLineDisplay.cpp

!PURPOSE:
    contains hardware specific display implementation.
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
#include <wiring.h>
#include "twoLineDisplay.hpp"

static const uint8_t ROW1 = (uint8_t)0;
static const uint8_t ROW2 = (uint8_t)ROW1+1;
static const uint8_t COLUMN0 = (uint8_t)0;
static const uint8_t CONTROLHEADINGCOLUMN = (uint8_t)0;
static const uint8_t ROTATORHEADINGCOLUMN = (uint8_t)13;
static const uint8_t TOTALROWS = (uint8_t)2;
static const uint8_t TOTALCOLUMNS = (uint8_t)16;

static const uint8_t LCD_RS = (uint8_t)12;
static const uint8_t LCD_ENABLE = (uint8_t)11;
static const uint8_t LCD_D4 = (uint8_t)7;
static const uint8_t LCD_D5 = (uint8_t)6;
static const uint8_t LCD_D6 = (uint8_t)5;
static const uint8_t LCD_D7 = (uint8_t)4;

const char headerMsg[] = "Tic Ring";
const char errorMsg[] = "Error!";
const char blank3Msg[] = "   ";
const char blank10Msg[] = "          ";
const char twoZeroPad[] = "00 ";
const char oneZeroPad[] = "0  ";
const char rotatingMsg[] = "Rotating";
const char idleMsg[] = "Idle";
const char rightArrow[] = ">";
const char leftArrow[] = "<";



/*!Function     TwoLineDisplay::TwoLineDisplay
*   \par Purpose
*   			Constructor
*/
TwoLineDisplay::TwoLineDisplay():
pLcdInterface(0)
{;}


/*!Function     TwoLineDisplay::initializeDisplay
*   \return     void
*   \par Purpose
*   			set up this particular display
*/
void
TwoLineDisplay::initializeDisplay(void)
{
	//set up the LCD's number of columns and rows:
	pLcdInterface = new LiquidCrystal(LCD_RS, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
	if(pLcdInterface)
	{
		pLcdInterface->begin(TOTALCOLUMNS, TOTALROWS);
	}
}

/*!Function     TwoLineDisplay::displayHeader
*   \return     void
*   \par Purpose
*   			display header particular to this display hardware
*/
void
TwoLineDisplay::displayHeader(void)
{
	if(pLcdInterface)
	{
		// Print a message to the LCD.
		pLcdInterface->setCursor(COLUMN0+4, ROW1);
		pLcdInterface->print(headerMsg);
	}
}

/*!Function     TwoLineDisplay::displayError
*   \return     void
*   \par Purpose
*               display error header
*/
void
TwoLineDisplay::displayError(void)
{
    if(pLcdInterface)
    {
        pLcdInterface->setCursor(COLUMN0+4, ROW1);
        pLcdInterface->print(blank10Msg);
        pLcdInterface->setCursor(COLUMN0+6, ROW1);
        pLcdInterface->print(errorMsg);
    }
}

/*!Function     TwoLineDisplay::displayControlHeading
*	\param		uint32_t heading
*	\return		void
*   \par Purpose
*   			display degree heading of control pot
*/
void
TwoLineDisplay::displayControlHeading(uint32_t heading)
{
    static uint32_t savedControlHeading = 1000;

    if(!pLcdInterface)
    {
        return;
    }

    if(heading > 360)
    {
        ; /* error condition */
    }
    else if(heading != savedControlHeading)
    {
        savedControlHeading = heading;
        pLcdInterface->setCursor(CONTROLHEADINGCOLUMN, ROW2);
        pLcdInterface->print(blank3Msg);
        pLcdInterface->setCursor(CONTROLHEADINGCOLUMN, ROW2);

        if(heading < 10)
        {
            pLcdInterface->print(twoZeroPad);
            pLcdInterface->setCursor(CONTROLHEADINGCOLUMN+2, ROW2);
        }
        else if(heading < 100)
        {
            pLcdInterface->print(oneZeroPad);
            pLcdInterface->setCursor(CONTROLHEADINGCOLUMN+1, ROW2);
        }
        pLcdInterface->print(heading);
        //printf("Control Pot Heading %ld\n", heading);
    }
}

/*!Function     TwoLineDisplay::displayRotatorHeading
*	\param		uint32_t heading
*	\return		void
*   \par Purpose
*   			display degree heading of rotator pot
*/
void
TwoLineDisplay::displayRotatorHeading(uint32_t heading)
{
    static uint32_t savedRotatorHeading = 1000;

    if(!pLcdInterface)
    {
        return;
    }

    if(heading > 360)
    {
        ; /* error condition */
    }
    else if(heading != savedRotatorHeading)
    {
        savedRotatorHeading = heading;
        pLcdInterface->setCursor(ROTATORHEADINGCOLUMN, ROW2);
        pLcdInterface->print(blank3Msg);
        pLcdInterface->setCursor(ROTATORHEADINGCOLUMN, ROW2);

        if(heading < 10)
        {
            pLcdInterface->print(twoZeroPad);
            pLcdInterface->setCursor(ROTATORHEADINGCOLUMN+2, ROW2);
        }
        else if(heading < 100)
        {
            pLcdInterface->print(oneZeroPad);
            pLcdInterface->setCursor(ROTATORHEADINGCOLUMN+1, ROW2);
        }
        pLcdInterface->print(heading);
        //printf("Rotator Pot Heading %ld\n", heading);
    }
}

/*!Function     TwoLineDisplay::displayRotationMsg
*   \return     void
*   \par Purpose
*               display rotation status
*/
void
TwoLineDisplay::displayRotationMsg(void)
{
    if(pLcdInterface)
    {
        pLcdInterface->setCursor(COLUMN0+3, ROW2);
        pLcdInterface->print(blank10Msg);
        pLcdInterface->setCursor(COLUMN0+4, ROW2);
        pLcdInterface->print(rotatingMsg);
    }
}

/*!Function     TwoLineDisplay::displayIdleMsg
*   \return     void
*   \par Purpose
*               display rotation status
*/
void
TwoLineDisplay::displayIdleMsg(void)
{
    if(pLcdInterface)
    {
        pLcdInterface->setCursor(COLUMN0+3, ROW2);
        pLcdInterface->print(blank10Msg);
        pLcdInterface->setCursor(COLUMN0+6, ROW2);
        pLcdInterface->print(idleMsg);
    }
}

/*!Function     TwoLineDisplay::displayErrorMsg
*   \return     void
*   \par Purpose
*               display rotation status
*/
void
TwoLineDisplay::displayErrorMsg(void)
{
    if(pLcdInterface)
    {
        pLcdInterface->setCursor(COLUMN0+3, ROW2);
        pLcdInterface->print(blank10Msg);
        pLcdInterface->setCursor(COLUMN0+5, ROW2);
        pLcdInterface->print(errorMsg);
    }
}


/*!Function     TwoLineDisplay::displayRotationStatus
*   \param      bool_t isRotatingCW
*   \return     void
*   \par Purpose
*               display rotation status
*/
void
TwoLineDisplay::displayRotationCW(bool isRotatingCW)
{
    static uint32_t lastSecond = 0;
    static uint8_t lastCount = 0;
    uint32_t currentSecond = (millis()/1000);

    if(pLcdInterface)
    {
        if(isRotatingCW)
        {
            if(lastSecond < currentSecond)
            {
                lastSecond = currentSecond;
                if(lastCount < 3)
                {
                    pLcdInterface->setCursor(ROTATORHEADINGCOLUMN+lastCount, ROW1);
                    pLcdInterface->print(rightArrow);
                    ++lastCount;
                }
                else
                {
                    pLcdInterface->setCursor(ROTATORHEADINGCOLUMN, ROW1);
                    pLcdInterface->print(blank3Msg);
                    lastCount = 0;
                }
            }
        }
        else
        {
            pLcdInterface->setCursor(ROTATORHEADINGCOLUMN, ROW1);
            pLcdInterface->print(blank3Msg);
            lastCount = 0;
        }
    }
}

/*!Function     TwoLineDisplay::displayRotationCCW
*   \param      bool_t isRotatingCCW
*   \return     void
*   \par Purpose
*               display rotation status
*/
void
TwoLineDisplay::displayRotationCCW(bool isRotatingCCW)
{
    static uint32_t lastSecond = 0;
    static uint8_t lastCount = 3;
    uint32_t currentSecond = (millis()/1000);

    if(pLcdInterface)
    {
        if(isRotatingCCW)
        {
            if(lastSecond < currentSecond)
            {
                lastSecond = currentSecond;
                if(lastCount > 0)
                {
                    pLcdInterface->setCursor(CONTROLHEADINGCOLUMN+(lastCount-1), ROW1);
                    pLcdInterface->print(leftArrow);
                    --lastCount;
                }
                else
                {
                    pLcdInterface->setCursor(CONTROLHEADINGCOLUMN, ROW1);
                    pLcdInterface->print(blank3Msg);
                    lastCount = 3;
                }
            }
        }
        else
        {
            pLcdInterface->setCursor(CONTROLHEADINGCOLUMN, ROW1);
            pLcdInterface->print(blank3Msg);
            lastCount = 3;
        }
    }
}
