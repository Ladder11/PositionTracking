#ifndef WALLFOLLOW
#define WALLFOLLOW
#include <Arduino.h>
#include "ultrasonic.h"
#include "Drivetrain.h"

class WallFollow {
public:
  WallFollow(Drivetrain* drivetrain, ultrasonic* leftSensor, ultrasonic* rightSensor);
  void initialize();
  void followLeftWall();
  void followRightWall(float set);
private:
  Drivetrain* _drivetrain;
  ultrasonic* _rUS;
  ultrasonic* _lUS;
};



#endif
