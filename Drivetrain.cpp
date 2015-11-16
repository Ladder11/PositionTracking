#include "Drivetrain.h"

/** Constructor
  * @param RegulatedMotor leftMotor The RegulatedMotor object that corresponds to the motor on the left side of the robot
  * @param RegulatedMotor rightMotor The RegulatedMotor object that corresponds to the motor on the right side of the robot
  * @param float wheelDia Diameter in inches of the drive wheels
  * @param float gearRatio Torque ratio of the motor to drive wheels
  * @param float trackWidth Width in inches of the drivetrain's track
  **/
Drivetrain::Drivetrain(RegulatedMotor* leftMotor, RegulatedMotor* rightMotor, float wheelDia, float gearRatio, float trackWidth) {
	_leftMotor = leftMotor;
	_rightMotor = rightMotor;
	_gearRatio = gearRatio;
	_trackWidth = trackWidth;
	_wheelDia = wheelDia;
	_speedConversion = 19.1/wheelDia/gearRatio; //19.099 = 60/pi //#TODO Check this number
}

/**
 * Assumes that the motors have been initialized
 **/
void Drivetrain::initialize() {
}

/**
 * Moves the robot at a linear speed (fwd/rev) and a turning speed (l/r)
 * @param float Velocity The tangential velocity of the center of the robot (in/s)
 * @param float turnVelocity The turning velocity of the robot (deg/s)
**/
void Drivetrain::drive(float velocity, float turnVelocity) {
	turnVelocity = turnVelocity*3.1415/360;
	V_r = velocity+(_trackWidth*turnVelocity)/2;
	V_l = velocity-(_trackWidth*turnVelocity)/2;
	//Serial.println(V_r*_speedConversion);
	//Serial.println(V_l*_speedConversion);
	_rightMotor->setRPM(V_r*_speedConversion);
	_leftMotor->setRPM(V_l*_speedConversion);
}

float Drivetrain::getXOdoEst() {
	return 0;
}

float Drivetrain::getYOdoEst() {
	return 0;
}

float Drivetrain::getOrientOdoEst() {
	_theta = (_leftMotor->getRevolutions()-_rightMotor->getRevolutions())*_wheelDia/(2*_trackWidth)*360;
	return _theta; 
}