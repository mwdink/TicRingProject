/*****************************************************************************/
/* main.cpp

!PURPOSE:
    contains all the hardware specific setups, initializations, and
    the primary task loop. stuff in here is generally not testable

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
/*----------------------------- Nested includes -----------------------------*/
#include <wiring.h>
#include <WProgram.h>
#include <HardwareSerial.h>

#include "stdioFixup.hpp"
#include "uart.hpp"
#include "rotator.hpp"
#include "controlHardware.hpp"
#include "controlprocess.hpp"
#include "twoLineDisplay.hpp"

/*----------------- Symbolic Constants and Macros (defines) -----------------*/
#define BAUD    9600

/*-------------------------- Typedefs and structs ---------------------------*/
/*----------------------- Declarations (externs only) -----------------------*/
/*------------------------------ Declarations -------------------------------*/
Rotator *pRotator = 0;
DisplayInterface *pDisplay = 0;


int main(void)
{
    init();
    setup();

    for (;;)
    {
    	interrupt0Cleanup(millis()/1000);
        loop();
    }
    return 0;
}


/*!Function     setup
*   \return     void
*   \par Purpose
*               perform one-time initializations, attach hardware
*               implementations
*/
void setup(void)
{
    usartInit(BAUD);
    attachInterrupt(0, interrupt0Handler, FALLING);
    setupStdIo();

	pRotator = new Rotator;
	ControlHardware *pControlHardware = new ControlHardware;
	pRotator->configureHardwareInterface(pControlHardware);

	pDisplay = new TwoLineDisplay;
	pDisplay->initializeDisplay();
    pDisplay->displayHeader();
}


/*!Function     loop
*   \return     void
*   \par Purpose
*               main task loop for application
*/
void loop(void)
{
    processRotator();
    updateDisplay();
}









