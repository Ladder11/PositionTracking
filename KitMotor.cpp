#include "KitMotor.h"

/** Constructor
  * @param int FWDpin The analog capable digital pin that the H-bridge is wired to, such that when it is high, the motor will drive forward
  * @param int REVpin The analog capable digital pin that the H-bridge is wired to, such that when it is high, the motor will drive in reverse
  **/

KitMotor::KitMotor(int FWDpin, int REVpin) {
	_FWDpin = FWDpin;
	_REVpin = REVpin;
}

/**
 * Performs initial setup of the motor pins, and grounds both pins to ensure no movement
 **/

void KitMotor::initialize() {
  pinMode(_FWDpin, OUTPUT);
  pinMode(_REVpin, OUTPUT);
  digitalWrite(_FWDpin, LOW);
  digitalWrite(_REVpin, LOW);
}

/**
 * Sets the motor to move
 * @param float setpoint Value from -1.0 (full reverse) to 1.0 (full forward)
**/

void KitMotor::setOutput(float setpoint) {
  setpoint = constrain(setpoint, -1.0, 1.0); 
  if (setpoint > 0.0) {
  	analogWrite(_FWDpin, 255*setpoint);
  	digitalWrite(_REVpin, LOW);
  } else if (setpoint < 0.0) {
  	analogWrite(_REVpin, -255*setpoint);
  	digitalWrite(_FWDpin, LOW);
  } else {
  	digitalWrite(_FWDpin, LOW);
  	digitalWrite(_REVpin, LOW);
  }
}