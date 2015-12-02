#include "Gyro.h"

Gyro::Gyro() {

}

void Gyro::initialize() {
  Wire.begin(); // i2c begin
  if (!gyro.init()) // gyro init
  {
    Serial.println("Failed to autodetect gyro type!");
    while (1); 
  }
  gyro.enableDefault(); // gyro init. default 250/deg/s

  delay(1000);// allow time for gyro to settle
  gdriftx = 0;
  gyro_xcumulative = 0;
  gerrx = 0;
  setGyroOffset();
  //setGyroDrift();
  prevTime = millis();
}

float Gyro::getGyro() {
  return gyro_xcumulative;
}

void Gyro::updateGyro() {
  Dt = (float)(millis()-prevTime)/1000.0;
  gyro.read(); // read gyro

  gyro_x=(float)(gyro.g.x-gerrx)*G_gain;
 
  gyro_x = (gyro_x)*Dt;
  //gyro_x -= gdriftx*Dt;
 
  gyro_xcumulative += gyro_x;

  prevTime=millis(); //reset prevTime
}

void Gyro::setGyroOffset() {
  for(int i=0;i<100;i++){  // takes 100 samples of the gyro
    gyro.read();
    gerrx+=gyro.g.x;
    delay(25);
  }

  gerrx = gerrx/100;
}

void Gyro::setGyroDrift() {
// Get drift rate
  long stime = millis();
  prevTime = millis();
  for(int i =0;i<500;i++){ 
    updateGyro();
    delay(25);
  }
  long etime = millis();

  gdriftx = gyro_xcumulative/(etime-stime)*1000;
  Serial.println(gyro_xcumulative);
  gyro_xcumulative = 0;
  Serial.println(gdriftx);
}
