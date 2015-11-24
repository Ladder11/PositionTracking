#include "KitEncoder.h"
#include "KitMotor.h"
#include "RegulatedMotor.h"
#include "Drivetrain.h"
#include "Gyro.h"

KitEncoder* rightEncoder;
KitEncoder* leftEncoder;
KitMotor* rightMotor;
KitMotor* leftMotor;
RegulatedMotor* leftRegMotor;
RegulatedMotor* rightRegMotor;
Drivetrain* drivetrain;
Gyro* gyro;

float angle;

bool output = true;

void setup() {
  Serial.begin(115200); 

  gyro = new Gyro();

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
  if (millis()%1000 < 10) {
    Serial.print("Odo Theta: ");
    angle = drivetrain->getOrientOdoEst()*180/3.1415;
    Serial.println(angle);
    Serial.print("Gyro Theta: ");
    Serial.println(gyro->getZGyro());
    // Serial.print("X: ");
    // Serial.println(drivetrain->getXOdoEst());
    // Serial.print("Y: ");
    // Serial.println(drivetrain->getYOdoEst());
  }
  
  drivetrain->drive(6.0, 0);
  
  //rightMotor->setOutput(1.0);
  //leftMotor->setOutput(1.0);
  delay(5);
}