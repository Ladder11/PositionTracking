#include "FlameSense.h"

FlameSense::FlameSense(int xDegrees, int yDegrees) {
	_xAngleComp = tan(xDegrees*3.1415/180)/1023;
	_yAngleComp = tan(yDegrees*3.1415/180)/1023;
}

void FlameSense::initialize() {
	ircam.init();
}

bool FlameSense::isFlame() {
	return ircam.read()&BLOB1;
}

/**
 * Returns the angle to the candle in radians
 * @return float angle
 **/

float FlameSense::flameAngle() {
	ircam.read();
	return atan((512-ircam.Blob1.X)*_xAngleComp);
}

float FlameSense::flameHeight() {
	ircam.read();
	return sin(atan((512-ircam.Blob1.Y)*_yAngleComp))*flameDistance();
}

float FlameSense::flameDistance() {
	return analogRead(0); //#TODO: Fix this function
}