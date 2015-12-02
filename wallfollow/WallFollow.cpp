#include "WallFollow.h"

WallFollow::WallFollow(Drivetrain* drivetrain, ultrasonic* leftSensor, ultrasonic* rightSensor) {
	_lUS = leftSensor;
	_rUS = rightSensor;
}

void WallFollow::initialize() {

}

void WallFollow::followLeftWall(){
	if(_lUS->distance()<7)
		drive(5,20);
	else if(_lUS->distance()>7)
		drive(2,-10);
	else
		drive(2,0);
  Serial.println(_lUS->distance());
}

void WallFollow::followRightWall(){
	// if(_rUS->distance()<2)
	// 	drive(2,-10);
	// else if(_rUS->distance()>2)
	// 	drive(2,10);
	// else
	// 	drive(3,0);
}
