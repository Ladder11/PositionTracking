#ifndef FLAMESENSE
#define FLAMESENSE
#include <Arduino.h>
#include <PVision.h>
#include "ultrasonic.h"

class FlameSense {
	public: 
		FlameSense(int xDegrees, int yDegrees);
		void initialize();
		bool isFlame();
		float flameAngle();
		float flameHeight(ultrasonic* frontSensor);
		float flameDistance(ultrasonic* frontSensor);
	private:
		float _xAngleComp, _yAngleComp;
		PVision ircam;
};
#endif