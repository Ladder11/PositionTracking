#include <Wire.h>
#include <PVision.h>
#include "KitEncoder.h"
#include "KitMotor.h"
#include "RegulatedMotor.h"
#include "Drivetrain.h"

KitEncoder* rightEncoder;
KitEncoder* leftEncoder;
KitMotor* rightMotor;
KitMotor* leftMotor;
RegulatedMotor* leftRegMotor;
RegulatedMotor* rightRegMotor;
Drivetrain* drivetrain;

PVision ircam;
byte result;
float error;

void setup()
{
  Serial.begin(115200);
  Serial.println("Hello");
  ircam.init();

  rightEncoder = new KitEncoder(22);
  leftEncoder = new KitEncoder(23);
  rightMotor = new KitMotor(4, 5);
  leftMotor = new KitMotor(6, 7);
  
  leftEncoder->initialize();
  rightEncoder->initialize();
  leftMotor->initialize();
  rightMotor->initialize();

  leftRegMotor = new RegulatedMotor(leftMotor, leftEncoder, 50, 64);
  rightRegMotor = new RegulatedMotor(rightMotor, rightEncoder, 50, 64);
  drivetrain = new Drivetrain(leftRegMotor, rightRegMotor, 2.75, 0.3, 5.3125);  
  drivetrain->initialize();

}

void loop() {
  result = ircam.read();
  error = (512-ircam.Blob1.X)*-0.25;
  if (result&BLOB1) {
    Serial.print("X: ");
    Serial.println(ircam.Blob1.X);
    Serial.print("Y: ");
    Serial.println(ircam.Blob1.Y);
  } else {
    Serial.println("Nothing");
  }
  
  drivetrain->drive(0, error);

}