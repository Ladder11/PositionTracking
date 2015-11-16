#ifndef KITMOTOR
#define KITMOTOR
#include <Arduino.h>

class KitMotor {
public:
  KitMotor(int FWDpin, int REVpin);
  void initialize();
  void setOutput(float setpoint);
private:
  int _FWDpin, _REVpin;
};



#endif