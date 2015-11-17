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
	_turnConversion = _gearRatio*_wheelDia/_trackWidth*180;
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
	V_r = velocity+(_trackWidth*turnVelocity)/2.0;
	V_l = velocity-(_trackWidth*turnVelocity)/2.0;
	//Serial.println(V_r*_speedConversion);
	//Serial.println(V_l*_speedConversion);
	_rightMotor->setRPM(V_r*_speedConversion);
	_leftMotor->setRPM(V_l*_speedConversion);
	currTime = millis();
	currAngle = getOrientOdoEst()*3.1415/180.0;
	xPos+=prevVel*sin(currAngle)*(currTime-prevTime)/1000.0;
	yPos+=prevVel*cos(currAngle)*(currTime-prevTime)/1000.0;
	prevVel = velocity;
	prevTime = currTime;
}

float Drivetrain::getXOdoEst() {
	return xPos;
}

float Drivetrain::getYOdoEst() {
	return yPos;
}

/**
 * Assumes that the robot is facing along the +y axis when turned on
 * @return float theta Deviation from the +y axis, +/- 180deg
 **/
float Drivetrain::getOrientOdoEst() {
	_theta = (_leftMotor->getRevolutions()-_rightMotor->getRevolutions())*_turnConversion;
	//Serial.println(_leftMotor->getRevolutions());
	//Serial.println(_rightMotor->getRevolutions());
	Serial.println(_theta);
	//Serial.println(_leftMotor->getRevolutions()-_rightMotor->getRevolutions());
	// constrains output to be +/- 180, robot is facing in the +y-direction at the beginning
	while (_theta >= 360) {
		_theta-=360;
	}
	while (_theta <= -360) {
		_theta+=360; 
	}
	if (_theta > 180) {
		_theta -= 360;
	} else if (_theta < -180) {
		_theta += 360;
	}
	return _theta; 
}