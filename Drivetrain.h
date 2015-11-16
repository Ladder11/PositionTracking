#ifndef DRIVETRAIN
#define DRIVETRAIN
#include <Arduino.h>
#include "RegulatedMotor.h"

class Drivetrain {
public:
  Drivetrain(RegulatedMotor* leftMotor, RegulatedMotor* rightMotor, float wheelDia, float gearRatio, float trackWidth);
  void initialize();
  void drive(float velocity, float turnVelocity);
  float getXOdoEst();
  float getYOdoEst();
  float getOrientOdoEst();
private:
  RegulatedMotor* _leftMotor;
  RegulatedMotor* _rightMotor;
  float _speedConversion, _gearRatio, _trackWidth, V_r, V_l, _theta, _wheelDia;
};



#endif