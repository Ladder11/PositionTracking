#ifndef DRIVETRAIN
#define DRIVETRAIN
#include <Arduino.h>
#include "RegulatedMotor.h"

class Drivetrain {
public:
  Drivetrain(RegulatedMotor* leftMotor, RegulatedMotor* rightMotor, float wheelDia, float gearRatio, float trackWidth);
  void initialize();
  void drive(float velocity, float turnVelocity);
  void stop();
  double getXOdoEst();
  double getYOdoEst();
  double getOrientOdoEst();
  void updateRobotPos();
private:
  RegulatedMotor* _leftMotor;
  RegulatedMotor* _rightMotor;
  float _speedConversion, _gearRatio, _trackWidth, V_r, V_l, _wheelDia, prevVel, 
        currAngle, _turnConversion, currLeft, currRight, prevLeft, prevRight, 
        leftDelta, rightDelta, robotDelta;
  double xPos, yPos, _theta;
};



#endif