/*
 * controlProcessTest.cpp
 *
 *  Created on: Jun 22, 2011
 *      Author: dinkem1
 */
#include "stdio.h"
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "displayInterface.hpp"
#include "rotator.hpp"
#include "mocks/mockDisplay.hpp"
#include "mocks/mockRotator.hpp"
#include "mocks/mockHardware.hpp"
#include "wiring.h"
#include "controlProcess.hpp"

Rotator *pRotator = 0;
DisplayInterface *pDisplay = 0;

extern long interrupt0Debounce;
extern uint32_t convertToNorthCenteredDegrees(uint32_t percentageValue);
extern uint32_t convertToPercentage(uint32_t potValue);
extern void displayRotatorPot(void);
extern void displayControlPot(void);

namespace
{
using namespace mockRotator;
using namespace mockHardware;

TEST_GROUP(noSetUp){};


TEST_GROUP(controlProcessSetUp)
{
    MockHardware *pMockHardware;

    void setup()
    {
        pDisplay = new MockDisplay;
        pRotator = new MockRotator;
        pMockHardware = new MockHardware;
        pRotator->configureHardwareInterface(pMockHardware);
    }

    void teardown()
    {
        delete pMockHardware;
        delete pRotator;
        delete pDisplay;
    }
};


TEST(noSetUp, interrupt0Handler)
{
    pRotator = new Rotator;
    setMockMillis(45000);

    interrupt0Debounce = 0;
    interrupt0Handler();
    CHECK_EQUAL(45, interrupt0Debounce);

    interrupt0Debounce = 100;
    interrupt0Handler();
    CHECK_EQUAL(100, interrupt0Debounce);

    delete pRotator;
}

TEST(noSetUp, interrupt0Cleanup)
{
    interrupt0Debounce = 100;
    interrupt0Cleanup(101);
    CHECK_EQUAL(0, interrupt0Debounce);

    interrupt0Debounce = 100;
    interrupt0Cleanup(99);
    CHECK_EQUAL(100, interrupt0Debounce);
}

TEST(noSetUp, convertToNorthCenteredDegrees)
{
    CHECK_EQUAL(0, convertToNorthCenteredDegrees(50));
    CHECK_EQUAL(180, convertToNorthCenteredDegrees(0));
    CHECK_EQUAL(180, convertToNorthCenteredDegrees(100));
    CHECK_EQUAL(270, convertToNorthCenteredDegrees(75));
    CHECK_EQUAL(90, convertToNorthCenteredDegrees(25));
}

TEST(noSetUp, convertToPercentage)
{
    CHECK_EQUAL(0, convertToPercentage(0));
    CHECK_EQUAL(25, convertToPercentage(256));
    CHECK_EQUAL(50, convertToPercentage(512));
    CHECK_EQUAL(75, convertToPercentage(768));
    CHECK_EQUAL(100, convertToPercentage(1023));
}

TEST(controlProcessSetUp, displayRotatorPot)
{
    setTestHeading(0xffff);
    pMockHardware->setRotatorPotValue(512);
    displayRotatorPot();
    CHECK_EQUAL(0,getTestHeading());

    setTestHeading(0xffff);
    pMockHardware->setRotatorPotValue(256);
    displayRotatorPot();
    CHECK_EQUAL(90,getTestHeading());

    setTestHeading(0xffff);
    pMockHardware->setRotatorPotValue(768);
    displayRotatorPot();
    CHECK_EQUAL(270,getTestHeading());

    setTestHeading(0xffff);
    pMockHardware->setRotatorPotValue(1023);
    displayRotatorPot();
    CHECK_EQUAL(180,getTestHeading());

}

TEST(noSetUp, displayRotatorPot_noDisplay)
{
    MockHardware *pMockHardware;
    pRotator = new MockRotator;
    pMockHardware = new MockHardware;
    pDisplay = 0;

    setTestHeading(0xbaad);
    pMockHardware->setRotatorPotValue(512);
    displayRotatorPot();
    CHECK_EQUAL(0xbaad,getTestHeading());

    delete pMockHardware;
    delete pRotator;
}

TEST(noSetUp, displayRotatorPot_noRotator)
{
    MockHardware *pMockHardware;
    pRotator = 0;
    pMockHardware = new MockHardware;
    pDisplay = new MockDisplay;

    setTestHeading(0xbadd);
    pMockHardware->setRotatorPotValue(512);
    displayRotatorPot();
    CHECK_EQUAL(0xbadd,getTestHeading());

    delete pMockHardware;
    delete pDisplay;
}

TEST(controlProcessSetUp, displayControlPot)
{
    setTestHeading(0xffff);
    pMockHardware->setControlPotValue(512);
    displayControlPot();
    CHECK_EQUAL(0,getTestHeading());

    setTestHeading(0xffff);
    pMockHardware->setControlPotValue(256);
    displayControlPot();
    CHECK_EQUAL(90,getTestHeading());

    setTestHeading(0xffff);
    pMockHardware->setControlPotValue(768);
    displayControlPot();
    CHECK_EQUAL(270,getTestHeading());

    setTestHeading(0xffff);
    pMockHardware->setControlPotValue(1023);
    displayControlPot();
    CHECK_EQUAL(180,getTestHeading());

}

TEST(noSetUp, displayControlPot_noDisplay)
{
    MockHardware *pMockHardware;
    pRotator = new MockRotator;
    pMockHardware = new MockHardware;
    pDisplay = 0;

    setTestHeading(0xbaad);
    pMockHardware->setControlPotValue(512);
    displayControlPot();
    CHECK_EQUAL(0xbaad,getTestHeading());

    delete pMockHardware;
    delete pRotator;
}

TEST(noSetUp, displayControlPot_noRotator)
{
    MockHardware *pMockHardware;
    pRotator = 0;
    pMockHardware = new MockHardware;
    pDisplay = new MockDisplay;

    setTestHeading(0xbadd);
    pMockHardware->setControlPotValue(512);
    displayControlPot();
    CHECK_EQUAL(0xbadd,getTestHeading());

    delete pMockHardware;
    delete pDisplay;
}

TEST(controlProcessSetUp, updateDisplay)
{
    pRotator->setRotationStatus(ROTATE_IDLE);
    setDisplayMsg(0);
    updateDisplay();
    CHECK_EQUAL(idle, getDisplayMsg());

    pRotator->setRotationStatus(ROTATE_ERROR);
    setDisplayMsg(0);
    updateDisplay();
    CHECK_EQUAL((error|idle), getDisplayMsg());

    pRotator->setRotationStatus(ROTATE_CCW);
    setDisplayMsg(0);
    updateDisplay();
    CHECK_EQUAL((rotate|ccw), getDisplayMsg());

    pRotator->setRotationStatus(ROTATE_CCW);
    setDisplayMsg(0);
    updateDisplay();
    CHECK_EQUAL(ccw, getDisplayMsg());

    pRotator->setRotationStatus(ROTATE_CW);
    setDisplayMsg(0);
    updateDisplay();
    CHECK_EQUAL((rotate|cw), getDisplayMsg());

    pRotator->setRotationStatus(ROTATE_CW);
    setDisplayMsg(0);
    updateDisplay();
    CHECK_EQUAL(cw, getDisplayMsg());

    pRotator->setRotationStatus(ROTATE_START);
    setDisplayMsg(0);
    updateDisplay();
    CHECK_EQUAL(0x0000, getDisplayMsg());
}



} //namespace
