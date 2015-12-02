#ifndef DRIVETRAIN
#define DRIVETRAIN
#include <Arduino.h>
#include "RegulatedMotor.h"
#include "ultrasonic.h"

class Drivetrain {
public:
  Drivetrain(RegulatedMotor* leftMotor, RegulatedMotor* rightMotor, float wheelDia, float gearRatio, float trackWidth);
  void initialize();
  void drive(float velocity, float turnVelocity);
  double getXOdoEst();
  double getYOdoEst();
  double getOrientOdoEst();
  void updateRobotPos();
private:
  RegulatedMotor* _leftMotor;
  RegulatedMotor* _rightMotor;
  ultrasonic* rUS;
  float _speedConversion, _gearRatio, _trackWidth, V_r, V_l, _wheelDia, prevVel, 
        currAngle, _turnConversion, currLeft, currRight, prevLeft, prevRight, 
        leftDelta, rightDelta, robotDelta;
  double xPos, yPos, _theta;
//  const int rightUSPinIN = 25;
//  const int rightUSPinOUT=24;
//  const int leftUSPinIN = 29;
//  const int leftUSPinOUT=28;
 
  
//  lUS= new ultrasonic(25,24);
//  rUS=new ultrasonic(28,29);
  //ultrasonic leftUltrasonic(25,24);
  //ultrasonic rightUltrasonic(29,28);
};



#endif
