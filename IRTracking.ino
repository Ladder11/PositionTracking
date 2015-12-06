#include <Wire.h>
#include <PVision.h>
#include "KitEncoder.h"
#include "KitMotor.h"
#include "RegulatedMotor.h"
#include "Drivetrain.h"
#include "Servo.h"
#include "FlameSense.h"
#include "ultrasonic.h"
#include <LiquidCrystal.h>

KitEncoder* rightEncoder;
KitEncoder* leftEncoder;
KitMotor* rightMotor;
KitMotor* leftMotor;
RegulatedMotor* leftRegMotor;
RegulatedMotor* rightRegMotor;
Drivetrain* drivetrain;
FlameSense* flameSense;
ultrasonic frontSensor(26, 27);

LiquidCrystal lcd(40, 41, 42, 43, 44, 45);

// White, Green, Yellow - SPI
// Grey, Purple, White, Black - I2C
// Red 4-Blue, 5-Green, Yellow 6-Blue, 7-Green
// 2nd power - blue

// Yellow - 22, orange - 23

Servo prop;
float distSpeed;

void setup()
{
  Serial.begin(115200);
  Serial.println("Hello");
  lcd.begin(16, 2);

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

  flameSense = new FlameSense(40, 30);
  flameSense->initialize();

}

void loop() {
  if (abs(flameSense->flameAngle()*180/3.14) < 10 && frontSensor.distance() < 20) {
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
      if (!flameSense->isFlame()){
        delay(3000);
        if (!flameSense->isFlame()){
          prop.write(0);
          lcd.setCursor(0, 0);
          lcd.print("X: ");
          lcd.print(drivetrain->getXOdoEst(), DEC);
          lcd.setCursor(7, 0);
          lcd.print("Y: ");
          lcd.print(drivetrain->getYOdoEst(), DEC);
          lcd.setCursor(0, 1);
          lcd.print(" T: ");
          lcd.print(drivetrain->getOrientOdoEst());
          delay(5000);
        }
      }
    }
  }
  if (flameSense->isFlame()) {
    Serial.println("Flame");
  } else {
    Serial.println("Nothing");
  }
  Serial.print("Flame sensor: ");
  Serial.println(analogRead(0));
  distSpeed = .05*(frontSensor.distance()-20);
  if (flameSense->flameDistance()-700 < 20) {
    distSpeed = 0;
  }
  drivetrain->drive(distSpeed, flameSense->flameAngle()*180/3.1415*-7); //-.01*(800-flameSense->flameDistance())
  drivetrain->updateRobotPos();

}