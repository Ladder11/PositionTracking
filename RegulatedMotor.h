#ifndef REGULATEDMOTOR
#define REGULATEDMOTOR
#include <Arduino.h>
#include "KitMotor.h"
#include "KitEncoder.h"

class RegulatedMotor {
public:
  RegulatedMotor(KitMotor* motor, KitEncoder* encoder, float gearboxRatio, int encoderCounts);
  void initialize();
  void setRPM(float rpms);
  float getRPM();
  bool isStalled();
  float getRevolutions();
private:
  KitMotor* _motor;
  KitEncoder* _encoder;
  float _gearboxRatio;
  int _encoderCounts;
  float avgRPM, newOut, _scaleFactor, arpm;
  float out = 0.5; //#TODO: Probably not a great idea, need to find a better way to do this
  long lastCount, currentCount;
  unsigned long lastTime, currentTime;
};



#endif