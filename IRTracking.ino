#include <Wire.h>
#include <PVision.h>
#include "KitEncoder.h"
#include "KitMotor.h"
#include "RegulatedMotor.h"
#include "Drivetrain.h"
#include "Servo.h"

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
Servo prop;

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
  error = (512-ircam.Blob1.X)*-0.5;
  if (abs(error) < 2 && abs((300-analogRead(0))) < 10) {
    drivetrain->drive(0, 0);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    prop.attach(11, 1000, 2000);
    prop.write(180);
    delay(40);
    prop.write(0);
    delay(1000);
    prop.write(180);
    while(1){
      result = ircam.read();
      if (!(result&BLOB1)){
        delay(3000);
        result = ircam.read();
        if (!(result&BLOB1)){
          prop.write(0);
        }
      }
    }
  }
  if (result&BLOB1) {
    Serial.print("X: ");
    Serial.println(ircam.Blob1.X);
    Serial.print("Y: ");
    Serial.println(ircam.Blob1.Y);
  } else {
    Serial.println("Nothing");
  }
  Serial.print("Flame sensor: ");
  Serial.println(analogRead(0));
  drivetrain->drive(-.01*(300-analogRead(0)), error);

}