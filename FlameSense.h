#ifndef FLAMESENSE
#define FLAMESENSE
#include <Arduino.h>
#include <PVision.h>

class FlameSense {
	public: 
		FlameSense(int xDegrees, int yDegrees);
		void initialize();
		bool isFlame();
		float flameAngle();
		float flameHeight();
		float flameDistance();
	private:
		float _xAngleComp, _yAngleComp;
		PVision ircam;
};
#endif