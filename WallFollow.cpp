#include "WallFollow.h"

WallFollow::WallFollow(Drivetrain* drivetrain, ultrasonic* leftSensor, ultrasonic* rightSensor) {
	_lUS = leftSensor;
	_rUS = rightSensor;
	_drivetrain=drivetrain;
}

void WallFollow::initialize() {

}

void WallFollow::followLeftWall(){
	float dist=_lUS->distance();
	if(dist>7.5){
		_drivetrain->drive(0,40); 
		Serial.println("TURNING RIGHT");}

	else if(dist<6){
		_drivetrain->drive(0,-40); 
		Serial.println("turning left");}
	else
		_drivetrain->drive(2,0);
  Serial.println(_lUS->distance());
}

void WallFollow::followRightWall(float set){
	float dist=_rUS->distance();
	_drivetrain->drive(4, set-dist);
  	Serial.println(_lUS->distance());
}