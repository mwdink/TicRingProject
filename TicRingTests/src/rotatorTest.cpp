/*
 * rotatorTest.cpp
 *
 *  Created on: Jun 20, 2011
 *      Author: dinkem1
 */
#include "stdio.h"
#include "rotator.hpp"
#include "wiring.h"
#include "mocks/mockHardware.hpp"
#include "mocks/mockRotator.hpp"
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#define BIT_PATTERN1    0x5e5e
#define BIT_PATTERN2    0xe5e5
#define POT_VALUE_LOW   490
#define POT_VALUE_MID   500
#define POT_VALUE_HIGH  510

namespace
{
using namespace mockHardware;
using namespace mockRotator;


TEST_GROUP(noSetUp){};


TEST_GROUP(rotatorSetUp)
{
    MockRotator *pTestRotator;
    MockHardware *pMockHardware;

    void setup()
    {
        pTestRotator = new MockRotator;
        pMockHardware = new MockHardware;
        pTestRotator->configureHardwareInterface(pMockHardware);
    }

    void teardown()
    {
        delete pTestRotator;
        delete pMockHardware;
    }
};

/* check the contruction of the rooatator object */
TEST(noSetUp, constructor)
{
    MockRotator *pTestRotator;
    pTestRotator = new MockRotator;
    CHECK(pTestRotator != 0);
    CHECK(ROTATE_IDLE == pTestRotator->getRotation());
    CHECK(1000 == pTestRotator->getLastControlPotValue());
    CHECK(1000 == pTestRotator->getLastRotatorPotValue());
    CHECK(0 == pTestRotator->getProgressSecondCount());
    CHECK(0 == pTestRotator->getHardwareInterface());
    delete pTestRotator;
}

/* check the functionality of getControlPotValue */
TEST(rotatorSetUp, getControlPotValue)
{
    pMockHardware->setControlPotValue(0xeeee);
    CHECK_EQUAL(0xeeee, pTestRotator->getControlPotValue());
    pMockHardware->setControlPotValue(0x5555);
    CHECK_EQUAL(0x5555, pTestRotator->getControlPotValue());
    /* clear the hardware interface */
    pTestRotator->configureHardwareInterface(0);
    CHECK_EQUAL(0x0000, pTestRotator->getControlPotValue());
}

/* check the functionality of getRotatorPotValue */
TEST(rotatorSetUp, getRotatorPotValue)
{
    pMockHardware->setRotatorPotValue(0xeeee);
    CHECK_EQUAL(0xeeee, pTestRotator->getRotatorPotValue());
    pMockHardware->setRotatorPotValue(0x5555);
    CHECK_EQUAL(0x5555, pTestRotator->getRotatorPotValue());
    /* clear the hardware interface */
    pTestRotator->configureHardwareInterface(0);
    CHECK_EQUAL(0x0000, pTestRotator->getRotatorPotValue());
}


/* check the functionality of getRotationStatus */
TEST(rotatorSetUp, getRotationStatus)
{
    pTestRotator->setRotation(ROTATE_IDLE);
    CHECK_EQUAL(ROTATE_IDLE, pTestRotator->getRotationStatus());
    pTestRotator->setRotation(ROTATE_CCW);
    CHECK_EQUAL(ROTATE_CCW, pTestRotator->getRotationStatus());
    pTestRotator->setRotation(ROTATE_CW);
    CHECK_EQUAL(ROTATE_CW, pTestRotator->getRotationStatus());
    pTestRotator->setRotation(ROTATE_START);
    CHECK_EQUAL(ROTATE_START, pTestRotator->getRotationStatus());
    pTestRotator->setRotation(ROTATE_ERROR);
    CHECK_EQUAL(ROTATE_ERROR, pTestRotator->getRotationStatus());
    pTestRotator->setRotation(LAST_STATUS);
    CHECK_EQUAL(ROTATE_ERROR, pTestRotator->getRotationStatus());
}

/* check the functionality of startRotation */
TEST(rotatorSetUp, startRotation)
{
    setMockMillis(20000);
    pMockHardware->setRotatorPotValue(BIT_PATTERN1);
    pTestRotator->setRotation(ROTATE_CCW);
    pTestRotator->startRotation();
    CHECK_EQUAL(ROTATE_CCW, pTestRotator->getRotation());
    CHECK_EQUAL(0, pTestRotator->getProgressSecondCount());
    CHECK_EQUAL(0, pTestRotator->getProgressRotationValue());

    setMockMillis(20000);
    pMockHardware->setRotatorPotValue(BIT_PATTERN1);
    pTestRotator->setRotation(ROTATE_CW);
    pTestRotator->startRotation();
    CHECK_EQUAL(ROTATE_CW, pTestRotator->getRotation());
    CHECK_EQUAL(0, pTestRotator->getProgressSecondCount());
    CHECK_EQUAL(0, pTestRotator->getProgressRotationValue());

    setMockMillis(20000);
    pMockHardware->setRotatorPotValue(BIT_PATTERN1);
    pTestRotator->setRotation(ROTATE_START);
    pTestRotator->startRotation();
    CHECK_EQUAL(ROTATE_START, pTestRotator->getRotation());
    CHECK_EQUAL(0, pTestRotator->getProgressSecondCount());
    CHECK_EQUAL(0, pTestRotator->getProgressRotationValue());

    setMockMillis(20000);
    pMockHardware->setRotatorPotValue(BIT_PATTERN1);
    pTestRotator->setRotation(ROTATE_ERROR);
    pTestRotator->startRotation();
    CHECK_EQUAL(ROTATE_START, pTestRotator->getRotation());
    CHECK_EQUAL(25, pTestRotator->getProgressSecondCount());
    CHECK_EQUAL(BIT_PATTERN1, pTestRotator->getProgressRotationValue());

    setMockMillis(50000);
    pMockHardware->setRotatorPotValue(BIT_PATTERN2);
    pTestRotator->setRotation(ROTATE_IDLE);
    pTestRotator->startRotation();
    CHECK_EQUAL(ROTATE_START, pTestRotator->getRotation());
    CHECK_EQUAL(55, pTestRotator->getProgressSecondCount());
    CHECK_EQUAL(BIT_PATTERN2, pTestRotator->getProgressRotationValue());
}

/* check the functionality of controlRotation  - START */
TEST(rotatorSetUp, controlRotation_START)
{
    pTestRotator->setRotation(ROTATE_START);
    pMockHardware->setRotatorPotValue(POT_VALUE_MID);
    pMockHardware->setControlPotValue(POT_VALUE_HIGH);
    pTestRotator->controlRotation();
    CHECK_EQUAL(ROTATE_CCW, pTestRotator->getRotation());
    CHECK_EQUAL(LONG_VALUE2, pMockHardware->getTestValue());

    pTestRotator->setRotation(ROTATE_START);
    pMockHardware->setRotatorPotValue(POT_VALUE_MID);
    pMockHardware->setControlPotValue(POT_VALUE_LOW);
    pTestRotator->controlRotation();
    CHECK_EQUAL(ROTATE_CW, pTestRotator->getRotation());
    CHECK_EQUAL(LONG_VALUE1, pMockHardware->getTestValue());

    pTestRotator->setRotation(ROTATE_START);
    pMockHardware->setRotatorPotValue(POT_VALUE_MID);
    pMockHardware->setControlPotValue(POT_VALUE_MID);
    pTestRotator->controlRotation();
    CHECK_EQUAL(ROTATE_IDLE, pTestRotator->getRotation());
}

/* check the functionality of controlRotation  - no affect expected */
TEST(rotatorSetUp, controlRotation_IDLE)
{
    pTestRotator->setRotation(ROTATE_IDLE);
    pTestRotator->controlRotation();
    CHECK_EQUAL(ROTATE_IDLE, pTestRotator->getRotation());

    pTestRotator->setRotation(ROTATE_ERROR);
    pTestRotator->controlRotation();
    CHECK_EQUAL(ROTATE_ERROR, pTestRotator->getRotation());
}

/* check the functionality of controlRotation  - rotating CCW */
TEST(rotatorSetUp, controlRotation_CCW)
{
    pTestRotator->setRotation(ROTATE_CCW);
    pMockHardware->setRotatorPotValue(POT_VALUE_MID);
    pMockHardware->setControlPotValue(POT_VALUE_MID);
    pTestRotator->controlRotation();
    CHECK_EQUAL(ROTATE_IDLE, pTestRotator->getRotation());

    pTestRotator->setRotation(ROTATE_CCW);
    pMockHardware->setRotatorPotValue(POT_VALUE_MID);
    pMockHardware->setControlPotValue(POT_VALUE_LOW);
    pTestRotator->controlRotation();
    CHECK_EQUAL(ROTATE_IDLE, pTestRotator->getRotation());

    pTestRotator->setRotation(ROTATE_CCW);
    pMockHardware->setRotatorPotValue(POT_VALUE_LOW);
    pMockHardware->setControlPotValue(POT_VALUE_MID);
    pTestRotator->controlRotation();
    CHECK_EQUAL(ROTATE_CCW, pTestRotator->getRotation());
}

/* check the functionality of controlRotation  - rotating CW */
TEST(rotatorSetUp, controlRotation_CW)
{
    pTestRotator->setRotation(ROTATE_CW);
    pMockHardware->setRotatorPotValue(POT_VALUE_MID);
    pMockHardware->setControlPotValue(POT_VALUE_MID);
    pTestRotator->controlRotation();
    CHECK_EQUAL(ROTATE_IDLE, pTestRotator->getRotation());

    pTestRotator->setRotation(ROTATE_CW);
    pMockHardware->setRotatorPotValue(POT_VALUE_LOW);
    pMockHardware->setControlPotValue(POT_VALUE_MID);
    pTestRotator->controlRotation();
    CHECK_EQUAL(ROTATE_IDLE, pTestRotator->getRotation());

    pTestRotator->setRotation(ROTATE_CW);
    pMockHardware->setRotatorPotValue(POT_VALUE_MID);
    pMockHardware->setControlPotValue(POT_VALUE_LOW);
    pTestRotator->controlRotation();
    CHECK_EQUAL(ROTATE_CW, pTestRotator->getRotation());
}

/* check the functionality of configureToRotateCCW */
TEST(rotatorSetUp, configureToRotateCCW)
{
    pTestRotator->setRotation(ROTATE_IDLE);
    pMockHardware->clearTestValue();
    pTestRotator->testAccessToConfigureToRotateCCW();
    CHECK_EQUAL(ROTATE_CCW, pTestRotator->getRotation());
    CHECK_EQUAL(LONG_VALUE2, pMockHardware->getTestValue());

    pTestRotator->setRotation(ROTATE_IDLE);
    pMockHardware->clearTestValue();
    pTestRotator->configureHardwareInterface(0);
    pTestRotator->testAccessToConfigureToRotateCCW();
    CHECK_EQUAL(ROTATE_ERROR, pTestRotator->getRotation());
    CHECK_EQUAL(0, pMockHardware->getTestValue());
}

/* check the functionality of configureToRotateCW */
TEST(rotatorSetUp, configureToRotateCW)
{
    pTestRotator->setRotation(ROTATE_IDLE);
    pMockHardware->clearTestValue();
    pTestRotator->testAccessToConfigureToRotateCW();
    CHECK_EQUAL(ROTATE_CW, pTestRotator->getRotation());
    CHECK_EQUAL(LONG_VALUE1, pMockHardware->getTestValue());

    pTestRotator->setRotation(ROTATE_IDLE);
    pMockHardware->clearTestValue();
    pTestRotator->configureHardwareInterface(0);
    pTestRotator->testAccessToConfigureToRotateCW();
    CHECK_EQUAL(ROTATE_ERROR, pTestRotator->getRotation());
    CHECK_EQUAL(0, pMockHardware->getTestValue());
}

/* check the functionality of stopRotation */
TEST(rotatorSetUp, stopRotation)
{
    pTestRotator->setRotation(ROTATE_CW);
    pMockHardware->clearTestValue();
    pTestRotator->testAccessToStopRotation();
    CHECK_EQUAL(ROTATE_IDLE, pTestRotator->getRotation());
    CHECK_EQUAL(LONG_VALUE3, pMockHardware->getTestValue());

    pTestRotator->setRotation(ROTATE_CW);
    pMockHardware->clearTestValue();
    pTestRotator->configureHardwareInterface(0);
    pTestRotator->testAccessToStopRotation();
    CHECK_EQUAL(ROTATE_ERROR, pTestRotator->getRotation());
    CHECK_EQUAL(0, pMockHardware->getTestValue());
}


} //end of namespace
