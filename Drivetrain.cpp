#include "Drivetrain.h"
#include "ultrasonic.h"


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
	_turnConversion = gearRatio*wheelDia*3.1415;
}

/**
 * Assumes that the motors have been initialized
 **/
void Drivetrain::initialize() {
	xPos = 0;
	yPos = 0;
	_theta = 0;
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
	updateRobotPos();
}

double Drivetrain::getXOdoEst() {
	return xPos;
}

double Drivetrain::getYOdoEst() {
	return yPos;
}

/**
 * Assumes that the robot is facing along the +y axis when turned on
 * @return float theta Deviation from the +y axis, in radians
 **/
double Drivetrain::getOrientOdoEst() {
	// while (_theta >= 360) {
	// 	_theta-=360;
	// }
	// while (_theta <= -360) {
	// 	_theta+=360; 
	// }
	// if (_theta > 180) {
	// 	_theta -= 360;
	// } else if (_theta < -180) {
	// 	_theta += 360;
	// }
	return _theta; 
}

/**
 * Updates the odometry estimates for the robot's x, y, and theta positions
 **/
void Drivetrain::updateRobotPos() {

	currLeft = _leftMotor->getRevolutions();
	currRight = _rightMotor->getRevolutions();

	leftDelta = currLeft-prevLeft;
	rightDelta = currRight-prevRight;
	robotDelta = (leftDelta+rightDelta)/2*_turnConversion;
	// Serial.print("Left: ");
	// Serial.println(leftDelta);
	// Serial.print("Right: ");
	// Serial.println(rightDelta);

	_theta+=atan((leftDelta-rightDelta)*_turnConversion/_trackWidth);
	// Serial.print("Theta: ");
	// Serial.println(_theta);
	xPos+=robotDelta*sin(_theta);
	yPos+=robotDelta*cos(_theta);

	prevLeft = currLeft;
	prevRight = currRight;
}

void Drivetrain::followLeftWall(){
	if(getInchestoWall(leftUSPin)<2)
		drive(2,10);
	else if(getInchestoWall(rightUSPin>4)
		drive(2,-10);
	else
		drive(2,0);
}

void Drivetrain::followRIghtWall(){
	if(getInchestoWall(RightUSPin)<2)
		drive(2,-10);
	else if(getInchestoWall(rightUSPin>4)
		drive(2,10);
	else
		drive(3,0);
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

float Drivetrain::getInchestoWall(int pingPin){
	// establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  //cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(10);
  return inches;
}