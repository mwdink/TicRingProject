#include <wiring.h>

uint32_t milliValue = 0;


/* for test support */
void setMockMillis(uint32_t newMilliValue)
{
	milliValue = newMilliValue;
}

/* for testing - mocks AVR specific function */
uint32_t millis(void)
{
	return milliValue;
}
