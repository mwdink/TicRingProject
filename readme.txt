
A TicRing is an antenna rotator that goes around the tower (versus on top
of a tower). This allows for mounting/rotating antennas at any point along the
length of the tower. A control head sits at the operator location that allows
moving the antenna to any azimuth.

The TicRing controller uses analog circutry and is subject to calibration
and drifting issues. Frequently, tapping the meter would result
in a different indication by 10-20 degrees.  

The purpose of this project was to drop in replacement control circuitry
using a micro-controller (Atmel AVR in a Arduino form factor).

The microcontroller reads the pot in the TicRing directly, converting it
to degrees for display on the LCD. There is a similar pot on the control
head for setting the desired azimuth. When a start switch is pressed, 
the micro-controller fires the appropriate relay combination to turn the
TicRing motor. When the TicRing gets within 5 degrees of the setting, it
turns off the motor.

Having a micro-controller affords an additional advantage. If the TicRing
does not appear to be moving, the controller can stop the motor immediately.
Hopefully, this will help prevent future occurances of incidents that have
happened in the past where the pot in the TicRing failed but the motor kept on 
going (there are no mechanical limits) until I noticed a problem. Normally,
this results in the coaxial cable being damaged.


