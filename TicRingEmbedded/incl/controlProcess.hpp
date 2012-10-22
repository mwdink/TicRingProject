/*
 * controlProcess.hpp
 *
 *  Created on: Jun 21, 2011
 *      Author: dinkem1
 */

#ifndef CONTROLPROCESS_HPP_
#define CONTROLPROCESS_HPP_

/*----------------------------- Nested includes -----------------------------*/
#include "rotator.hpp"
#include "twoLineDisplay.hpp"

/*----------------- Symbolic Constants and Macros (defines) -----------------*/
/*-------------------------- Typedefs and structs ---------------------------*/
/*----------------------- Declarations (externs only) -----------------------*/
/*------------------------------ Declarations -------------------------------*/
/*--------------------------- Function prototypes ---------------------------*/
void updateDisplay(void);
void processRotator(void);
void interrupt0Handler(void);
void interrupt0Cleanup(long tick);


#endif /* CONTROLPROCESS_HPP_ */
