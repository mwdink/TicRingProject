/*
 * controlProcess.cpp
 *
 *  Created on: Jun 21, 2011
 *      Author: dinkem1
 */
/*----------------------------- Nested includes -----------------------------*/
#include <wiring.h>
#include "controlprocess.hpp"

/*----------------- Symbolic Constants and Macros (defines) -----------------*/
/*-------------------------- Typedefs and structs ---------------------------*/
/*----------------------- Declarations (externs only) -----------------------*/
extern Rotator *pRotator;
extern DisplayInterface *pDisplay;

/*------------------------------ Declarations -------------------------------*/
long interrupt0Debounce = 0;

/*--------------------------- Function prototypes ---------------------------*/
void displayControlPot(void);
void displayRotatorPot(void);
uint32_t convertToPercentage(uint32_t potValue);
uint32_t convertToNorthCenteredDegrees(uint32_t percentageValue);
//void debugStatus(void);


/*!Function     updateDisplay
*   \return     void
*   \par Purpose
*               process display functionality
*/
void
updateDisplay(void)
{
    static rotationStatus lastRotationStatus = LAST_STATUS;
    rotationStatus currentRotationStatus = pRotator->getRotationStatus();

    if(lastRotationStatus != currentRotationStatus)
    {
        switch(currentRotationStatus)
        {
        case ROTATE_IDLE:
            pDisplay->displayIdleMsg();
            break;
        case ROTATE_ERROR:
            pDisplay->displayIdleMsg();
            pDisplay->displayErrorMsg();
            break;
        case ROTATE_CCW:
        case ROTATE_CW:
            pDisplay->displayRotationMsg();
            break;
        case ROTATE_START:
        default:
            break;
        }
        lastRotationStatus = currentRotationStatus;
    }

    displayControlPot();
    displayRotatorPot();
    pDisplay->displayRotationCW(pRotator->isRotatingCW());
    pDisplay->displayRotationCCW(pRotator->isRotatingCCW());

    //debugStatus();
}


/*!Function     displayControlPot
*   \return     void
*   \par Purpose
*               display the control pot value on the display
*/
void
displayControlPot(void)
{
    if(pRotator && pDisplay)
    {
        uint32_t percentageValue = 0;
        uint32_t northCenterDegreeValue = 0;
        percentageValue = convertToPercentage(pRotator->getControlPotValue());
        northCenterDegreeValue = convertToNorthCenteredDegrees(percentageValue);
        pDisplay->displayControlHeading(northCenterDegreeValue);
    }
}


/*!Function     displayControlPot
*   \return     void
*   \par Purpose
*               display the rotator pot value on the display
*/
void
displayRotatorPot(void)
{
    if(pRotator && pDisplay)
    {
        uint32_t percentageValue = 0;
        uint32_t northCenterDegreeValue = 0;
        percentageValue = convertToPercentage(pRotator->getRotatorPotValue());
        northCenterDegreeValue = convertToNorthCenteredDegrees(percentageValue);
        pDisplay->displayRotatorHeading(northCenterDegreeValue);
    }
}

/*!Function     convertToPercentage
*   \param      uint32_t potValue
*   \return     void
*   \par Purpose
*               display the rotator pot value on the display
*/
uint32_t convertToPercentage(uint32_t potValue)
{
    return (potValue*100)/1023;
}


/*!Function     displayNorthCenteredDegrees
*   \param      uint32_t percentageValue (percentage between 0 and 360 degrees)
*   \return     void
*   \par Purpose
*               set a value, in degrees, based on the
*               percentage of the pot value measured (0 to 100%)
*               this function assumes north is 0/360 degrees and 50% of the pot value
*               this function assumes south is 180 degrees and 0/100% of the pot value
*/
uint32_t convertToNorthCenteredDegrees(uint32_t percentageValue)
{
    uint32_t degreeValue = 1000;  /* init to error value */

    if((percentageValue < 0) || (percentageValue > 100))
    {
        ;   /*error condition*/
    }
    else
    {
        if(50 == percentageValue )
        {
            degreeValue = 0;
        }
        else if(percentageValue  < 50) /* this covers 0-180 degrees */
        {
            degreeValue = 180 - ((3600*percentageValue)/1000);

//            if((percentageValue > 25) && (percentageValue < 50))
//			{
//            	compensation = ((degreeValue * 130)/100)- degreeValue;
//			}
//            if((percentageValue > 13) && (percentageValue < 26))
//			{
//            	compensation = ((degreeValue * 129)/100)- degreeValue;
//			}
//            if(percentageValue < 26)
//			{
//            	compensation = ((degreeValue * 128)/100)- degreeValue;
//			}
//
//            if(true == compensate)
//            {
//            	//printf("Foo1: %ld, %ld, %ld\n", degreeValue, percentageValue, compensation);
//            	//printf("Foo1: %ld, %ld\n", degreeValue, degreeValue+compensation);
//            	//degreeValue += compensation;
//            }
        }
        else  /* this covers 180-360 degrees */
        {
            degreeValue = 360 + (180 - ((3600*percentageValue)/1000));

//            if((percentageValue > 62) && (percentageValue < 75))
//			{
//            	compensation = ((degreeValue * 130)/100)- degreeValue;
//			}
//            if((percentageValue > 75) && (percentageValue < 97))
//			{
//            	compensation = ((degreeValue * 129)/100)- degreeValue;
//			}
//            if(percentageValue > 97)
//			{
//            	compensation = ((degreeValue * 128)/100)- degreeValue;
//			}
        }
    }
    return degreeValue;
}

/*!Function     processRotator
*   \return     void
*   \par Purpose
*               process rotator functionality
*/
void
processRotator(void)
{
    pRotator->controlRotation();
    if(pRotator->isRotatorBusy())
    {
        pRotator->checkForProgress();
    }
}



/*!Function     interrupt0Handler
*   \return     void
*   \par Purpose
*               process interrupt zero
*/
void
interrupt0Handler(void)
{
    if(pRotator)
    {
        if(0 == interrupt0Debounce)
        {
            pRotator->startRotation();
            interrupt0Debounce = millis()/1000;
        }
    }
}

/*!Function     interrupt0Cleanup
*   \return     void
*   \par Purpose
*               debounce interrupt zero
*/
void
interrupt0Cleanup(long tick)
{
    if(interrupt0Debounce)
    {
        if(tick > interrupt0Debounce)
        {
            interrupt0Debounce = 0;
        }
    }
}

/*!Function     debugStatus
*   \return     void
*   \par Purpose
*               debounce interrupt zero
*/
//void
//debugStatus(void)
//{
//    static rotationStatus status = LAST_STATUS;
//    if(pRotator->getRotationStatus() != status)
//    {
//        status = pRotator->getRotationStatus();
//        switch(status)
//        {
//        case ROTATE_IDLE:
//            printf("ROTATE_IDLE\n");
//            break;
//        case ROTATE_CCW:
//            printf("ROTATE_CCW\n");
//            break;
//        case ROTATE_CW:
//            printf("ROTATE_CW\n");
//            break;
//        case ROTATE_START:
//            printf("ROTATE_START\n");
//            break;
//        case ROTATE_ERROR:
//            printf("ROTATE_ERROR\n");
//            break;
//        default:
//            printf("ROTATE unknown\n");
//            break;
//        }
//    }
//}
